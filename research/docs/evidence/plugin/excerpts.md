# lx7 插件原文摘录

来源为上传包的 android/main.bundle；只做 RAM bundle 拆分，未执行插件。偏移均为原始 bundle 字节偏移，不是源码行号。

## model-flags

模块 `10142`，符号 `Base.model`，偏移 `0x1e4d41`，长度 `503` 字节。

```javascript
  _extends(Base.model, {
    islx7lx8: model === Base.model.cMivlx7 || model === Base.model.cMivlx8,
    islx7: model === Base.model.cMivlx7,
    islx8: model === Base.model.cMivlx8,
    isMi2: model === Base.model.cMivlx5 || model === Base.model.cMivlx7,
    isLx4: model === Base.model.cMivlx4,
    isUnder: model === Base.model.cMiv3 || model === Base.model.cMivlx3 || model === Base.model.cMivlx5 || model === Base.model.cMivlx6 || model === Base.model.cMivlx7 || model === Base.model.cMivlx8
  });
```

## model-config-dispatch

模块 `10259`，符号 `Config switch`，偏移 `0x1fe0ed`，长度 `98` 字节。

```javascript
    case 'yunmi.waterpuri.lx7':
      (0, _extends2.default)(Config, _lx6.default);
      break;
```

## lx7-config

模块 `10286`，符号 `default config`，偏移 `0x1fea57`，长度 `230` 字节。

```javascript
  var _default = {
    inWaterTempTds: Base.lang.inWaterTemp,
    unit: '℃',
    showTips: false,
    Mainunit: 'mg/L',
    showRestDays: false,
    enalbeConsecutivePress: true,
    showLvStatus: true,
    showReset: true
  };
```

## get-prop-fields

模块 `10136`，符号 `MainPage.readState`，偏移 `0x1dfe2b`，长度 `284` 字节。

```javascript
        if (Base.model.isMi2) {
          params = ['run_status', 'f1_totalflow', 'f1_totaltime', 'f1_usedflow', 'f1_usedtime', 'f2_totalflow', 'f2_totaltime', 'f2_usedflow', 'f2_usedtime', 'tds_in', 'tds_out', 'rinse', 'temperature', 'tds_warn_thd', 'lightMode'];
        } else {}
```

## time-days

模块 `10334`，符号 `getDays`，偏移 `0x211798`，长度 `185` 字节。

```javascript
  function getDays(totalTime, usePercent) {
    usePercent = usePercent < 0 ? 0 : usePercent;
    var d = totalTime * (usePercent / 100);
    return d <= 0 ? 0 : parseInt(d / 24);
  }
```

## filter-lifetime

模块 `10334`，符号 `DealProp.excute isMi2 branch`，偏移 `0x211e09`，长度 `512` 字节。

```javascript
        var life1int = (obj.f1_totaltime - obj.f1_usedtime) * 100 / obj.f1_totaltime;
        var life2int = (obj.f2_totaltime - obj.f2_usedtime) * 100 / obj.f2_totaltime;
        var life1color = getColorByPercent(life1int, obj.f1_totaltime);
        var life2color = getColorByPercent(life2int, obj.f2_totaltime);
        var days1 = getDays(obj.f1_totaltime, life1int);
        var days2 = getDays(obj.f2_totaltime, life2int);
        var daysObj = {
          days1: days1,
          days2: days2
        };
```

## light-warning

模块 `10334`，符号 `DealProp.excute lightMode branch`，偏移 `0x212100`，长度 `558` 字节。

```javascript
        if (obj.lightMode === 1) {
          if (obj.tds_out >= obj.tds_warn_thd || obj.rinse === 1 || life1int <= 0 || life2int <= 0) {
            curError.push({
              name: Base.lang.longtou,
              detail: Base.lang.longtouDesSpecial,
              type: 'tdsWarn'
            });
          }
        } else {
          if (life1int <= 0 || life2int <= 0) {
            curError.push({
              name: Base.lang.longtou,
              detail: Base.lang.longtouDes,
              type: 'tdsWarn'
            });
          }
        }
```

## filter-binding

模块 `10142`，符号 `Base.getFilterData isMi2 branch`，偏移 `0x1e4487`，长度 `471` 字节。

```javascript
      if (Base.model.isMi2) {
        data = [{
          key: '1',
          name: Base.lang.f1FilterName,
          leftDays: props.days1,
          skuId: 21,
          gid: '108348',
          leftPercent: props.life1int,
          index: 1
        }, {
          key: '2',
          name: Base.lang.filter3Name,
          skuId: roSkuId,
          gid: '108348',
          leftDays: props.days2,
          leftPercent: props.life2int,
          index: 2
        }];
```

## details-navigation

模块 `10298`，符号 `MainPageFilter.toFilterState`，偏移 `0x203203`，长度 `197` 字节。

```javascript
      key: "toFilterState",
      value: function toFilterState(item) {
        if (item.leftPercent === null) return;
        this.props.navigation.navigate('FilterState', item);
      }
    }, {
```

## percent-render

模块 `10298`，符号 `MainPageFilter.render`，偏移 `0x204061`，长度 `182` 字节。

