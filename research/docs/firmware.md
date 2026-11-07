# 环境与固件识别

## 实机版本核对

**已证实（用户实测）**：用户提供的 `miIO.info []` 报告如下版本字段，脱敏摘录保存在 [runtime-version.json](evidence/runtime-version.json)：

| 字段 | 当前设备报告 |
|---|---|
| `model` | `yunmi.waterpuri.lx7` |
| `hw_ver` | `esp8266` |
| `fw_ver` | `2.1.3` |
| `mcu_fw_ver` | `0012` |
| `wifi_fw_ver` | `8903c22` |
| `miio_ver` | `0.0.9` |

**已证实（静态）**：仓库样本的 [FUN_402409EC](evidence/decompiled/402409ec.c)（原文件 `0x3F9EC`）生成 `fw_ver`，取固定字符串 `1.3.9`（原文件 `0x6D730`）；`FUN_40240F28` 调用该函数。因此样本与当前实机报告的应用版本不同，不能称为当前运行的 `2.1.3` 固件。

**推测**：米家显示的 `2.1.3.0012` 是 `fw_ver` 与 `mcu_fw_ver` 的组合，两段与此次读数精确对应；未检查米家插件的显示代码。`wifi_fw_ver` 是另一个版本标识，不应代替 `fw_ver` 比较应用版本。旧样本中该字段由 `FUN_40240D94 → FUN_40206EA8` 生成，返回 SDK 字符串 `1.5.0-dev(7efd021)`（原文件 `0x6DB6C`），不是固定应用版本 `1.3.9`。

此前的桥接实现、16 项委托、30 项串口命令及所有 VA/偏移仅针对 **1.3.9 样本**。当前 `2.1.3 / MCU 0012` 是否沿用相同框架、属性限制或存储逻辑均待验证。需要另行取得 `2.1.3` Wi-Fi 镜像及匹配的 `0012` MCU 镜像；尚未获取这两份文件，不把旧版反编译当成当前实现。

本次仅人工摘录型号和版本白名单；不保存原始 info 响应中的 Token、账号、MAC、SSID/BSSID 或网络地址。此次响应由用户读取提供，本分析未主动访问设备。

## 样本与工具

| 项目 | 结果/证据 |
|---|---|
| 原始文件 | `firmware/yunmi.waterpuri.lx7-1.3.9.bin`，456872 字节（`0x6F8A8`） |
| SHA-256 | `f20d634664918a9e5ab483774c1fd3b80afae2bfd6a5416619a56aaa1093a1c5` |
| CPU/平台 | ESP8266，Xtensa 32 位小端；`0x28FD0` 字符串 `Firmware ONLY supports ESP8266!!!`；Ghidra 用 `Xtensa:LE:32:default`，可解出 `call0`/`l32r` |
| SDK 标记 | 文件 `0x29010`：`OS SDK ver: 1.5.0-dev(7efd021) compiled @ Oct 19 2018 17:39:04`；这是 SDK 标记，不是整份产品固件构建日期 |
| Wi-Fi 版本 | 文件 `0x6D730`：`1.3.9` |
| REA | 6.8.0；doctor 确认 Ghidra 可用。总体 unhealthy 另含缺 Hopper/IDA 等及未安装 REA skill，不能据此说 REA 全部失效 |
| Binwalk / Unblob | 3.1.0 / 26.6.4；REA 签名扫描及指定 IROM 区间提取尝试完成，后者为 partial、无产出文件 |
| Ghidra / Java | 12.1.4 / OpenJDK 21.0.13；直接 headless 导入合成 ELF 并导出 C |

REA `inspect-firmware-regions` 使用 Binwalk 成功，报告 AES/SHA/CRC 表和 PEM 证书等候选；它们不是文件系统证据。`extract-firmware --offset 16 --length 414304` 经 Unblob 返回该范围 `unclassified-range`，不能宣称成功解包。保留的结构化结果见 [tool-runs.json](evidence/tool-runs.json)。

