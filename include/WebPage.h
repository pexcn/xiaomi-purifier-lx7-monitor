#pragma once
#include <Arduino.h>

// Embedded in the application image: no filesystem image or external web assets.
static const char LoginPage[] PROGMEM = R"HTML(<!doctype html>
<html lang="zh-CN"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>登录 · 小米净水器 500G 增强版（MR532-D）监视器</title>
<style>
:root{font:16px system-ui;color:#20332c;background:#f3f6f3}*{box-sizing:border-box}
body{min-height:100svh;margin:0;display:grid;place-items:center;padding:20px}
main{width:100%;max-width:390px;background:white;border:1px solid #dce5dd;border-radius:12px;padding:28px}
h1{font-size:24px;margin-top:0}p{color:#52675c;line-height:1.6}
label{display:block;margin:22px 0 16px}input{display:block;width:100%;margin-top:8px;padding:12px;border:1px solid #adbeb2;border-radius:6px;font:inherit}
button{width:100%;padding:12px;background:#216b50;color:white;border:0;border-radius:6px;font:inherit;cursor:pointer}button:disabled{opacity:.5;cursor:wait}
#status{min-height:1.5em;font-size:14px;margin-bottom:0}
</style>
<main><h1>登录小米净水器监视器</h1><p>输入管理密码，即可修改设置或升级固件。</p>
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
<title>小米净水器 500G 增强版（MR532-D）监视器</title>
<style>
:root{font:16px system-ui;color:#20332c;background:#f3f6f3}*{box-sizing:border-box}[hidden]{display:none!important}
body{max-width:660px;margin:32px auto;padding:0 18px}h1{font-size:26px}h2{font-size:20px}
section{background:white;border:1px solid #dce5dd;border-radius:12px;padding:22px;margin:20px 0}
label{display:block;margin:16px 0}input:not([type=checkbox]),textarea{display:block;width:100%;margin-top:6px;padding:10px;border:1px solid #adbeb2;border-radius:6px;font:inherit}
textarea{font:13px monospace;min-height:220px}button{padding:11px 18px;background:#216b50;color:white;border:0;border-radius:6px;font:inherit;cursor:pointer}
button:disabled{opacity:.5;cursor:wait}small,p{color:#52675c;line-height:1.6}#status{white-space:pre-wrap}summary{cursor:pointer}
header{display:flex;align-items:center;justify-content:space-between;gap:12px;flex-wrap:wrap}#logout{background:transparent;color:#216b50;border:1px solid #adbeb2;padding:8px 12px;white-space:nowrap;margin-left:auto}
.toolbar{display:flex;align-items:center;gap:14px;flex-wrap:wrap}.toolbar label{margin:0}.secondary{background:transparent;color:#216b50;border:1px solid #adbeb2;padding:8px 12px}
.metrics{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:16px;margin:20px 0}.metrics div{min-width:0}.metrics dt{font-size:13px;color:#52675c}.metrics dd{margin:5px 0 0;font-size:16px;overflow-wrap:anywhere}
#log-output{max-height:320px;min-height:140px;overflow:auto;white-space:pre-wrap;overflow-wrap:anywhere;background:#182b23;color:#e1f0e6;border-radius:6px;padding:12px;font:12px/1.6 monospace}#log-panel>summary{font-size:20px;font-weight:700}
</style>
<header><h1>小米净水器监视器</h1><button id="logout" type="button" hidden>退出登录</button></header><p>设置保存在监视器中，重启和固件升级后仍会保留。</p>
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
<section><div class="toolbar"><h2>设备信息</h2><button id="system-refresh" class="secondary" type="button" disabled>刷新</button></div>
<p id="system-status" role="status">页面载入时读取一次，点击刷新可更新当前数值。</p>
<dl class="metrics">
<div><dt>CPU 频率</dt><dd id="cpu-frequency">--</dd></div>
<div><dt>运行时间</dt><dd id="uptime">--</dd></div>
<div><dt>RAM 总量（应用 DRAM）</dt><dd id="ram-total">--</dd></div>
<div><dt>RAM 可用（空闲堆）</dt><dd id="ram-free">--</dd></div>
<div><dt>最大连续空闲堆</dt><dd id="ram-max">--</dd></div>
<div><dt>堆碎片率</dt><dd id="heap-fragmentation">--</dd></div>
<div><dt>Flash 容量（物理）</dt><dd id="flash-total">--</dd></div>
<div><dt>当前固件大小</dt><dd id="firmware-size">--</dd></div>
<div><dt>Flash 可用（OTA）</dt><dd id="flash-free">--</dd></div>
<div><dt>文件系统容量</dt><dd id="fs-total">--</dd></div>
<div><dt>文件系统可用</dt><dd id="fs-free">--</dd></div>
<div><dt>Wi-Fi 信号</dt><dd id="wifi-signal">--</dd></div>
<div><dt>局域网 IP</dt><dd id="local-ip">--</dd></div>
<div><dt>Arduino 核心版本</dt><dd id="core-version">--</dd></div>
</dl></section>
<section><details id="log-panel"><summary>运行日志</summary><p>保留最近的运行记录，重启后清空。时间为启动后的秒数。</p>
<div class="toolbar"><button id="log-refresh" class="secondary" type="button">刷新</button><label><input id="log-auto" type="checkbox" checked> 自动刷新（2 秒）</label></div>
<p id="log-status" role="status">展开后读取日志。</p><pre id="log-output" tabindex="0" aria-label="设备运行日志">尚未读取日志</pre></details></section>
<section><h2>固件升级</h2><p>选择本项目的 .bin 固件即可。升级保留配置，无需上传 littlefs.bin。</p>
<form id="ota" method="post" enctype="multipart/form-data">
<label>应用固件<input type="file" name="firmware" accept=".bin" required></label>
<button id="upgrade" disabled>上传并升级</button></form><p>上传期间保持供电，完成后设备自动重启。</p></section>
<script>
const form=document.querySelector('#config'),status=document.querySelector('#status');
let csrf='';
let pageBusy=false;
const logPanel=document.querySelector('#log-panel'),logOutput=document.querySelector('#log-output'),logStatus=document.querySelector('#log-status'),logAuto=document.querySelector('#log-auto');
let logTimer=0,logLoading=false,systemLoading=false;
function stopLogRefresh(){clearTimeout(logTimer);logTimer=0;}
function scheduleLogRefresh(){stopLogRefresh();if(logPanel.open&&logAuto.checked&&!document.hidden&&!pageBusy)logTimer=setTimeout(refreshLogs,2000);}
function loginRequired(r){if(r.status!==401)return false;pageBusy=true;stopLogRefresh();location.replace('/login');return true;}
const setText=(id,value)=>document.getElementById(id).textContent=value;
function bytes(n){if(typeof n!=='number'||!Number.isFinite(n))return '--';return n>=1048576?(n/1048576).toFixed(2)+' MiB':n>=1024?(n/1024).toFixed(1)+' KiB':n+' B';}
function uptime(n){const days=Math.floor(n/86400),hours=Math.floor(n/3600)%24,minutes=Math.floor(n/60)%60;return(days?days+' 天 ':'')+hours+' 时 '+minutes+' 分 '+Math.floor(n%60)+' 秒';}
async function refreshSystem(){if(systemLoading||pageBusy)return;systemLoading=true;document.querySelector('#system-refresh').disabled=true;
 try{const r=await fetch('/api/system',{cache:'no-store'});if(loginRequired(r))return;if(!r.ok)throw Error('读取失败：'+r.status);const c=await r.json();
 setText('cpu-frequency',c.cpu_mhz+' MHz');setText('uptime',uptime(c.uptime_seconds));setText('ram-total',bytes(c.ram_total_bytes));setText('ram-free',bytes(c.heap_free_bytes));
 setText('ram-max',bytes(c.heap_max_block_bytes));setText('heap-fragmentation',c.heap_fragmentation_percent+'%');setText('flash-total',bytes(c.flash_total_bytes));
 setText('firmware-size',bytes(c.firmware_bytes));setText('flash-free',bytes(c.ota_free_bytes));setText('fs-total',c.filesystem_ready?bytes(c.filesystem_total_bytes):'未初始化');
 setText('fs-free',c.filesystem_ready?bytes(c.filesystem_free_bytes):'未初始化');setText('wifi-signal',c.wifi_rssi_dbm===null?'未连接':c.wifi_rssi_dbm+' dBm');
 setText('local-ip',c.local_ip||'未连接');setText('core-version',c.core_version);setText('system-status','已更新；点击刷新可读取当前数值。');}
 catch(e){setText('system-status','读取失败：'+e.message);}finally{systemLoading=false;document.querySelector('#system-refresh').disabled=false;}}
async function refreshLogs(){stopLogRefresh();if(logLoading||pageBusy)return;logLoading=true;document.querySelector('#log-refresh').disabled=true;
 const follow=logOutput.scrollHeight-logOutput.scrollTop-logOutput.clientHeight<24;
 try{const r=await fetch('/api/logs',{cache:'no-store'});if(loginRequired(r))return;if(!r.ok)throw Error('读取失败：'+r.status);logOutput.textContent=(await r.text())||'暂无运行日志';
 if(follow)logOutput.scrollTop=logOutput.scrollHeight;logStatus.textContent='已刷新';}
 catch(e){logStatus.textContent='读取失败：'+e.message;}finally{logLoading=false;document.querySelector('#log-refresh').disabled=false;scheduleLogRefresh();}}
document.querySelector('#system-refresh').addEventListener('click',refreshSystem);
document.querySelector('#log-refresh').addEventListener('click',refreshLogs);
logPanel.addEventListener('toggle',()=>{if(logPanel.open)refreshLogs();else stopLogRefresh();});
logAuto.addEventListener('change',()=>{if(logAuto.checked&&logPanel.open)refreshLogs();else stopLogRefresh();});
document.addEventListener('visibilitychange',()=>{if(document.hidden)stopLogRefresh();else if(logPanel.open&&logAuto.checked)refreshLogs();});
fetch('/api/config',{cache:'no-store'}).then(async r=>{if(r.status===401){location.replace('/login');throw Error('请重新登录');}if(!r.ok)throw Error('读取失败：'+r.status);return r.json()}).then(c=>{
 csrf=c.csrf;form.elements.wifi_ssid.value=c.wifi_ssid;form.elements.device_ip.value=c.device_ip;
 form.elements.settings.value=JSON.stringify(c.settings,null,2);form.elements.token.required=!c.has_token;
 form.elements.admin_password.required=!c.has_admin_password;
 document.querySelector('#initialize').hidden=c.storage_ready;
 document.querySelector('#save').disabled=false;
 document.querySelector('#upgrade').disabled=!c.has_admin_password;
 document.querySelector('#logout').hidden=c.setup_access;
 document.querySelector('#ota').action='/update?csrf='+encodeURIComponent(csrf);
 refreshSystem();
 status.textContent=c.has_admin_password?'设置已读取。':'请设置 Wi-Fi、净水器连接信息和管理密码。';
}).catch(e=>status.textContent=e.message);
form.addEventListener('submit',async e=>{e.preventDefault();const save=document.querySelector('#save');
 try{const fields=Object.fromEntries(new FormData(form));fields.settings=JSON.parse(fields.settings);
 fields.open_wifi=form.elements.open_wifi.checked;fields.initialize_storage=form.elements.initialize_storage.checked;
 pageBusy=true;stopLogRefresh();save.disabled=true;const r=await fetch('/config?csrf='+encodeURIComponent(csrf),{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(fields)});
 if(r.status===401){location.replace('/login');return;}const text=await r.text();if(!r.ok)throw Error(text);status.textContent='已保存，正在重启。请重新连接 Wi-Fi 后打开设备页面。';}
 catch(e){status.textContent='保存失败：'+e.message;save.disabled=false;pageBusy=false;scheduleLogRefresh();}});
document.querySelector('#logout').addEventListener('click',async()=>{
 const button=document.querySelector('#logout');button.disabled=true;pageBusy=true;stopLogRefresh();
 try{const r=await fetch('/logout?csrf='+encodeURIComponent(csrf),{method:'POST'});
 if(!r.ok&&r.status!==401)throw Error(await r.text());location.replace('/login');}
 catch(e){status.textContent='退出失败：'+e.message;button.disabled=false;pageBusy=false;scheduleLogRefresh();}});
document.querySelector('#ota').addEventListener('submit',()=>{pageBusy=true;stopLogRefresh();document.querySelector('#upgrade').disabled=true;status.textContent='正在上传固件，请保持供电…';});
</script></html>)HTML";
