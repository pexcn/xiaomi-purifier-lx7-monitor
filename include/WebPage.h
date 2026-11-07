#pragma once
#include <Arduino.h>

// Embedded in the application image: no filesystem image or external web assets.
static const char LoginPage[] PROGMEM = R"HTML(<!doctype html>
<html lang="zh-CN"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>登录净水器显示器</title>
<style>
:root{font:16px system-ui;color:#20332c;background:#f3f6f3}*{box-sizing:border-box}
body{min-height:100svh;margin:0;display:grid;place-items:center;padding:20px}
main{width:100%;max-width:390px;background:white;border:1px solid #dce5dd;border-radius:12px;padding:28px}
h1{font-size:24px;margin-top:0}p{color:#52675c;line-height:1.6}
label{display:block;margin:22px 0 16px}input{display:block;width:100%;margin-top:8px;padding:12px;border:1px solid #adbeb2;border-radius:6px;font:inherit}
button{width:100%;padding:12px;background:#216b50;color:white;border:0;border-radius:6px;font:inherit;cursor:pointer}button:disabled{opacity:.5;cursor:wait}
#status{min-height:1.5em;font-size:14px;margin-bottom:0}
</style>
<main><h1>登录净水器显示器</h1><p>输入管理密码，即可修改设置或升级固件。</p>
<form id="login"><label>管理密码<input name="password" type="password" maxlength="64" required autocomplete="current-password" autofocus></label>
<button id="submit" disabled>登录</button></form><p id="status" role="status">正在连接设备…</p></main>
<script>
const form=document.querySelector('#login'),status=document.querySelector('#status'),button=document.querySelector('#submit');
let csrf='';
fetch('/api/login',{cache:'no-store'}).then(async r=>{if(!r.ok)throw Error('连接失败，请刷新后重试');return r.json()}).then(c=>{
 if(!c.has_admin_password){status.textContent='尚未设置管理密码，请连接 OLED 显示的设置热点完成配置。';return;}
 csrf=c.csrf;button.disabled=false;status.textContent='';
}).catch(e=>status.textContent=e.message);
form.addEventListener('submit',async e=>{e.preventDefault();button.disabled=true;status.textContent='正在登录…';
 try{const r=await fetch('/login?csrf='+encodeURIComponent(csrf),{method:'POST',body:new URLSearchParams(new FormData(form))});
 if(!r.ok)throw Error(await r.text());location.replace('/');}
 catch(e){status.textContent=e.message;button.disabled=false;form.elements.password.focus();}});
</script></html>)HTML";

static const char ManagementPage[] PROGMEM = R"HTML(<!doctype html>
<html lang="zh-CN"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>净水器显示器设置</title>
<style>
:root{font:16px system-ui;color:#20332c;background:#f3f6f3}*{box-sizing:border-box}[hidden]{display:none!important}
body{max-width:660px;margin:32px auto;padding:0 18px}h1{font-size:26px}h2{font-size:20px}
section{background:white;border:1px solid #dce5dd;border-radius:12px;padding:22px;margin:20px 0}
label{display:block;margin:16px 0}input:not([type=checkbox]),textarea{display:block;width:100%;margin-top:6px;padding:10px;border:1px solid #adbeb2;border-radius:6px;font:inherit}
textarea{font:13px monospace;min-height:220px}button{padding:11px 18px;background:#216b50;color:white;border:0;border-radius:6px;font:inherit;cursor:pointer}
button:disabled{opacity:.5;cursor:wait}small,p{color:#52675c;line-height:1.6}#status{white-space:pre-wrap}summary{cursor:pointer}
header{display:flex;align-items:center;justify-content:space-between;gap:12px}#logout{background:transparent;color:#216b50;border:1px solid #adbeb2;padding:8px 12px;white-space:nowrap}
</style>
<header><h1>净水器显示器设置</h1><button id="logout" type="button" hidden>退出登录</button></header><p>设置保存在显示器中，重启和固件升级后仍会保留。</p>
<p id="status" role="status">正在读取设置…</p>
<section><h2>连接与显示</h2>
<form id="config" autocomplete="off">
<label>Wi-Fi 名称<input name="wifi_ssid" maxlength="32" required></label>
<label>Wi-Fi 密码<input name="wifi_password" type="password" maxlength="64" placeholder="留空保留原密码" autocomplete="new-password"></label>
<label><input name="open_wifi" type="checkbox"> 使用无密码 Wi-Fi（清除原密码）</label>
<label>净水器 IP<input name="device_ip" inputmode="decimal" placeholder="192.168.1.100" required></label>
<label>净水器 Token<input name="token" type="password" maxlength="32" placeholder="32 位十六进制；留空保留原值" autocomplete="new-password"></label>
<label>管理密码<input name="admin_password" type="password" maxlength="64" placeholder="首次设置必填；以后留空保留" autocomplete="new-password"></label>
<small>登录只需管理密码，不设最短长度。密码和 Token 不会从设备回填到网页。</small>
<details><summary>显示、轮询及高级设置</summary><p>时间单位为毫秒；filter_display 可选 percent 或 litres。</p>
<label>设置 JSON<textarea name="settings" spellcheck="false" required></textarea></label></details>
<label id="initialize" hidden><input name="initialize_storage" type="checkbox"> 初始化设备存储（首次使用需要；会清空配置区）</label>
<button id="save" disabled>保存并重启</button></form></section>
<section><h2>固件升级</h2><p>选择本项目的 .bin 固件即可。升级保留配置，无需上传 littlefs.bin。</p>
<form id="ota" method="post" enctype="multipart/form-data">
<label>应用固件<input type="file" name="firmware" accept=".bin" required></label>
<button id="upgrade" disabled>上传并升级</button></form><p>上传期间保持供电，完成后设备自动重启。</p></section>
<script>
const form=document.querySelector('#config'),status=document.querySelector('#status');
let csrf='';
fetch('/api/config',{cache:'no-store'}).then(async r=>{if(r.status===401){location.replace('/login');throw Error('请重新登录');}if(!r.ok)throw Error('读取失败：'+r.status);return r.json()}).then(c=>{
 csrf=c.csrf;form.elements.wifi_ssid.value=c.wifi_ssid;form.elements.device_ip.value=c.device_ip;
 form.elements.settings.value=JSON.stringify(c.settings,null,2);form.elements.token.required=!c.has_token;
 form.elements.admin_password.required=!c.has_admin_password;
 document.querySelector('#initialize').hidden=c.storage_ready;
 document.querySelector('#save').disabled=false;
 document.querySelector('#upgrade').disabled=!c.has_admin_password;
 document.querySelector('#logout').hidden=c.setup_access;
 document.querySelector('#ota').action='/update?csrf='+encodeURIComponent(csrf);
 status.textContent=c.has_admin_password?'设置已读取。':'请设置 Wi-Fi、净水器连接信息和管理密码。';
}).catch(e=>status.textContent=e.message);
form.addEventListener('submit',async e=>{e.preventDefault();const save=document.querySelector('#save');
 try{const fields=Object.fromEntries(new FormData(form));fields.settings=JSON.parse(fields.settings);
 fields.open_wifi=form.elements.open_wifi.checked;fields.initialize_storage=form.elements.initialize_storage.checked;
 save.disabled=true;const r=await fetch('/config?csrf='+encodeURIComponent(csrf),{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(fields)});
 if(r.status===401){location.replace('/login');return;}const text=await r.text();if(!r.ok)throw Error(text);status.textContent='已保存，正在重启。请重新连接 Wi-Fi 后打开设备页面。';}
 catch(e){status.textContent='保存失败：'+e.message;save.disabled=false;}});
document.querySelector('#logout').addEventListener('click',async()=>{
 const button=document.querySelector('#logout');button.disabled=true;
 try{const r=await fetch('/logout?csrf='+encodeURIComponent(csrf),{method:'POST'});
 if(!r.ok&&r.status!==401)throw Error(await r.text());location.replace('/login');}
 catch(e){status.textContent='退出失败：'+e.message;button.disabled=false;}});
document.querySelector('#ota').addEventListener('submit',()=>{document.querySelector('#upgrade').disabled=true;status.textContent='正在上传固件，请保持供电…';});
</script></html>)HTML";
