// Ghidra 12.1.4; synthetic ELF; 4023f2a8

int FUN_4023f2a8(int param_1)

{
  int iVar1;
  int iVar2;
  int local_20 [7];

  iVar2 = 0;
  if (*(int *)(DAT_4023f110 + 0x44) != param_1) {
    *(int *)(DAT_4023f110 + 0x44) = param_1;
    local_20[0] = param_1;
    iVar1 = FUN_40243cf4();
    if (iVar1 == iVar2) {
      iVar2 = -1;
    }
    else {
      iVar1 = FUN_4023ef54(iVar1,PTR_s_ot_config_disable_local_restore_4023f228,local_20,4);
      if (iVar1 != 0) {
        iVar2 = 1;
      }
      iVar2 = -iVar2;
    }
  }
  return iVar2;
}
