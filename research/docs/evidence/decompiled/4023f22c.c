// Ghidra 12.1.4; synthetic ELF; 4023f22c

undefined4 FUN_4023f22c(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_20 [7];

  iVar2 = DAT_4023f110;
  (*DAT_4023d19c)(DAT_4023f110,0,0x48);
  iVar1 = FUN_40243cf4();
  iVar3 = iVar2;
  if (iVar1 != 0) {
    local_20[0] = 0;
    iVar1 = FUN_4023f040(iVar1,PTR_s_ot_config_disable_local_restore_4023f228,local_20,4);
    if ((-1 < iVar1) && (local_20[0] != -1)) {
      *(undefined4 *)(iVar2 + 0x44) = 1;
      return 0;
    }
  }
  *(undefined4 *)(iVar3 + 0x44) = 0;
  return 0;
}
