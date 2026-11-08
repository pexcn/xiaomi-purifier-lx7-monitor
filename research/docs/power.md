# 轮询、低功耗与 MCU 唤醒

分析日期：2026-11-08。**本页的固件结论仅针对仓库 1.3.9 Wi-Fi 样本**；用户实机报告 2.1.3 / MCU 0012，不能直接等同。未提供主控 MCU 镜像，未操作设备或测量功耗、寿命。

## 结论

| 问题 | 状态与结论 |
|---|---|
| 普通 get_prop 是否等同于 miIO.wake_up_mcu？ | **已证实（已恢复的旧版路径）**：不同。前者进入 MCU 下行队列；后者创建定时器，回调操作 GPIO bit 5。普通桥接路径没有调用该显式唤醒代码 |
| set_low_power 是否控制主控 MCU 睡眠？ | **已证实（旧版调用范围）**：处理器调用 Wi-Fi SDK 侧睡眠控制，未调用显式 MCU 唤醒函数；它不是已恢复的 MCU 睡眠状态 getter |
| Wi-Fi 是否默认一直全速工作？ | **不能这样推断**。找到初始化睡眠使能标志为 1、类型为 2；只确认配置，不证明实际进入睡眠、睡眠占比或主控状态 |
| 普通查询能否让 MCU 保持唤醒？ | **待验证**。没有走显式 GPIO 唤醒，不代表串口收发不会让 MCU 退出休眠或重置空闲计时 |
| 全天轮询是否缩短净水器寿命？ | **未测量**。已恢复桥接路径没有水泵/阀门控制或滤芯 Flash 写入；预计低频只读查询主要增加通信及处理器活动，但不能替代当前 MCU 的实现和功耗证据 |

## REA 与证据范围

本次优先尝试 `rea function work/extracted/lx7-analysis.elf 0x4024ca4c --format json`。REA 6.8.0 返回 `unsupported ELF architecture`，见 [原始失败记录](evidence/power/rea-function-rejection.json)；没有通过 REA 完成该函数的反编译。

改用 Ghidra 12.1.4、`Xtensa:LE:32:default` 和 [ExportFunctions.java](../scripts/ExportFunctions.java)，对已有分析工程中的准确入口导出 C、调用、入口引用和指令。哈希与来源见 [provenance.json](evidence/power/provenance.json)；[完整所选指令](evidence/power/instructions.txt)用于核对返回值、寄存器和字面量。C 中 void 返回值、间接调用和可变参数仍有自动推断局限，不能直接作为厂商源码。

## 普通属性查询：排队，不调用显式 GPIO 唤醒

