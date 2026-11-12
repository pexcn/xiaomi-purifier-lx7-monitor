// Ghidra 12.1.4; synthetic ELF; 40242d58

int FUN_40242d58(void)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int local_20;
  int iStack_1c;

  FUN_40242c08();
  iVar1 = FUN_4023fa6c(*(undefined4 *)(DAT_40242148 + 0x28),&local_20,8);
  if (iVar1 == 0) {
    if (local_20 == DAT_40242d4c) {
      puVar3 = (uint *)PTR_DAT_4023ccf0;
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__valied_user_firmware_was_fou_40242d50,iStack_1c);
      }
      iVar2 = FUN_40242ca4(8,iStack_1c);
      iVar1 = iStack_1c;
      if ((iVar2 != 0) && (iVar1 = iVar2, *puVar3 < 4)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__check_crc_error_in_find_vali_40242d54);
        iVar1 = iVar2;
      }
    }
  }
  else {
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__flash_read_error_in_find_val_40242d48);
    }
    if (0 < iVar1) {
      iVar1 = -1;
    }
  }
  return iVar1;
}
