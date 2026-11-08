# 制水状态：用户观察与插件证据

## 用户实测 U4

用户报告制水和不制水时，`run_status`、`rinse` 均为 0。本分析未查询设备；用户未提供带时间戳的原始响应、采样间隔或同时读取的版本信息。

| 用户观察的工况 | run_status | rinse |
|---|---:|---:|
| 制水 | 0 | 0 |
| 不制水 | 0 | 0 |

插件模块 10334 将 run_status 送入 getError，按位查异常文案；lx7 使用模块 10145 的 exceptionsArr2，仅 bit 15 对应“泵热保护”。因此插件按故障位处理此字段，0 表示没有由这些位映射出的故障提示，不代表待机。未定义的位仍不能断言没有硬件含义。

rinse 非零进入清洗提示；等于 1 时映射 washState=2。它不是所查代码中的普通制水标志，0 不能区分制水和闲置。用户 U4 与此解释相容。

**待验证**：尚未从 lx7 已知 15 项查询和所查显示链恢复可靠的实时制水接口；不等于证明设备没有其他属性或推送机制。pure_water_record 是云端历史记录，尚未验证上传延迟及状态全集，不能直接作为实时开关量。

## 是否通过 tds_out 变化判断制水？

**已证实（上传插件显示链）**：没有按前后两次 tds_out 的差值判断制水。模块 10136 将 DealProp 解析后的 outTds 传入模块 10253 的 MainPageTDS.setData；setData 直接覆盖 this.tds_out，并依据当前值是否有效选择数字或初始提示，不保存此前 TDS 来判断制水状态。

- 当前出水 TDS≥1000，或进/出水 TDS 是 error、null、undefined 时，调用 showInitValue。模块 10256 将显示值设为内部哨兵 -1000；模块 10253 的 render 在此状态显示“--”及 Base.lang.waitFor（模块 10145 文案“等待制水开始”）。这是显示条件，不是已恢复的 MCU 制水标志；1000 也不能被当成停机状态码。
- 有效值直接交给 setTaegetValue 显示；这个函数直接 setValue，不检查 TDS 是否变化。方法拼写保留插件原文。
- MainPage.dealValue 还将 TDS 传给模块 10295 的 MainPageWave.dealValue，用于选择颜色。水波在 componentDidMount 后启动循环动画，不依赖 TDS 变化判定泵状态。

**待验证的经验规则**：若实测确认该设备只在制水时刷新 TDS，数值变化可以提示最近有测量更新；仍不等于此刻泵一定在运行。制水中水质稳定或整数读数相同时可以不变，停水后也可能收到延迟更新。设备静止时是否持续采样、是否受温度等因素影响尚未恢复，不能预设绝不变化。即使使用“变化后保持一段时间”的规则，超时和误判率也需要带人工开/关水时间的日志验证。

本结论仅针对上传插件版本，不据此声称所有官方版本均无其他判断机制。以下追加片段记录了显示链的关键条件。

## 原始代码证据

来源：上传包 android/main.bundle；哈希和模块来源见 [provenance.json](plugin/provenance.json)。以下偏移为原 bundle 字节偏移，SHA-256 对应原始片段字节；显示仅去除片段末尾空白。未执行插件。

### getError

模块 `10334`，偏移 `0x21145d`，长度 `705` 字节，SHA-256 `ed957dc8e0d2b4c1ab72864f624c361847061ca63373671001cd7d43e27b6233`。

```javascript
  function getError(errorCode) {
    var errorCode = Number(errorCode).toString(2);
    var len = 32;
    errorCode = Base.paddingZero(errorCode, len);

    if (Base.model.isMi2) {
      var errors = Base.lang.exceptionsArr2;
    } else {
      errors = Base.lang.exceptionsArr1;
    }

    var curError = [];

    for (var i = 31; i >= 0; i--) {
      if (errorCode.charAt(i) === '1') {
        var index = 31 - i;
        var target = errors[index];

        if (target && target.length > 0) {
          curError.push({
            index: index,
            name: target[0],
            detail: target[1] || '',
            type: 'error'
          });
        }
      }
    }

    return curError;
  }
```

### DealProp.excute: run_status

模块 `10334`，偏移 `0x211dd8`，长度 `49` 字节，SHA-256 `62665caf12eea444c8ff79450430650bd362c5e8c9350443b84529487ab0cda7`。

```javascript
        var curError = getError(obj.run_status);
```

### exceptionsArr2

模块 `10145`，偏移 `0x1e726b`，长度 `265` 字节，SHA-256 `ff1a8e148139ed480b92c0d630c6c8c2b9059b688d1e9edfd25713eef61bf330`。

```javascript
    exceptionsArr2: [null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, ['泵热保护', '净水器连续工作时间过长，为避免净水器水泵过热造成损坏，请暂停使用，20分钟后可恢复正常工作']],
```

### DealProp.excute: rinse warning

模块 `10334`，偏移 `0x21232e`，长度 `204` 字节，SHA-256 `c8ddd4c7698e2f96dc87991f6b0212ea23f4c5be5a35eeea6c175f8d9a0718a1`。

