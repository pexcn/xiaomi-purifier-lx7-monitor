// Ghidra 12.1.4; synthetic ELF; 40244068

void FUN_40244068(undefined4 param_1,undefined1 *param_2,int param_3)

{
  undefined1 *puVar1;

  if (param_2 == (undefined1 *)0x0) {
    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__warning_serial_buffer_is_nul_40244064);
    }
  }
  else {
    puVar1 = param_2 + param_3;
    for (; param_2 != puVar1; param_2 = param_2 + 1) {
      FUN_402571c8(0,*param_2);
    }
  }
  return;
}
