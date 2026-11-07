# lx7 米家插件静态分析

## 样本与方法

| 项目 | 证据 |
|---|---|
| 用户上传包 | `1023976.zip`，SHA-256 `2d639e9dc42b606c2e78c760f63c75ef2c0fb4092fdd130d080f22d8485033e3` |
| 型号声明 | `model_list.json` 仅含 `yunmi.waterpuri.lx7`，version=75 |
| 工程声明 | `android/project.json`：package_path=`com.viomi.miwaterpurifier`，version=`1.0.62`，sdk_api_level=10062 |
| 主 bundle | `android/main.bundle`，2441117 字节，SHA-256 `33a3e8ab29f824f904632444e2d96f8b7bf0f9b37dc5ecfcb3c24cc4561fd9cd` |
| 格式 | Metro indexed RAM bundle，魔数 `0xFB0BD1E5`；23339 个表项，639 个有效模块 |

版本 75、工程版本 1.0.62 和设备 `fw_ver` 属于不同元数据，不能互相替代。包内含签名材料，本次未验证签名，也不据安装目录证明它必定是当前激活版本。

通过 [unpack_ram_bundle.py](../scripts/unpack_ram_bundle.py) 只读拆分，未执行插件代码。639 个模块均核对原始字节范围、SHA-256 和包装器模块 ID。REA 对选定 9 个模块完成 AST 解析，无语法解析失败；整体应用和语义图仍为 partial，不能称为完整恢复。原始包、资源和完整 REA 结果只保存在忽略的 `work/`。

重要结论使用模块 ID、函数名和原 bundle 字节偏移定位，不使用源码行号。见 [原文摘录](evidence/plugin/excerpts.md) 和 [来源及模块表](evidence/plugin/provenance.json)。

## 已证实的 lx7 分支

模块 10142 的 `Base.model.isMi2` 对 lx5/lx7 为真，`getFilterData` 对应两滤芯：F1 复合滤芯、F2 RO。模块 10259 的型号分派将 lx7 映射到模块 10286：启用连按隐藏设置、滤芯复位入口，首页顶部显示温度；`showRestDays=false`。这不是未识别型号的通用分支推测。

## 时间与滤芯寿命

模块 10136 的 `MainPage.readState` 请求 15 个属性；模块 10334 的 `DealProp.excute` 对其按顺序映射。lx7 的显示链为：

```text
MainPage.readState
  → DealProp.excute
  → Base.getFilterData
  → MainPageFilter.setData/render
  → FilterState（沿用传入的百分比）
```

**已证实（插件解释）**：`usedtime/totaltime` 按小时量纲使用。`getDays` 将剩余时间除以 24 换算天数；8640、17280 因此对应 360、720 天配额。

正常正数输入下的显示规则：

```text
剩余百分比 = (totaltime - usedtime) × 100 / totaltime
界面百分比 = parseInt(剩余百分比)，负数先钳到 0；NaN 显示 --
内部剩余天数 = parseInt(totaltime × max(剩余百分比, 0) / 100 / 24)
```

lx7 默认隐藏天数字样，但内部仍用天数判断临期提示。用户 U3 的 usedtime=24 时，F1/F2 约为 99.7222%/99.8611%，首页整数显示均为 99%；内部剩余天数为 359/719。

**已证实的范围**：该插件的所查首页/详情显示链没有把 usedflow/totalflow 放进百分比公式，也没有在此求时间与流量寿命的最小值。**不能据此推断** MCU 生成 usedtime 时不考虑流量，或设备忽略流量寿命。

## usedflow、容量与历史水量

- f1/f2 usedflow、totalflow 在本包中用于读取和原始字段映射，未找到其原水/纯水解释、升单位标注或 10L 向上取整算法。
- 没有找到 3600、7200 的源码字面量或针对这些字段的倍增换算。7200 仍是用户设备读数；本插件不能解释它与 3600L 标称的差异。
- “24 时间档、10 流量档”仍是 U3 支持的假设；插件按小时解释时间，并不证明 MCU 每 24 小时更新一次。

**历史水量另有来源**：模块 10316/10319 调用 `Base.fetchUserDeviceData`，底层由模块 10043 映射到米家 SDK `getDeviceData`。这是云端历史数据读取，不是 MiIO get_prop 属性：

| 数据 | type/key | 已见解释 |
|---|---|---|
| 日/周/月统计 | `store`：`daily_record`、`weekly_record`、`monthly_record` | 解析不同长度格式；三字段格式把值 1 视为纯水、值 0 视为总水量；lx7 分支随后只保留纯水显示 |
| 单次制水事件 | `event`：`pure_water_record` | 详情页筛选 10 字段且末字段以 idle 开头的记录；`getItem` 用值 0 作秒数、值 1 作纯水量、值 3 作自来水量 |

历史记录的水量通过 `Base.formatWater` 除以 1000 后以 L 显示，支持这些历史水量字段按 mL 解释；**不能把这个单位套给滤芯 usedflow**。lx7 统计图将废水显示量强制置 0，并隐藏自来水文案，不代表实物无废水或原始传感器读数为 0。读取真实事件并与计数跳变对照是后续无拆机验证方向，本次未访问云端。

## 设置及隐藏入口

| 接口/功能 | 已见实现 | 范围与限制 | 证据模块 |
|---|---|---|---|
| `get_prop` | lx7 请求 15 项，详见 miio-api.md | 不是设备全部属性枚举 | 10136、10334 |
| TDS 阈值 | 读取 `tds_warn_thd`；`showTdsList` 调 `set_tds_warn_thd [item.value]` | 选择器函数生成 100–300、步长 10；当前 render 未见调用该选择器的入口。不是固件限值，更不是默认值；用户 50 成功的证据保留 | 10139 |
| 灯模式隐藏入口 | 4 秒内连续点击“功能设置”标题 5 次后读取 lightMode 并显示开关 | lx7 配置启用；已核对米家路由 `10007→10385→10391`，非另一套未使用设置页 | 10286、10391 |
| `set_lightMode` | 插件发送数字 `[0]`/`[1]` | 0 为简易、1 为特殊需求模式；用户字符串 "1" 成功不与数字请求矛盾。未实测其他值 | 10391 |
| 模式的告警含义 | 简易模式依据滤芯寿命到期；特殊模式还检查出水 TDS≥阈值或 rinse=1 | 指插件提示/说明；硬件灯光行为未在本次实测，文案中的 100ppm 不等于实时阈值固定为 100 | 10334、10145 |
| 滤芯复位 | 动态拼 `set_f1_used`/`set_f2_used`，参数 `[0,0]`，两次确认后才请求 | 只恢复此调用格式；非零参数及两个参数各自含义未知，未执行 | 10436 |

`rinse` 是已见读取属性；没有找到 lx7 的主动冲洗命令，不补造 setter。完整 MCU 参数校验、传感器、计数存储和复位实现仍缺主控代码。

## 复现

先将该包的 `android/main.bundle` 放到本地忽略目录：

```sh
python3 scripts/unpack_ram_bundle.py work/plugin-1023976/android/main.bundle work/plugin-modules
```

输出为纯文本模块及带原始偏移/哈希的 manifest，不启动 React Native 或执行模块。REA 选择路径及统计保存在来源记录中；可对拆出的 .js 文件使用 `analyze-javascript-application` 静态分析。
