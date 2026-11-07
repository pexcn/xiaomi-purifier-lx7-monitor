# 小米净水器 500G 增强版（MR532-D）监视器

NodeMCU ESP8266 + SSD1306 128×32，通过局域网 MiIO/UDP 只读查询 `yunmi.waterpuri.lx7`，无需 Home Assistant 或云端登录。显示原水/纯水 TDS、温度及两支滤芯的流量寿命；默认每 2 秒轮询，熄屏时继续查询，支持 Wi-Fi 重连、超时重握手和异常提示。

**制水状态尚未核实，默认不自动熄屏。** 参考仓库未恢复制水标志；用户本次回忆闲置、制水时 `run_status/rinse` 都为 0，冲洗未测。不能将 `run_status != 0` 或 `rinse` 当成制水。可选择下面的近似亮屏模式，或在实测状态规则后启用准确的状态匹配。协议证据与限制见 [docs/protocol.md](docs/protocol.md)。本项目已编译及通过主机测试，尚未连接实物验证。

## 接线

NodeMCU 经 USB 5V 供电；OLED 的供电及 I²C 上拉使用 **3.3V**。

| OLED | NodeMCU |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | D2 / GPIO4 |
| SCL | D1 / GPIO5 |

默认 7 位地址 `0x3c`，可配置为 `0x3d`。配置中的引脚是 GPIO 编号。使用 U8g2 单页缓冲（128 字节），屏幕使用英文短标签，避免加载中文字库。`IN/OUT` 为 TDS，`F1` 为复合滤芯，`F2` 为 RO，`--` 表示字段不可用。

## 首次烧录和网页配置

只需通过 USB 刷入一次**应用固件**，无需构建或上传 `littlefs.bin`：

```sh
python3 -m venv .venv
# Linux/macOS；Windows 使用 .venv\Scripts\activate
. .venv/bin/activate
python -m pip install -r requirements.txt
pio run -e nodemcuv2
pio run -e nodemcuv2 -t upload
```

1. 新设备启动后，OLED 显示设置热点 `purifier-xxxxxx`、随机 `KEY` 和 `http://192.168.4.1`。
2. 手机/电脑连接该热点，在浏览器打开显示的地址，填写 Wi-Fi、净水器 IP、32 位十六进制 Token，并设置非空管理密码（不设最短长度，短密码也可）。
3. 若首次使用提示存储未初始化，勾选“初始化设备存储”再保存。设备会自行创建 LittleFS 并写入配置；已能正常挂载的存储不会被格式化。
4. 保存后自动重启。连接家庭 Wi-Fi，访问 `http://purifier-xxxxxx.local`，或设备连接成功时 OLED 显示的 IP；在登录页填写刚设置的管理密码即可，无需用户名。设备 IP 也会输出到 115200 波特率串口。

网页直接内嵌在应用固件中。Wi-Fi 密码、Token、管理密码只在开发板的 `/config.json` 保存，不编入固件、不在网页回显、不输出串口；编辑时留空保留原值；首次设置管理密码需非空，当前固定存储上限为 64 字节。清除 Wi-Fi 密码需明确勾选无密码网络。保存先写临时文件再原子重命名，未通过校验不改动原配置。

设备 IP 建议设置 DHCP 保留地址；开发板须能访问净水器 UDP 54321（源端口 49152），AP 客户端隔离可能阻止通信。Token 使用你已有的合法本地工具获取；固件不获取 Token、不发送 setter、不复位滤芯、不更改净水器配置。

### OTA 升级与旧版迁移

- 下载 Actions / Release 中的 `xiaomi-purifier-lx7-monitor-nodemcuv2.bin`，打开设备管理网页，在“固件升级”中上传。完成后自动重启，Wi-Fi、Token、显示设置及管理密码都会保留。
- **旧版固件没有 OTA，第一次迁移仍需 USB 刷入本次应用固件**，以后可用网页升级。选择保留文件系统的普通上传方式，不执行整片擦除；原先刷入 LittleFS 的配置会兼容读取，只需通过设置热点补充管理密码。
- OTA 仅写应用区，不提供文件系统上传入口。使用相同 NodeMCU 4MB / 默认 1MB LittleFS 布局的本项目应用，升级时保持供电；固件过大、文件校验失败或上传中断会报告错误。损坏到无法启动、变更 Flash 布局等情况仍需 USB 恢复。
- 当前使用核心自带 WebServer / Updater，无新增 OTA 库；使用独立的密码登录页、Cookie 会话及表单随机校验码，不弹出 Basic / Digest 认证框。会话空闲 30 分钟过期，也可主动退出登录；设备重启后需重新登录。页面为本地 HTTP，配置区没有加密，应只在可信局域网或设置热点使用。

### 重新配网和恢复入口

