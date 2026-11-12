// Ghidra 12.1.4; synthetic ELF; 4023f300

int FUN_4023f300(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined1 auStack_60 [64];
  undefined4 auStack_20 [7];

  (*DAT_4023d19c)(auStack_60,0,0x40);
  iVar1 = FUN_4024a908(*param_1,param_1[2],0);
  if (iVar1 == 0) {
    puVar2 = PTR_s_value_not_found_4023f2f0;
    if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4023f383;
    FUN_4023f7b4();
    puVar2 = PTR_s__E__Failed_to_find_valid_value_i_4023f2ec;
  }
  else {
    auStack_20[0] = 0;
    iVar1 = FUN_4024aa94(*param_1,iVar1,auStack_20);
    if (iVar1 == 0) {
      iVar1 = FUN_4023f2a8(auStack_20[0]);
      if (iVar1 == 0) {
        FUN_402446ac(param_2,param_3,0);
        return iVar1;
      }
      puVar2 = PTR_s_save_failed_4023f2f8;
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__Failed_to_save_disable_local_4023f2f4);
        puVar2 = PTR_s_save_failed_4023f2f8;
      }
      goto LAB_4023f383;
    }
    puVar2 = PTR_s_value_not_found_4023f2f0;
    if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4023f383;
    FUN_4023f7b4();
    puVar2 = PTR_s__E__Failed_to_find_valid_value_i_4023f2fc;
  }
  (*(code *)PTR_FUN_4023ccf8)(puVar2);
  puVar2 = PTR_s_value_not_found_4023f2f0;
LAB_4023f383:
  (*DAT_40225f90)(auStack_60,puVar2,0x40);
  FUN_40244640(param_2,param_3,0xffffffff,auStack_60);
  return -1;
}
