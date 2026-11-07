// Ghidra 12.1.4; synthetic ELF; 402572d8

undefined4 FUN_402572d8(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;

  piVar3 = (int *)PTR_DAT_4023ccf0;
  if (*(int *)PTR_DAT_4023ccf0 == 0) {
    FUN_4023f7b4();
    uVar1 = FUN_402039d0();
    uVar2 = FUN_40203980();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__current_flash_flag_is__d__cu_402572d0,uVar1,uVar2);
  }
  if (*piVar3 == 0) {
    FUN_4023f7b4();
    uVar1 = FUN_40203740();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__current_user_bin_addr__x_402572d4,uVar1);
  }
  return 0;
}