运行后按住 NodeMCU **FLASH 键 3 秒**，可重新打开设置热点；不要按住 FLASH 再复位，否则会进入芯片下载模式。热点使用每次新生成、只在 OLED 显示的密码，10 分钟后自动关闭。连接设置热点代表具有实体访问权限，可重设管理密码；家庭局域网请求仍需管理密码。

Wi-Fi 连续断开 60 秒也会打开一次设置热点，原连接仍持续重试。忘记管理密码或配错 Wi-Fi 时无需重刷配置。若自定义 OLED 使用了 GPIO0，FLASH 恢复检测会停用以避免引脚冲突。

## 网页布局与主题

桌面使用常驻侧边栏，手机使用抽屉式导航，分为“设备概览”“运行日志”“连接与设置”“固件升级”四个视图。首次配网默认进入设置页；切换视图会保留当前未保存的表单内容，并支持浏览器前进/返回。手机抽屉支持点击遮罩或按 Esc 关闭，打开时会管理键盘焦点。

默认跟随系统的深浅色主题，也可点击右上角的单个主题按钮，按“跟随系统 → 浅色 → 深色 → 跟随系统”循环切换，图标随当前模式变化；登录页同样支持切换。主题偏好只保存在当前浏览器的本地存储，不写入开发板配置。界面全部使用原生 HTML/CSS/JavaScript 与内嵌 SVG，没有第三方前端框架、字体或 CDN，也不需要文件系统镜像。

升级页显示固件上传进度及成功/失败状态。页面切换、抽屉和主题在浏览器中处理；设备信息只在进入概览或手动刷新时查询，日志只在当前日志视图内自动刷新。

## 设备信息与运行日志

管理网页提供 CPU 频率、应用 DRAM 总量、空闲堆、最大连续空闲堆、堆碎片率、物理 Flash 容量、固件大小、OTA 可用空间、文件系统容量/可用空间、运行时间、Wi-Fi 信号和核心版本。设备信息在进入概览时读取一次，也可手动刷新；没有后台采样定时器。

当前 NodeMCU 链接布局为应用 DRAM 分配 80 KiB；“RAM 可用”指核心实时报告的空闲堆，最大连续空闲堆可帮助判断大块内存分配是否可行。Flash 的 OTA 与文件系统可用空间分别显示；OTA 空间按实际升级入口相同的保留与对齐规则计算。文件系统尚未初始化时显示“未初始化”。这些查询仅读取监视器自身状态，不查询净水器。

切换到“运行日志”可查看启动、Wi-Fi 重连、MiIO 通信、配置保存、登录和 OTA 事件。默认每 2 秒刷新，支持暂停和手动刷新；离开日志视图或切到后台会停止自动刷新。日志接口和设备信息接口均使用现有登录会话；自动刷新会保持会话活跃。

日志采用 **2 KiB RAM 环形缓冲**，满后按整行丢弃最旧记录，重启清空，不写入 Flash。时间戳为启动后的秒数。开启 `diagnostics` 时，原始状态及滤芯计数也会同时写入网页日志和串口。日志不记录 Wi-Fi 密码、Token、管理密码、会话 Cookie、表单校验码或热点密码。

## 常用配置

完整存储格式参考 [docs/config.example.json](docs/config.example.json)，**无需复制或刷入此文件**。常用连接信息在网页填写，其余字段可在网页的高级设置中修改。

| 字段 | 默认值 | 说明 |
|---|---|---|
| `poll_interval_ms` | `2000` | 所有工况均继续轮询，范围 500–60000ms |
| `screen_off_delay_ms` | `30000` | 停止状态被观察到后的延时，范围 0–3600000ms |
| `response_timeout_ms` | `1500` | 每个握手/查询的应答等待时间，非阻塞 |
| `stale_after_ms` | `10000` | 数据过期阈值，须 ≥ 轮询间隔 + 2×应答超时 |
| `filter_display` | `"percent"` | `"percent"` 或 `"litres"` |
| `litres_per_flow_unit` | `[0, 0]` | F1/F2 各自每个计数单位对应的升数；0 表示未确认 |
| `activity_source` | `"unverified"` | 下述三种亮屏模式 |
| `making_mask` / `making_value` | `0` / `0` | 仅供实测确认后的位掩码规则使用 |
| `diagnostics` | `false` | 在串口和网页日志输出状态、冲洗及滤芯原始计数，不输出凭据 |
| `oled_address` | `60` | JSON 十进制，60=`0x3c`，61=`0x3d` |
| `oled_sda` / `oled_scl` | `4` / `5` | NodeMCU D2 / D1 |

滤芯寿命**仅用流量**，不读取或使用 `usedtime/totaltime`：

```text
剩余计数 = max(totalflow - usedflow, 0)
剩余百分比 = floor(剩余计数 × 100 / totalflow)
剩余升数 = floor(剩余计数 × litres_per_flow_unit[滤芯下标])
```

