# MR532-D / yunmi.waterpuri.lx7 固件分析

目标设备由用户提供：小米净水器 500G 增强版，MR532-D。分析日期：2026-11-07。

## 当前结论

- **已证实（用户实测）**：设备当前报告 `fw_ver=2.1.3`、`mcu_fw_ver=0012`；与仓库样本 `1.3.9` 不同。固件函数地址和本地委托表属于旧样本，不能直接作为当前固件实现的证据；插件证据独立标注，详见 [版本核对](docs/firmware.md#实机版本核对)。
- **已证实**：样本是 ESP8266 / Xtensa 小端 Wi-Fi OTA 镜像，内嵌版本 `1.3.9`；RAM 段 XOR 校验通过。未识别出文件系统或独立主控 MCU 镜像。
- **已证实**：还原 15 项 `miIO` 本地委托、1 项 `user` 委托和 30 项 MCU→Wi-Fi 串口命令。未命中本地处理器的 JSON 方法转入 MCU 下行队列。
- **已证实**：桥接层复制请求、封装 MCU 返回值，不按滤芯或水量进行运算。`miIO.info` 的 `life` 来自运行计时，不能当作滤芯寿命。
- **待验证**：F1/F2 `usedflow` 的原水/纯水口径、单位、脉冲公式、保存和复位规则。当前没有设备主控代码或原始传感器数据，不能回答这些问题。
- **已证实（用户实测）**：该数组依次为 F1/F2 usedtime、F1/F2 usedflow、F1/F2 totaltime、F1/F2 totalflow；两个 totalflow 都是 7200。单位及 3600L/7200L 差异仍未证实，不能据倍数认定纯废水比。
- **已证实（用户实测）**：用户自行重置后、不足 24 小时且仅取用几升水时，后续读数为 `[24,24,10,10,8640,17280,7200,7200]`。时间/流量可能按 24/10 分档；插件已支持时间按小时解释，实际步长、流量单位和取整规则仍待验证。
- **已证实（插件）**：上传包声明对应 lx7，型号映射版本 75。插件按小时解释时间，以时间余量算滤芯百分比；所查显示链未使用 usedflow。10 流量档、原水/纯水口径及 3600L/7200L 差异仍未解决。

## 文档

| 文件 | 内容 |
|---|---|
| [docs/firmware.md](docs/firmware.md) | 环境、镜像结构、地址映射和 REA 限制 |
| [docs/usedflow.md](docs/usedflow.md) | 流量统计证据、结论边界、只读验证方案 |
| [docs/miio-api.md](docs/miio-api.md) | MiIO、串口接口、参数及风险 |
| [docs/plugin.md](docs/plugin.md) | lx7 插件格式、寿命公式、历史水量与隐藏设置 |
| [docs/evidence/](docs/evidence/) | 表解析、SHA-256、精选真实反编译输出 |
| [scripts/](scripts/) | 只读解析和 Ghidra 导出脚本 |

`FUN_地址` 是 Ghidra 自动命名；文中的功能说明是分析标签，不是恢复的厂商源码符号。证据保留的 C 输出含自动类型推断错误，应结合原始地址及调用指令复核。

## 复现

需要 Python 3、Ghidra 12.1.4、JDK 21；REA 6.8.0、Binwalk 3.1.0、Unblob 26.6.4 用于工具检查和签名/解包尝试。

```sh
python3 scripts/prepare_image.py firmware/yunmi.waterpuri.lx7-1.3.9.bin work/extracted
python3 scripts/inventory.py firmware/yunmi.waterpuri.lx7-1.3.9.bin > work/interfaces.json
# 设置 GHIDRA_INSTALL_DIR、JAVA_HOME，并将 java 加入 PATH 后：
bash scripts/run_ghidra.sh
```

`work/extracted/lx7-analysis.elf` 是脚本合成的分析容器，不是厂商 ELF，也不可用于刷机。IROM 采用 flash 槽位 `0x1000` 的映射，依据见格式文档。

原始固件与插件只读分析，未执行插件、运行固件或操作设备。新提取的二进制、Ghidra 工程和临时日志保存在忽略的 `work/`；不提交固件副本、原始插件包、Token 或账号凭据。
