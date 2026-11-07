# 用户指定 mit fork：客户端行为证据

只读取公开源码，没有编译或运行客户端、没有接触用户米家凭据。取样提交：`pexcn/mit@f0760df508e0d6a1e46cb7997fab9194ec5a5d4b`（2026-11-07 查得 main）。这不独立证明用户本机安装包正是此提交。

| 证据 | 源文件与函数 | 观察 |
|---|---|---|
| C1 | [src/cli/mod.rs](https://github.com/pexcn/mit/blob/f0760df508e0d6a1e46cb7997fab9194ec5a5d4b/src/cli/mod.rs) 的 `RawArgs/parse_raw_params` | 参数解析为 serde_json::Value，只要求数组或对象，不改变数字/字符串类型 |
| C2 | [src/cli/commands.rs](https://github.com/pexcn/mit/blob/f0760df508e0d6a1e46cb7997fab9194ec5a5d4b/src/cli/commands.rs) 的 `handle_raw` | 用本地缓存取得连接信息，直接传 `args.method`、`args.params` 到 lan_request_direct；输出 result，没有单位换算 |
| C3 | [src/miot_lan.rs](https://github.com/pexcn/mit/blob/f0760df508e0d6a1e46cb7997fab9194ec5a5d4b/src/miot_lan.rs) 的 `lan_request_direct` | 握手后调用 miio_command；未按属性名分支 |
| C4 | 同文件的 `miio_command` | JSON 包含 id、method、params；解密后取出 result，不重排数组、不将 3600 乘成 7200 |
| C5 | [tests/test_cli_raw.rs](https://github.com/pexcn/mit/blob/f0760df508e0d6a1e46cb7997fab9194ec5a5d4b/tests/test_cli_raw.rs) | mock 测试包含 tds_warn_thd/lightMode 及字符串/数值参数透传；这是模拟应答，不能作为固件默认值或实机可读性的证据 |

C4 核心原文：

```rust
let payload = json!({ "id": msg_id, "method": method, "params": params });
// ...发送、解密、JSON 解析...
Ok(value.get("result").cloned().unwrap_or(value))
```

因此用户报告的 `set_lightMode '["1"]'` 在该源码路径确实以字符串 "1" 发送；不能因为 CLI 打印成功，就将其参数规范写成数字 `[1]`。