```javascript
            }, typeof item.leftPercent == 'number' ? parseInt(item.leftPercent) : '--'), _react.default.createElement(_reactNative.Text, {
              style: styles.filterLifeUnit
```

## tds-options

模块 `10139`，符号 `FeatureView constructor`，偏移 `0x1e2986`，长度 `155` 字节。

```javascript
      var tdsList = [];

      for (var i = 100; i <= 300; i = i + 10) {
        tdsList.push({
          value: i,
          text: i
        });
      }
```

## tds-read-write

模块 `10139`，符号 `FeatureView.componentDidMount/showTdsList`，偏移 `0x1e2a8a`，长度 `1179` 字节。

```javascript
      key: "componentDidMount",
      value: function componentDidMount() {
        var _this2 = this;

        if (Base.supportTdsWarn()) {
          Base.fetchMethod('get_prop', ['tds_warn_thd'], function (data) {
            if (data.code === 0) {
              _this2.setState({
                tdsWarnValue: data.result[0]
              });
            } else {
              Base.toast(Base.lang.getReadError(Base.handlerErrorMes(data)));
            }
          });
        }
      }
    }, {
      key: "componentWillUnmount",
      value: function componentWillUnmount() {}
    }, {
      key: "showTdsList",
      value: function showTdsList() {
        var _this3 = this;

        Base.showItemPicker(this.state.tdsWarnValue, this.tdsList, function (item) {
          Base.fetchMethod('set_tds_warn_thd', [item.value], function (data) {
            if (data.code === 0) {
              Base.toast(Base.lang.setSuccess);

              _this3.setState({
                tdsWarnValue: item.value
              });
            } else {
              Base.toast(Base.lang.getReadError(Base.handlerErrorMes(data)));
            }
          });
        });
      }
    }, {
```

## hidden-light-entry

模块 `10391`，符号 `MiSettingPage.consecutivePress`，偏移 `0x22a2c8`，长度 `1094` 字节。

```javascript
      _this.consecutivePress = function () {
        if (!_Config.default.enalbeConsecutivePress) {
          return;
        }

        _this.num++;

        if (_this.num == 1) {
          _this.time_1 = new Date().getTime() / 1000;
        }

        if (_this.num == 5) {
          _this.time_5 = new Date().getTime() / 1000;

          if (_this.time_5 - _this.time_1 <= 4) {
            _this.num = 0;
            Base.fetchMethod('get_prop', ['lightMode'], function (data) {
              if (data.code === 0) {
                if (data.result[0] == 'error') {
                  _this.setState({
                    lightMode: 0
                  });

                  return;
                }

                _this.setState({
                  lightMode: data.result[0]
                });
              } else {
                Base.toast(Base.lang.getReadError(Base.handlerErrorMes(data)));
              }
            });

            _this.setState({
              showPressMode: true
            });
          } else {
            _this.num = 0;
          }
        }
      };
```

## light-write

模块 `10391`，符号 `MiSettingPage.setMode`，偏移 `0x22aa39`，长度 `469` 字节。

```javascript
      key: "setMode",
      value: function setMode(value) {
        var _this2 = this;

        Base.fetchMethod("set_lightMode", [value], function (data) {
          if (data.code === 0) {
            Base.toast(Base.lang.setSuccess);

            _this2.setState({
              lightMode: !_this2.state.lightMode
            });
          } else {
            Base.toast(Base.lang.getReadError(Base.handlerErrorMes(data)));
          }
        });
      }
    }, {
```

## light-switch-values

模块 `10391`，符号 `MiSettingPage.render`，偏移 `0x22b4fc`，长度 `660` 字节。

```javascript
          title: Base.lang.simpleMode,
          subtitle: Base.lang.simpleModeTips,
          value: lightMode == 0,
          showSeparator: true,
          onValueChange: function onValueChange(value) {
            _this3.setMode(value ? 0 : 1);
          }
        }), _react.default.createElement(_ListItem.ListItemWithSwitch, {
          title: Base.lang.specialMode,
          subtitleStyle: {
            height: 60
          },
          subtitle: Base.lang.specialModeTips,
          value: lightMode == 1,
          showSeparator: true,
          onValueChange: function onValueChange(value) {
            _this3.setMode(value ? 1 : 0);
          }
```

## filter-reset-name

模块 `10436`，符号 `FilterState.resetTwice`，偏移 `0x239ed0`，长度 `56` 字节。

```javascript
        var filterKey = "set_f" + params.key + "_used";
```

## filter-reset-params

模块 `10436`，符号 `FilterState.setResetMode`，偏移 `0x23a0b0`，长度 `444` 字节。

```javascript
      key: "setResetMode",
      value: function setResetMode(key) {
        var _this6 = this;

        Base.fetchMethod(key, [0, 0], function (data) {
          if (data.code === 0) {
            Base.toast(Base.lang.resetSuc);

            _this6.setState({
              leftPercent: 100
            });
          } else {
            Base.toast(Base.lang.getReadError(Base.handlerErrorMes(data)));
          }
        });
      }
    }, {
```

## water-display-unit

模块 `10142`，符号 `Base.formatWater`，偏移 `0x1e4a08`，长度 `236` 字节。