REA 深度分析有两次明确限制：[原始封装拒绝](evidence/rea-original-rejection.json)为 `unsupported binary format`；[合成 ELF 拒绝](evidence/rea-xtensa-rejection.json)为 `unsupported ELF architecture`。其 raw-binary CLI 架构选项也不包含 Xtensa。因此改用直接 Ghidra，而非声称通过 REA 完成反编译。完整尝试日志保留在本地 `work/evidence/`。

## 镜像结构：已证实

头部 `EA 04 00 50 04 00 10 40`，入口 `0x40100004`。`0x8` 处为地址 0、长度 `0x65260` 的 IROM 包装段；`0x65270` 处另有 `E9 03 00 50 04 00 10 40` 及三个装载段。SPI 字段原始值为 mode=0、size/frequency=`0x50`，不据此确认实物 Flash 容量。

| 区域 | 原文件偏移（起点） | 长度 | 分析虚拟地址（起点） |
|---|---:|---:|---:|
| IROM | `0x10` | `0x65260` | `0x40201010` |
| IRAM | `0x65280` | `0x7AF8` | `0x40100000` |
| DRAM 初始化段 1 | `0x6CD80` | `0xC80` | `0x3FFE8000` |
| DRAM 初始化段 2 | `0x6DA08` | `0x1E8C` | `0x3FFE8C80` |

RAM 数据结束于 `0x6F894`（不含），ESP 填充后 `0x6F89F` 校验字节为 `0xC7`，以 `0xEF` 为初始值对三个 RAM 段逐字节 XOR 得到同值。其后 8 字节用途未确认。该校验不是签名或设备型号认证。

IROM 地址采用 `0x40200000 + 0x1000 + 文件偏移`。这是装载槽位假设，得到的绝对调用、literal pool 和表指针相互吻合：

- `0x6D934` 存储 `json_get_down` 处理器指针 `0x4024B278`；其映射到原文件 `0x4A278`，Ghidra 能恢复函数。
- 该函数的 `l32r` 引用 `0x4024B26C`，原文件 `0x4A26C` 的字为 `0x3FFEA3F2`，按 DRAM 段映射精确指向原文件 `0x6F17A` 的 `json_down none`。
- 多项网络分发函数和串口表均在该映射下可连贯交叉引用。RAM 地址则直接来自 E9 段头。

地址换算及校验见 [image-map.json](evidence/image-map.json) 和 [prepare_image.py](../scripts/prepare_image.py)。对 IROM，本文函数文件偏移为 `VA - 0x40201000`。其他段须用表换算，不能套用同一差值。

## Wi-Fi 与主控 MCU 的边界

**已证实**：Wi-Fi 有网络、PSM、OTA 和串口命令框架。`FUN_4024CE54` 注册 `miIO` 15 项委托和 `user` 1 项委托；见 [C](evidence/decompiled/4024ce54.c)。MCU 可以通过串口 `model` 提供/修改运行时型号，`mcu_version` 提供版本，见 `FUN_4024C6B0`、`FUN_4024C808`。默认 PSM 型号回退是 `xiaomi.dev.lx1`，见 [FUN_40257360](evidence/decompiled/40257360.c)。文件名和用户说明将样本关联 lx7，镜像内容本身不独立认证 MR532-D。

**已证实**：OTA 处理器分别读取 `app_url` 和 `mcu_url`，见 [FUN_40243100](evidence/decompiled/40243100.c)。存在 MCU OTA 能力不代表样本包含 MCU 固件。

**已证实的覆盖边界**：已提供的二进制仅该 bin；镜像各段已按上表解释，未识别出独立 MCU 镜像或文件系统。不能用 Binwalk 的阴性结果证明绝无未知嵌入数据；主控芯片型号、主控代码、传感器驱动及滤芯记录格式仍缺失。

因此，“尚未恢复主控 MCU 的算法”是分析覆盖范围的描述，不等于证明文件每一处未知数据都不可能包含 MCU 内容。现有证据支持该文件主要是 Wi-Fi 镜像；主控算法的位置仍属待验证范围。

