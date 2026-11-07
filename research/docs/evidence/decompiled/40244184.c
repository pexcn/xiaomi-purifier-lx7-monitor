// Ghidra 12.1.4; synthetic ELF; 40244184

undefined4 FUN_40244184(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_20;
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;

  puVar2 = DAT_40243f38;
  DAT_40243f38[2] = 0x100;
  puVar2[4] = 1;
  puVar2[1] = 0;
  *puVar2 = 0;
  FUN_40241e04(DAT_40244174);
  iVar1 = (*(code *)PTR_FUN_4023cf0c)(puVar2[2]);
  puVar2[3] = iVar1;
  if (iVar1 == 0) {
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__malloc_uart_buf_failed_40244178);
    }
    FUN_40241eac(puVar2[5]);
  }
  FUN_40229a80(0);
  FUN_40229a80(1);
  local_20 = 0xb;
  uStack_1a = 1;
  uStack_1c = 0xff;
  uStack_1b = 0x14;
  FUN_40229c2c(0,&local_20);
  FUN_40229b0c(PTR_LAB_4024417c);
  (*(code *)PTR_FUN_40244180)(0x20);
  return 0;
}
