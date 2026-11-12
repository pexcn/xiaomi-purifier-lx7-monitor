# MiIO 接口核实与证据边界

核对日期：2026-11-08。以下区分仓库内研究证据与用户提供的本项目实机日志；开发环境未直接连接设备。

主要来源：[研究历史 `88e7082`（原 `2843776`）](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/tree/88e70822c2d332993b11e196cdba90cd8c76ca03/research)。其旧 Wi-Fi 固件样本是 **1.3.9**，研究记录中的用户设备为 **2.1.3 / MCU 0012**，二者不可混为当前实现证据。lx7 插件的型号映射版本 75 是另一组版本信息。

| 接口/字段 | 已确认的证据 | 本项目处理/待验证 |
|---|---|---|
| `get_prop`，参数为属性名字符串数组 | 研究资料记录的用户八字段查询成功；lx7 插件调用 15 字段；用户本项目日志已输出有效状态及滤芯计数 | 仅发送只读请求；用户反馈显示数据看起来正确，尚未提供完整原始应答用于逐项核对 |
| `tds_in` / `tds_out` | 插件请求并解释为进/出水 TDS，UI 使用 mg/L、文案使用 ppm | 显示设备值；本机采样周期、校准与现场可读性待验证 |
| `temperature` | 插件读取并标记为 ℃ | 显示数值；缺失显示 `--` |
| `f1_usedflow` / `f2_usedflow` | 用户请求返回过 0、10；插件也读取 | 仅作为累计流量计数，不补造更新时间或计量水路 |
| `f1_totalflow` / `f2_totalflow` | 用户设备都返回 7200；插件也读取 | 从设备读取，不硬编码额度；不推断 7200/3600 的关系 |
| `run_status` | 插件读取并按标志处理异常；lx7 的 bit15 有泵热保护文案 | **未确认制水位/枚举**；不以非零判定制水 |
| `rinse` | 插件将 1 解释为冲洗 | 不是制水属性，也不据此推断完整工况枚举 |
| `usedtime` / `totaltime` | 插件按时间计算百分比 | 用户要求按流量计算，本项目完全不请求这些字段 |
| `miIO.info.life` | 旧样本来自运行 tick | 不用作滤芯寿命，也不请求可能含敏感信息的 `miIO.info` |

详见迁入后固定研究版本的 [接口表](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/blob/88e70822c2d332993b11e196cdba90cd8c76ca03/research/docs/miio-api.md)、[插件证据](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/blob/88e70822c2d332993b11e196cdba90cd8c76ca03/research/docs/plugin.md)、[状态证据](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/blob/88e70822c2d332993b11e196cdba90cd8c76ca03/research/docs/evidence/operating-state.md)及 [流量口径](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/blob/88e70822c2d332993b11e196cdba90cd8c76ca03/research/docs/usedflow.md)。

本项目请求顺序固定如下，返回数组严格逐项对应，不能套用插件不同顺序的数组：

```json
{"id":1,"method":"get_prop","params":["tds_in","tds_out","temperature","f1_usedflow","f1_totalflow","f2_usedflow","f2_totalflow","run_status","rinse"]}
```

缺失字段、`null`、负计数、布尔值不会被转换为 0。计数兼容 JSON 无符号整数与严格十进制数字字符串；温度接受 JSON 数值。数组长度、RPC `id` 和 `error` 均检查；某个字段不可用显示 `--`，整个结果无有效监测字段时报告错误。遇到未知字段/不支持查询不尝试 setter 或猜测新属性。

## 传输

