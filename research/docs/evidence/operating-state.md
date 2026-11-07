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