**推测**：设备专用水务逻辑位于外部 MCU。依据是通用桥接调用链、动态属性上报、型号由 MCU 设置，且 ASCII/UTF-16 检索未找到 `usedflow/get_prop/tds_warn_thd/lightMode`。这不是对未提供 MCU 镜像的逆向结论。

### 主控镜像的识别线索

继续静态追踪后，已确认 **1.3.9 样本具有 MCU 镜像缓存和串口传输路径**。这不是 MCU 应用算法本身，也不证明当前设备仍有完整缓存。以下均来自旧样本，不能直接套用到实机 2.1.3。

| 证据函数 | 已确认内容 |
|---|---|
| [FUN_40242EE8](evidence/decompiled/40242ee8.c) | 分别处理应用和 MCU 的地址参数，支持 MCU 单独更新或两组件先后更新 |
| [FUN_4024268C](evidence/decompiled/4024268c.c)、[FUN_402421E0](evidence/decompiled/402421e0.c) | MCU 缓存初始化路径把两个候选基址均设为 `0x181000`；这是 ESP Flash 地址，不是 OTA 文件偏移 |
| [FUN_40242D58](evidence/decompiled/40242d58.c) | 从缓存基址读 8 字节头，核对魔数 `0x584C4655`（小端字节为 `UFLX`），第二个 32 位字段用作载荷长度 |
| [FUN_402436E4](evidence/decompiled/402436e4.c)、[FUN_40242CA4](evidence/decompiled/40242ca4.c) | 缓存布局为 8 字节头、载荷、4 字节校验值；校验覆盖载荷。日志称 CRC32，精确 CRC 参数尚未独立验证 |
| [FUN_402429CC](evidence/decompiled/402429cc.c)、[FUN_40242850](evidence/decompiled/40242850.c) | 与 MCU 握手后，从缓存头之后读取载荷，通过 XMODEM 相关调用传输，分块参数为 128 字节；没有执行该路径 |
| [FUN_4024270C](evidence/decompiled/4024270c.c)、[FUN_4023F928](evidence/decompiled/4023f928.c) | 成功传输后调用按 4KB 扇区传参的缓存清理路径；底层动作尚未独立验证，不能假定更新后仍保留完整镜像 |

对当前 bin 搜索 `UFLX`，只有原文件 `0x41D4C` 的程序常量一处，没有另一个可识别的缓存头。应用 OTA 文件与整片 ESP Flash 备份是不同资料；若已有整片备份，可先离线检查有无有效头、合理长度和完整载荷，不能仅凭魔数认定镜像有效。

获取主控代码的优先顺序：已有独立 MCU 文件；已有整片 ESP Flash 备份中的有效缓存；最后才是根据实物 MCU 型号制定只读读出方案。尚无主控型号时不猜测调试接口、引脚或读出命令，也不为抓固件触发更新。整片备份可能含配网和设备凭据，应仅在本地忽略目录处理，不提交仓库。

拿到主控载荷后，先识别封装、架构和装载地址，再追踪串口属性处理、流量采样、24/10 分档、滤芯记录保存及复位调用链。Wi-Fi 更新器提供的是查找和搬运线索，不能代替上述主控实现证据。

## 证据使用

[interfaces.json](evidence/interfaces.json) 来自对原文件函数表的直接解析，包含每项表偏移、字符串偏移、函数 VA 和文件偏移。`scripts/inventory.py` 先校验固定 SHA-256，避免将旧偏移套到别的版本。

[decompiled/](evidence/decompiled/) 是 Ghidra 的真实输出，仅去除行末空格和尾部空行，保留语句、签名及 `FUN_`/`DAT_` 自动名称。Xtensa 返回值和 varargs 部分被推断为 `void` 或缺少参数；不可将其当成可编译源码。关键分发/串口指令摘录在 [bridge-calls.txt](evidence/bridge-calls.txt)，对照实际 `call0`、`callx0`、`l32r` 使用。未执行固件代码。