`totalflow=0`、缺失或非法计数显示 `--`；百分比限制在 0–100%。升数换算未配置时显示 `--L?`。只有确认计数单位就是升时才设置 `[1, 1]`；不自动除以 2，不把结果声称为“还可生产多少升纯水”。百分比也会受设备计数更新粒度影响。

### 亮屏模式

- `"unverified"`：有正常数据时保持亮屏。推荐先开 `diagnostics`，在自然发生的闲置、制水、冲洗过程中记录状态；固件不会主动制造工况。
- `"flow_change"`：任一滤芯的 `usedflow` 增加且其 `totalflow` 未变化时亮屏，最后一次增加后延迟熄屏。启动及恢复通信时也显示一个延时窗口。**这是近似活动提示**：计数可能分档、延迟或停机更新，可能漏掉短时用水，冲洗是否计数未知；不能保证制水开始立即亮屏或停止后恰好 30 秒熄屏。
- `"run_status"`：仅在确认规则后配置非零 `making_mask`，按 `(run_status & making_mask) == making_value` 判定制水。制水期间常亮，首次观察到非制水状态时启动延时；重复闲置应答不会延长延时。缺失状态则继续亮屏。仓库没有填入任何猜测的 lx7 位值。

一次通信失败即显示异常、隐藏旧数据，持续重试；故障提示维持一个熄屏延时窗口，持续故障不会反复唤醒屏幕。恢复成功后重新显示。Wi-Fi 每 10 秒尝试重连；MiIO 超时、校验失败、RPC 错误会重新握手。错误和原始状态均可从串口观察；OLED 正常界面仅显示 TDS、滤芯余量和温度，已移除 `R`、`UNVERIFIED`、`RINSE` 等诊断标签。配置缺失/无效时进入设置热点，文件系统挂载失败不会自动格式化。

## 结构与测试

```text
MiioCodec + MiioCrypto       MiIO 报文、校验、AES（当前使用核心自带 BearSSL）
MiioClient + Lx7Protocol     UDP 状态机、只读属性请求、严格按请求顺序解析
Controller                  流量寿命、活动判定、数据有效性、屏幕计时
Display → Ssd1306Display     与通信无关的轻量显示接口及 U8g2 实现
Config / ConfigJson          本地持久化、校验、配置更新与旧版兼容
WebManagement / WebPage       设置热点、密码登录页、管理网页及应用 OTA
SessionAuth                  固定大小的内存会话、空闲过期及退出
RuntimeLog / AppLog           有上限的日志缓冲及应用串口输出
main                         Wi-Fi 与各模块的连接
```

更换 ST7789 / ILI9341 时实现 `Display`、选择屏幕尺寸/方向并替换实例即可，通信逻辑不变。升级 ESP32 还需选定开发板、增加 PlatformIO 环境，替换 Wi-Fi 入口及 `MiioCrypto` 平台实现；本仓库不声称已经编译验证未指定的 ESP32/彩屏组合。

固件编译后，可在 Linux 使用 `g++` 和 OpenSSL 开发库运行：

```sh
bash tests/run.sh
```

主机测试启用 ASan/UBSan，覆盖日志滚动/截断/分段读取、短密码、Cookie 解析、会话过期/退出及配置迁移、秘密字段脱敏、留空保留原值、非法配置拒绝及固定 MiIO 报文向量、损坏/超长报文、错误来源、旧应答 ID、超时重握手、字段空值、流量钳位、故障恢复、熄屏计时和 `millis()` 回绕。主机使用模拟 UDP/OpenSSL 后端；ESP8266 的真实 Wi-Fi、OTA 重启后配置保留、BearSSL 运行及 OLED 接线仍需实物验证。

## CI 与发布

每次 push（包括 tag）、PR 及手动触发均编译和测试，上传应用 `.bin` 和 `SHA256SUMS`。推送任意 tag 会在构建通过后创建 GitHub Release 并附上相同文件，不上传配置或文件系统镜像。例如自行确定版本后执行 `git tag v0.1.0 && git push origin v0.1.0`；本次开发不会自动创建 tag。

依赖已在 2026-11-07 核对并锁定：PlatformIO 6.2.0、Espressif8266 4.2.1（官方最新稳定平台，捆绑 Arduino core 3.1.2）、U8g2 2.37.1（上游实际版本提交 `b3a40de`，固定完整 SHA；Registry 的 2.36.18 滞后，上游 2.37.1 标签指向的提交仍标 2.36.19）、ArduinoJson 7.4.3。Actions 使用最新稳定版本对应 SHA：checkout 7.0.1、setup-python 7.1.0、upload-artifact 7.0.2、action-gh-release 3.0.4；runner 明确指定已 GA 的 `ubuntu-26.04`，不用 `ubuntu-latest`。Python 选择稳定 3.15 系列。Dependabot 跟踪 Actions/Python 依赖；PlatformIO 平台和库升级需手动核对并重编译。