旧样本的 get_prop 未注册本地处理器，走以下通用路径，详见 [usedflow 静态追踪](usedflow.md#静态追踪)：

```text
网络分发：FUN_402488F4 / FUN_40245E6C
  → FUN_4024C4F4
  → FUN_4024C2D8
  → FUN_4024CBFC：复制请求到 RAM，加入 MCU 下行队列

MCU 发来 get_down / json_get_down
  → FUN_4024B89C / FUN_4024B278：取队列请求
  → FUN_4024E0C0 → FUN_40244068 → FUN_402571C8：串口发送
```

`FUN_4024CBFC` 检查排队数小于 8，分配 RAM、保存请求与回调，再调用队列包装器 `FUN_40241F94`。失败可返回 queue full/一般错误。不能把这个队列长度当成推荐并发数；监测应一次完成一个查询，超时退避。

这些已恢复函数没有调用下面的 `FUN_4023FC10`、`FUN_4023D8B0` 或 GPIO 写寄存器函数 `FUN_40208670`。静态入口引用也仅发现显式唤醒处理器将该回调注册给定时器；这限定了当前分析结果，不能排除未知间接行为或 MCU 自身的串口唤醒。

证据：上述同名 [反编译 C](evidence/decompiled/)；[普通路径调用表](evidence/power/power-calls.tsv)、[GPIO 函数引用](evidence/power/power-sdk-entry-references.tsv)。

## 显式 miIO.wake_up_mcu：定时 GPIO 序列

| 函数 VA / 原文件偏移 | 已确认行为 |
|---|---|
| `FUN_4023FC10` / `0x3EC10` | 先应答，创建名为 weak_up_timer 的定时器，周期参数 `0x32`、回调 `FUN_4023D8B0`，再提交定时器命令 |
| `FUN_4023D8B0` / `0x3C8B0` | 配置 mask=`0x20`，即 bit 5；通过 GPIO 接口依次输出低、高、低，最后禁用该 bit 的输出；两次延时参数均为 10 |
| `FUN_40208670` / `0x7670` | 四个参数依次写入 GPIO 置位、清零、输出使能置位/清零寄存器 `0x60000304/308/310/314` |

原始调用参数如下；这是从指令整理的说明，不是厂商源码：

```text
GPIO(mask): (set, clear, enable, disable)
(0, 0x20, 0x20, 0)
delay(10)
(0x20, 0, 0x20, 0)
delay(10)
(0, 0x20, 0x20, 0)
(0, 0, 0, 0x20)
```

未将定时/延时参数换算成毫秒；尚未独立核对调度 tick 周期。也未验证实物 GPIO5 与主控的连线、电平有效含义或 MCU 侧响应。方法名与序列支持“显式 MCU 唤醒”的用途，不支持“每次 get_prop 都产生此序列”的说法。本次未调用该方法。

证据：[4023fc10.c](evidence/decompiled/4023fc10.c)、[4023d8b0.c](evidence/decompiled/4023d8b0.c)、[40208670.c](evidence/decompiled/40208670.c)、[入口引用](evidence/power/power-entry-references.tsv)。

## set_low_power 与默认配置

`set_low_power` 是 MCU→Wi-Fi 串口命令，不是已确认可直接发送的同名 MiIO 方法。处理器 [FUN_4024CA4C](evidence/decompiled/4024ca4c.c)（文件 `0x4BA4C`）：

- `on`：检查 `FUN_40204820` 返回值为 1，才调用 `FUN_402062F8(2)`；否则回复 error。前者从 Wi-Fi 配置的模式字节取值，不能当作 MCU 睡眠检测。
- `off`：调用 `FUN_402062F8(0)`。
- 调用后回复 ok，但不核验实际硬件睡眠是否成功，也没有读取 MCU 电源状态。

SDK 包装器 [FUN_402062F8](evidence/decompiled/402062f8.c)（文件 `0x52F8`）接受小于 3 的参数并调用 [FUN_40219750](evidence/decompiled/40219750.c)（`0x18750`）。后者操作睡眠配置：

| 参数/路径 | RAM 与日志证据 |
|---|---|
| 0 | `0x3FFEB63A=0`、`0x3FFEB638=0`，日志 sleep disable |
| 非零 | 将 `0x3FFEB63A` 设为 1，日志 sleep enable；类型 1/2 进一步更新 `0x3FFEB638` |
| 类型切换到 2 的分支 | 包含 `light sleep is not supported now` 日志，随后仍更新内部状态；不能只看 ok 或配置值就担保实际睡眠能力 |

初始化链 `FUN_402021C8 → FUN_4021A810` 中，后者（文件 `0x19810`）写 `0x3FFEB638=2`、`0x3FFEB63A=1`。读取函数 [FUN_402197FC](evidence/decompiled/402197fc.c)（`0x187FC`）恰好在使能标志为 1 时返回类型，否则返回 0，交叉印证这两个字段的关系。

**已确认的是旧版 Wi-Fi SDK 初始化的配置**。运行中可由串口命令等路径改变；不能据此给当前实机定默认值，也不能把类型值当作主控 MCU 或水泵状态。SDK 的实际睡眠入口、网络负载导致的睡眠占比，以及当前 2.1.3 的实现未完整恢复。

## 是否推荐持续轮询？

**建议**：以寿命与低干扰优先，不为了不可靠的 TDS 制水判据全天秒级轮询。若只需水质/历史监测，可先选择 30–60 秒或更长间隔；研究计数跳变时再短时间提高采样频率。间隔是工程折中建议，不是通过寿命试验得到的安全阈值。

低频只读查询预计不会显著增加水泵、阀门的机械磨损；现有证据不能量化 MCU 额外功耗、温升或多年寿命差异。既没有发现“每次查询都刷写滤芯存储”的证据，也不能据缺少 MCU 镜像保证其属性处理绝无写操作。不要为降低这点不确定性去调用 set_low_power、wake_up_mcu 或重启。

无需拆机的验证：在用户正常闲置、供电和网络条件相近的区间，对比无外部查询与固定低频查询时的平均功率；记录自然制水/冲洗，排除这些区间及 App 同时轮询的干扰。有现成能耗计则可进行；本次没有执行。查询时延和持续在线本身都不能证明 MCU 是否休眠。

## 复现关键函数导出

先按 README 建立 Ghidra 分析工程、配置 JDK 和 GHIDRA_INSTALL_DIR，然后在仓库根目录运行。此命令只打开本地分析工程，不连接设备。

```sh
export XDG_CONFIG_HOME="$PWD/work/config" XDG_CACHE_HOME="$PWD/work/cache"
export JAVA_TOOL_OPTIONS="-Duser.home=$PWD/work/ghidra-home"
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" work/ghidra-project lx7 \
  -process lx7-analysis.elf -noanalysis -scriptPath scripts \
  -postScript ExportFunctions.java work/evidence/power-review \
  4023fc10 4023d8b0 40208670 4024ca4c 402062f8 40219750 4021a810 402197fc
```

完整 25 项函数及其来源哈希记录在 provenance.json；额外引用表还保留辅助函数的交叉引用，不代表所有 SDK 间接调用已穷举。
