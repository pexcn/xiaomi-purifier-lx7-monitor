// Ghidra 12.1.4; synthetic ELF; 4024afc0

undefined4 * FUN_4024afc0(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;

  param_3 = param_3 & 0xffff;
  puVar2 = (undefined4 *)*DAT_4024af38;
  FUN_40241d00();
  for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    if ((*(ushort *)(puVar2 + 5) & 7) == param_3) {
      if (param_2 == 0) {
        iVar1 = (*DAT_40249f84)(param_1,puVar2 + 1);
      }
      else {
        iVar1 = FUN_40209084(param_1,param_2);
      }
      if (iVar1 == 0) break;
    }
  }
  FUN_40241d18();
  return puVar2;
}