```javascript
        if (obj.rinse !== 0) {
          curError = [{
            name: Base.lang.washing,
            detail: Base.lang.washingDes,
            type: 'washing'
          }].concat(curError);
        }
```

### DealProp.excute: washState

模块 `10334`，偏移 `0x21252b`，长度 `46` 字节，SHA-256 `591249ef3a71d45b82ec84861d89efb5500cb4264ba5dad2d7766124ee1a7de2`。

```javascript
          washState: obj.rinse === 1 ? 2 : 0,
```

### MainPageTDS.setData

模块 `10253`，偏移 `0x1f963e`，长度 `774` 字节，SHA-256 `df43cd00ed7d64f52f8a20133df1573b47288017d387028a6e4b3576ad50ea32`。

```javascript
      value: function setData(props) {
        this.tds_out = props.outTds;
        this.tds_in_init = props.inTds;
        var inTds;

        if (!this.init && props.inTds < 100) {
          inTds = 150;
        } else {
          inTds = props.inTds;
        }

        this.tds_in = inTds;
        this.setError(props);

        if (this.tds_out >= 1000 || Base.isUnValidValue(props.inTds) || Base.isUnValidValue(props.outTds)) {
          this.refs.animatedNumber && this.refs.animatedNumber.showInitValue();
        } else {
          Base.colorChange.init(this.tds_in, this.tds_out);
          this.refs.animatedNumber && this.refs.animatedNumber.setTaegetValue(this.tds_out);
          this.props.dealValue(this.tds_out);
        }

        this.init = true;
      }
```

### Base.isUnValidValue

模块 `10058`，偏移 `0x1ceaf8`，长度 `138` 字节，SHA-256 `a669d9c91f7aaaf1e011b6e74a48379abb16813737dc4090309e15dff445336e`。

```javascript
      isUnValidValue: function isUnValidValue(value) {
        return value === 'error' || value === null || value === undefined;
      },
```

### AnimatedNumber.showInitValue

模块 `10256`，偏移 `0x1fd3ca`，长度 `98` 字节，SHA-256 `be672b97a20755ae028b15a7472d4ddae5f44dbc8e4d0327c04caf3da0000943`。

```javascript
      value: function showInitValue() {
        this.state.valueAnimation.setValue(-1000);
      }
```

### AnimatedNumber.setTaegetValue

模块 `10256`，偏移 `0x1fd453`，长度 `104` 字节，SHA-256 `e6324d6a1f3effc0452b7640acd443a1b640903844be8395cee182106832989d`。

```javascript
      value: function setTaegetValue(value) {
        this.state.valueAnimation.setValue(value);
      }
```

### MainPageTDS.render: waiting branch

模块 `10253`，偏移 `0x1fa9d0`，长度 `40` 字节，SHA-256 `15d3210f25dc53dc67530673f8c0cad104bc783cf2bab3f1b97216f88ddb3c52`。

```javascript
          } else if (value === -1000) {
```

### MainPageTDS.render: waitFor label

模块 `10253`，偏移 `0x1fadde`，长度 `37` 字节，SHA-256 `3c244521305cc1c21df8d92c3da5327eb937ecebcf6f88df1fe663826776b9fe`。

```javascript
            }, Base.lang.waitFor)));
```

### waitFor Chinese label

模块 `10145`，偏移 `0x1e954c`，长度 `35` 字节，SHA-256 `2ed24e440e88588f0581c786217ff975ad701e6005080591e81adcfe8d4f7382`。

```javascript
    waitFor: '等待制水开始',
```

### MainPageWave.componentDidMount

模块 `10295`，偏移 `0x200eb6`，长度 `263` 字节，SHA-256 `d58f7c5b27dcebb4c94352175f1ef90b806ebe1fd82f133be17ff7614c3168ce`。

```javascript
      value: function componentDidMount() {
        var _this4 = this;

        _reactNative.Animated.timing(this.state.opacity, {
          toValue: 1,
          duration: 1000
        }).start(function () {
          _this4.startAnimation();
        });
      }
```

### MainPageWave.dealValue

模块 `10295`，偏移 `0x20126b`，长度 `238` 字节，SHA-256 `5bd4d93ae7c9a510431a05700178df820cb336967ea996d1a0097589d149e1bb`。

```javascript
      value: function dealValue(value) {
        var arr = Base.colorChange.getColorArr(value);

        if (!arr) {
          return;
        }

        this.setState({
          colors: arr,
          tagvalue: value
        });
      }
```

### MainPageWave.startAnimation

模块 `10295`，偏移 `0x200c94`，长度 `504` 字节，SHA-256 `acb46c53114c61abd7d8d5b4ce3da3fa7cb271a9defe945479675ace30138ede`。

```javascript
      value: function startAnimation() {
        var _this3 = this;

        this.timing = _reactNative.Animated.timing(this.state.value, {
          toValue: 0,
          duration: 2000,
          easing: _reactNative.Easing.bezier(1, 1, 0, 0)
        });
        this.timing.start(function (isFinished) {
          if (isFinished) {
            _this3.state.value.setValue(startX);

            _this3.state.value1.setValue(startX);

            _this3.startAnimation();
          }
        });
      }
```
