// Ghidra 12.1.4; synthetic ELF; 40242ca4

int FUN_40242ca4(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint local_28 [9];

  param_1 = param_1 + *(int *)(DAT_40242148 + 0x28);
  iVar3 = 0;
  local_28[0] = 0;
  uVar1 = FUN_40242c24(param_1,param_2);
  iVar2 = FUN_4023fa6c(param_1 + param_2,local_28,4);
  if (iVar2 < iVar3) {
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__crc_check__flash_read_error_40242c9c);
    }
  }
  else {
    if (uVar1 == local_28[0]) {
      return iVar3;
    }
    FUN_4024270c(iVar3);
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)
                (PTR_s__E__crc_check_error__crc32_is____40242ca0,
                 uVar1 >> 0x18 | uVar1 << 0x18 | (uVar1 & DAT_4023cf04) << 8 |
                 (uVar1 & DAT_4023cf00) >> 8);
    }
  }
  return -1;
}