通用 LAN MiIO 封装核对自 [`python-miio@9a00e08/miio/protocol.py`](https://github.com/rytilahti/python-miio/blob/9a00e0888ef85f8d8d84888cabd9e46d1b0a18df/miio/protocol.py)：UDP 54321，`0x2131`、大端长度/DID/时间戳、32 字节头；16 字节 Token，`key=MD5(token)`、`iv=MD5(key+token)`；JSON 含 NUL 后作 PKCS#7 填充，AES-128-CBC；校验为 `MD5(header[0:16]+token+ciphertext)`。

握手为 `21310020` 后接 28 字节 `ff`。响应提供 DID 和设备时间，握手本身不认证；**不学习响应中的 Token**，后续加密数据必须通过预配置 Token 校验。只接受配置 IP/端口的应答，检查长度、DID、校验、填充及请求 ID；768 字节上限，单个在途请求，非阻塞等待。异常后重新握手，每小时刷新设备时间基准，无需 NTP。

以上是传输实现依据。用户提供的本项目诊断日志表明其设备已接受查询并返回可解析数据；这不保证其他固件或网络环境具有相同的 LAN 访问策略，也不证明所有字段的计量语义。

## 自动亮屏的限制

用户最初回忆闲置和制水时 `run_status/rinse` 均为 0，随后再次测试报告“不变化”，并提供本项目诊断日志：启动后 `23.669` 至 `91.258` 秒，约 68 秒内所有记录均为：

```text
INFO run_status=0 rinse=0 f1=10/7200 f2=10/7200
```

日志没有标注具体开关水时刻或同时读取的固件版本，不能据此建立完整工况时序；冲洗仍未验证。但这次采样没有可供实时亮灭屏使用的状态或计数变化，不能将 0 判为闲置，也不能通过缩短轮询间隔解决字段缺乏区分度的问题。计数不变本身不证明缓存或通信故障，也不能据此确认具体计数步长。

插件按故障位解释 `run_status`、用 `rinse` 提示冲洗，与用户观察相容。已查证据尚未恢复其他实时制水 getter；这不等于证明设备不存在其他属性或推送机制。`pure_water_record` 是云端历史记录，不能当作局域网 `get_prop` 属性或实时开关量。

因此不填入猜测的 `making_mask`。`unverified` 可选为有正常数据时保持亮屏；`flow_change` 只提供计数变化提示。研究资料关于 10 流量档的描述仍是观察支持的假设，**不能保证每次轮询计数变化，也不能保证短时制水可检测**。未来只有实测证据支持后才配置状态规则，或加入已证实的新只读接口。当前不能承诺准确的“制水即亮、停止后 30 秒熄屏”。

## TDS 变化唤醒（默认经验规则）

用户选择按 `tds_out` 的变化唤醒屏幕，默认每 2500ms 查询、最后一次变化后 30000ms 熄屏；这些是本项目设置，不是设备协议或官方制水算法。复用原有九字段请求和上一份读数，不增加请求，不持久化活动状态。只比较连续有效且未过期的样本；首次收到数据或通信恢复时显示一个延时窗口，缺失/非法 TDS 不触发变化，随后第一次有效值只建立基线。

研究历史 [`6c4e4f8`（原 `cfe98aa`）](https://github.com/pexcn/xiaomi-purifier-lx7-monitor/blob/6c4e4f81ebd9be304edfae9223108765edce93a2/research/docs/evidence/operating-state.md#是否通过-tds_out-变化判断制水)给出了所上传官方插件的显示链：`MainPageTDS.setData` 直接覆盖并显示有效 TDS，没有比较前后差值；出水 TDS≥1000 或进/出水字段为 `error`/`null`/`undefined` 时显示“等待制水开始”；水波在挂载后循环动画，TDS 用于配色。这些显示条件不等于实时制水状态，也不证明 1000 是停机状态码，本项目不把该阈值作为亮灭屏规则。

TDS 变化只能作为最近有测量更新的经验线索。制水时整数读数可能长时间相同，停水后也可能延迟更新；静止时的采样规律尚未确认。本模式可能在制水中熄屏或在停水后亮屏，误判率需带人工开关水时间的实机日志验证。诊断日志已包含 `tds_in`、`tds_out`，原始 `run_status`、`rinse` 和滤芯计数仍保留。现有显式配置在 OTA 后保留，不自动改写旧的 `unverified`/2000ms 设置；启用方式见 README。

滤芯 `usedflow/totalflow` 的单位及原水/纯水口径在研究资料中仍待验证；本项目按用户要求只按这两个数计算流量百分比，升数需用户明确配置系数。没有任何时间寿命回退、固定纯废水比或除以 2 的隐含换算。
