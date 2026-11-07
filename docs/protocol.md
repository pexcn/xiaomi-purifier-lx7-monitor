# MiIO 接口核实与证据边界

核对日期：2026-11-07。以下是仓库证据及用户观察，不是本项目连接设备的实测报告。

主要来源：[`pexcn/xiaomi-waterpurifier-lx7-re@02b65af`](https://github.com/pexcn/xiaomi-waterpurifier-lx7-re/tree/02b65afb8498fe37f8ec1c7c349ddbd017465a8f)。其旧 Wi-Fi 固件样本是 **1.3.9**，分析仓库用户设备为 **2.1.3 / MCU 0012**，二者不可混为当前实现证据。lx7 插件的型号映射版本 75 是另一组版本信息。

| 接口/字段 | 已确认的证据 | 本项目处理/待验证 |
|---|---|---|
| `get_prop`，参数为属性名字符串数组 | 分析仓库记录的用户八字段查询成功；lx7 插件调用 15 字段 | 仅发送只读请求；本项目九字段组合及当前实机完整应答待验证 |
| `tds_in` / `tds_out` | 插件请求并解释为进/出水 TDS，UI 使用 mg/L、文案使用 ppm | 显示设备值；本机采样周期、校准与现场可读性待验证 |
| `temperature` | 插件读取并标记为 ℃ | 显示数值；缺失显示 `--` |
| `f1_usedflow` / `f2_usedflow` | 用户请求返回过 0、10；插件也读取 | 仅作为累计流量计数，不补造更新时间或计量水路 |
| `f1_totalflow` / `f2_totalflow` | 用户设备都返回 7200；插件也读取 | 从设备读取，不硬编码额度；不推断 7200/3600 的关系 |
| `run_status` | 插件读取并按标志处理异常；lx7 的 bit15 有泵热保护文案 | **未确认制水位/枚举**；不以非零判定制水 |
| `rinse` | 插件将 1 解释为冲洗 | 不是制水属性，也不据此推断完整工况枚举 |
| `usedtime` / `totaltime` | 插件按时间计算百分比 | 用户要求按流量计算，本项目完全不请求这些字段 |
| `miIO.info.life` | 旧样本来自运行 tick | 不用作滤芯寿命，也不请求可能含敏感信息的 `miIO.info` |

详见上游固定版本的 [接口表](https://github.com/pexcn/xiaomi-waterpurifier-lx7-re/blob/02b65afb8498fe37f8ec1c7c349ddbd017465a8f/docs/miio-api.md)、[插件证据](https://github.com/pexcn/xiaomi-waterpurifier-lx7-re/blob/02b65afb8498fe37f8ec1c7c349ddbd017465a8f/docs/plugin.md)及 [流量口径](https://github.com/pexcn/xiaomi-waterpurifier-lx7-re/blob/02b65afb8498fe37f8ec1c7c349ddbd017465a8f/docs/usedflow.md)。

本项目请求顺序固定如下，返回数组严格逐项对应，不能套用插件不同顺序的数组：

```json
{"id":1,"method":"get_prop","params":["tds_in","tds_out","temperature","f1_usedflow","f1_totalflow","f2_usedflow","f2_totalflow","run_status","rinse"]}
```

缺失字段、`null`、负计数、布尔值不会被转换为 0。计数兼容 JSON 无符号整数与严格十进制数字字符串；温度接受 JSON 数值。数组长度、RPC `id` 和 `error` 均检查；某个字段不可用显示 `--`，整个结果无有效监测字段时报告错误。遇到未知字段/不支持查询不尝试 setter 或猜测新属性。

## 传输

通用 LAN MiIO 封装核对自 [`python-miio@9a00e08/miio/protocol.py`](https://github.com/rytilahti/python-miio/blob/9a00e0888ef85f8d8d84888cabd9e46d1b0a18df/miio/protocol.py)：UDP 54321，`0x2131`、大端长度/DID/时间戳、32 字节头；16 字节 Token，`key=MD5(token)`、`iv=MD5(key+token)`；JSON 含 NUL 后作 PKCS#7 填充，AES-128-CBC；校验为 `MD5(header[0:16]+token+ciphertext)`。

握手为 `21310020` 后接 28 字节 `ff`。响应提供 DID 和设备时间，握手本身不认证；**不学习响应中的 Token**，后续加密数据必须通过预配置 Token 校验。只接受配置 IP/端口的应答，检查长度、DID、校验、填充及请求 ID；768 字节上限，单个在途请求，非阻塞等待。异常后重新握手，每小时刷新设备时间基准，无需 NTP。

这验证了实现依据，不等于已经证明目标固件接受本项目报文；设备 Token、LAN 访问策略、当前 getter 可用性均需现场验证。

## 自动亮屏的限制

本次用户补充：下午测试中，闲置和制水时 `get_prop ["run_status","rinse"]` **印象中均为 `[0,0]`**，冲洗未测。这是待重复核对的人工观察，不是精确时序抓包；如果属实，这两个字段不能区分制水与闲置。

因此不填入猜测的 `making_mask`。默认 `unverified` 保持正常数据显示（OLED 不再显示原始状态标签，诊断日志可读）；`flow_change` 只提供计数变化提示。上游关于 10 流量档的描述仍是观察支持的假设，**不能保证每 2 秒计数变化，也不能保证短时制水可检测**。未来只有实测证据支持后才配置状态规则，或加入已证实的新只读接口。当前不能承诺准确的“制水即亮、停止后 30 秒熄屏”。

滤芯 `usedflow/totalflow` 的单位及原水/纯水口径在上游仍待验证；本项目按用户要求只按这两个数计算流量百分比，升数需用户明确配置系数。没有任何时间寿命回退、固定纯废水比或除以 2 的隐含换算。
