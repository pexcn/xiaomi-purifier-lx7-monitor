# 小米净水器 OLED 监视器

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

默认 7 位地址 `0x3c`，可配置为 `0x3d`。配置中的引脚是 GPIO 编号。使用 U8g2 单页缓冲（128 字节），屏幕使用英文短标签，避免加载中文字库。`IN/OUT` 为 TDS，`F1` 为复合滤芯，`F2` 为 RO，`R` 为十六进制原始 `run_status`，`RINSE` 为原始冲洗字段，`--` 表示字段不可用。

## 配置、编译与烧录

需要 Python 3.10+、PlatformIO 和 USB 串口驱动。建议使用独立虚拟环境：

```sh
python3 -m venv .venv
# Linux/macOS；Windows 使用 .venv\Scripts\activate
. .venv/bin/activate
python -m pip install -r requirements.txt
cp data/config.example.json data/config.json
# 在本地编辑 data/config.json，填入 Wi-Fi、净水器 IPv4 和 32 位十六进制 Token
pio run -e nodemcuv2
pio run -e nodemcuv2 -t upload
pio run -e nodemcuv2 -t uploadfs
pio device monitor -b 115200
```

`uploadfs` 会替换此开发板上的 LittleFS 内容，配置修改后需重新上传并重启；配置不会写入净水器。可通过 `--upload-port` 选择串口。默认 4MB NodeMCU 布局无需额外分区配置。

`data/config.json` 已被 Git 忽略。凭据只存在开发板 LittleFS，不编入应用固件，不在串口输出。不要提交配置、发布文件系统镜像或上传构建目录；LittleFS 没有加密，拿到开发板的人可能读取配置。CI 不需要任何净水器凭据。Release 的 `.bin` 只包含应用，首次使用仍须上传本地配置文件系统。

设备 IP 建议设置 DHCP 保留地址；开发板须能访问净水器 UDP 54321（源端口 49152），AP 客户端隔离可能阻止通信。Token 由你已有的合法本地工具获取；此固件不获取 Token、不发送 setter、不复位滤芯、不更改净水器配置。

## 常用配置

完整示例在 [data/config.example.json](data/config.example.json)，除四项连接信息外其余可省略。

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
| `diagnostics` | `false` | 输出时间、状态、冲洗及滤芯原始计数，不输出凭据 |
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

- `"unverified"`：有正常数据时保持亮屏，显示 `UNVERIFIED` 和原始状态。推荐先开 `diagnostics`，在自然发生的闲置、制水、冲洗过程中记录状态；固件不会主动制造工况。
- `"flow_change"`：任一滤芯的 `usedflow` 增加且其 `totalflow` 未变化时亮屏，最后一次增加后延迟熄屏，显示 `FLOW~`。启动及恢复通信时也显示一个延时窗口。**这是近似活动提示**：计数可能分档、延迟或停机更新，可能漏掉短时用水，冲洗是否计数未知；不能保证制水开始立即亮屏或停止后恰好 30 秒熄屏。
- `"run_status"`：仅在确认规则后配置非零 `making_mask`，按 `(run_status & making_mask) == making_value` 判定制水。制水期间常亮，首次观察到非制水状态时启动延时；重复闲置应答不会延长延时。缺失状态则显示 `UNVERIFIED`。仓库没有填入任何猜测的 lx7 位值。

一次通信失败即显示异常、隐藏旧数据，持续重试；故障提示维持一个熄屏延时窗口，持续故障不会反复唤醒屏幕。恢复成功后重新显示。Wi-Fi 每 10 秒尝试重连；MiIO 超时、校验失败、RPC 错误会重新握手。错误和原始状态均可从串口观察；配置缺失/无效时不连接网络、不自动格式化文件系统。

## 结构与测试

```text
MiioCodec + MiioCrypto       MiIO 报文、校验、AES（当前使用核心自带 BearSSL）
MiioClient + Lx7Protocol     UDP 状态机、只读属性请求、严格按请求顺序解析
Controller                  流量寿命、活动判定、数据有效性、屏幕计时
Display → Ssd1306Display     与通信无关的轻量显示接口及 U8g2 实现
Config / main               独立配置及 Wi-Fi、各模块的连接
```

更换 ST7789 / ILI9341 时实现 `Display`、选择屏幕尺寸/方向并替换实例即可，通信逻辑不变。升级 ESP32 还需选定开发板、增加 PlatformIO 环境，替换 Wi-Fi 入口及 `MiioCrypto` 平台实现；本仓库不声称已经编译验证未指定的 ESP32/彩屏组合。

固件编译后，可在 Linux 使用 `g++` 和 OpenSSL 开发库运行：

```sh
bash tests/run.sh
```

主机测试启用 ASan/UBSan，覆盖固定 MiIO 报文向量、损坏/超长报文、错误来源、旧应答 ID、超时重握手、字段空值、流量钳位、故障恢复、熄屏计时和 `millis()` 回绕。主机使用模拟 UDP/OpenSSL 后端；ESP8266 的真实 Wi-Fi、BearSSL 运行及 OLED 接线仍需实物验证。

## CI 与发布

每次 push（包括 tag）、PR 及手动触发均编译和测试，上传应用 `.bin` 和 `SHA256SUMS`。推送任意 tag 会在构建通过后创建 GitHub Release 并附上相同文件，不上传配置或文件系统镜像。例如自行确定版本后执行 `git tag v0.1.0 && git push origin v0.1.0`；本次开发不会自动创建 tag。

依赖已在 2026-11-07 核对并锁定：PlatformIO 6.2.0、Espressif8266 4.2.1（官方最新稳定平台，捆绑 Arduino core 3.1.2）、U8g2 2.36.18、ArduinoJson 7.4.3。Actions 使用最新稳定版本对应 SHA：checkout 7.0.1、setup-python 7.1.0、upload-artifact 7.0.2、action-gh-release 3.0.4；runner 明确指定已 GA 的 `ubuntu-26.04`，不用 `ubuntu-latest`。Python 选择稳定 3.15 系列。Dependabot 跟踪 Actions/Python 依赖；PlatformIO 平台和库升级需手动核对并重编译。
