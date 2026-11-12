// Ghidra 12.1.4; synthetic ELF; 402421e0

undefined4 FUN_402421e0(void)

{
  int iVar1;
  undefined4 uVar2;

  iVar1 = FUN_40203980();
  if (iVar1 == 0) {
    uVar2 = DAT_40242148[5];
  }
  else {
    if (iVar1 != 1) {
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return 0;
      }
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__select_flash__flash_flag_err_402421dc);
      return 0;
    }
    uVar2 = *DAT_40242148;
  }
  DAT_40242148[10] = uVar2;
  return 0;
}