```javascript
    formatWater: function formatWater(value) {
      if (value !== '--' && value > 0) {
        value = Base.getFloatInteger1(value / 1000, 2);
      }

      if (value === -1) {
        return '--';
      }

      return value;
    },
```

## history-water-shape

模块 `10319`，符号 `getPureWaste`，偏移 `0x208fd5`，长度 `629` 字节。

```javascript
  function getPureWaste(values) {
    if (values[0] > 315504000000 || values.length === 5) {
      values.shift();
    }

    var item = {};

    if (values.length === 3) {
      item.pureWater = values[1] || 0;
      item.wasteWater = values[0] - values[1] || 0;
      item.water = values[0] || item.pureWater;
      if (item.wasteWater < 0) item.wasteWater = 0;
    } else if (values.length === 4) {
      item.pureWater = values[2] || 0;
      item.wasteWater = 0;
      item.water = values[2] || 0;
    }

    if (Base.model.isMi2) {
      item.wasteWater = 0;
      item.water = item.pureWater;
    }

    return item;
  }
```

## history-event-fields

模块 `10316`，符号 `MainPageUseWater.getItem`，偏移 `0x206bd8`，长度 `890` 字节。

```javascript
      key: "getItem",
      value: function getItem(target) {
        var targetValue = JSON.parse(target.value);

        if (targetValue[0] === 0 || targetValue[1] === 0 || targetValue[2] === 0) {
          return null;
        }

        var date = new Date(target.time * 1000);
        date.setSeconds(date.getSeconds() - targetValue[0]);
        var title = DateUtil.dateFormat(date.getTime(), 'hh:mm:ss');
        var des = Base.lang.dayWaterDetail(DateUtil.timeDetail(targetValue[0], Base.lang), Base.formatWater(targetValue[1]), Base.formatWater(targetValue[3]), Base.model.isMi2);
        return {
          key: Base.getUUID(),
          title: title,
          des: des
        };
      }
    }, {
      key: "chooseTypeByIndex",
      value: function chooseTypeByIndex(index) {
        this.chooseType([Base.lang.month, Base.lang.week, Base.lang.date][index]);
      }
    }, {
```

## cloud-history-keys

模块 `10319`，符号 `MainPageUseWaterAnalyse.dealData`，偏移 `0x20ab36`，长度 `725` 字节。

```javascript
        var now = new Date();
        var start, key;

        if (type === Base.lang.date) {
          var columnWidth = Base.screenWidth / 9;
          var date = DateUtil.addDays(now, -14);
          start = DateUtil.getDateBegin(date);
          key = "daily_record";
        } else if (type === Base.lang.week) {
          columnWidth = Base.screenWidth / 6;
          var firstDayOfWeek = DateUtil.getFirstDayOfWeek(now);
          start = DateUtil.addDays(firstDayOfWeek, -98);
          key = "weekly_record";
        } else {
          columnWidth = Base.screenWidth / 5;
          var date = DateUtil.addMonths(now, -14);
          start = DateUtil.getMonthBegin(date);
          key = "monthly_record";
        }
```

## tds-render-entry

模块 `10139`，符号 `FeatureView.render`，偏移 `0x1e2f25`，长度 `1551` 字节。

```javascript
      key: "render",
      value: function render() {
        var _this4 = this;

        return _react.default.createElement(_reactNative.View, {
          style: {
            backgroundColor: '#fff'
          }
        }, _react.default.createElement(_reactNative.View, {
          style: styles.border
        }), Base.model.isUnder ? null : _react.default.createElement(_reactNative.TouchableOpacity, {
          style: styles.rowContainer,
          onPress: function onPress() {
            _this4.props.navigation.navigate('SetupPage', {
              title: Base.lang.setupTip,
              tips: Base.getSetupTips()
            });
          }
        }, _react.default.createElement(_reactNative.Text, {
          style: styles.title
        }, Base.lang.setupTip), _react.default.createElement(_reactNative.Image, {
          style: styles.subArrow,
          source: _$$_REQUIRE(_dependencyMap[10])
        })), Base.model.isUnder ? null : _react.default.createElement(_reactNative.View, {
          style: styles.separator
        }), _react.default.createElement(_reactNative.TouchableOpacity, {
          style: styles.rowContainer,
          onPress: function onPress() {
            _this4.props.navigation.navigate("DeviceSet");
          }
        }, _react.default.createElement(_reactNative.Text, {
          style: styles.title
        }, Base.lang.deviceSet), _react.default.createElement(_reactNative.Image, {
          style: styles.subArrow,
          source: _$$_REQUIRE(_dependencyMap[10])
        })));
      }
    }]);
```

## sdk-history-api

模块 `10043`，符号 `dataManager.callSmartHomeAPI (Mijia)`，偏移 `0x1caf96`，长度 `266` 字节。

```javascript
          if (subUrl === urls.deviceData) {
            key = 'getDeviceData';
          } else if (subUrl === urls.interimFileUrl) {
            key = 'getInterimFileUrl';
          } else if (subUrl === urls.fileUrl) {
            key = 'getFileUrl';
          }
```
