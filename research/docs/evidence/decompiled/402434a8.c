// Ghidra 12.1.4; synthetic ELF; 402434a8

undefined4 FUN_402434a8(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint uVar4;
  int *piVar5;

  piVar5 = DAT_40242564;
  puVar3 = DAT_4024216c;
  if (param_1 < 6) {
    uVar4 = *DAT_4024216c;
    if ((((param_1 == 1) && (uVar4 != 1)) || ((param_1 == 2 && (uVar4 != 2)))) ||
       ((param_1 == 3 && (uVar4 != 3)))) {
      *DAT_4024216c = param_1;
      iVar1 = *piVar5;
      if (iVar1 < 100) {
        if ((*DAT_40242588 - 1U < 2) && (iVar1 < 0x46)) {
          iVar1 = iVar1 + 0x14;
        }
        else {
          iVar1 = iVar1 + 10;
        }
        *piVar5 = iVar1;
      }
      if (*(int *)PTR_DAT_4023ccf0 == 0) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__progress_is__d_402434a0,*piVar5);
      }
      FUN_40243384();
    }
    if (param_1 != uVar4) {
      *puVar3 = param_1;
      FUN_40241a90();
      FUN_402573d0();
      if ((*DAT_40242588 - 1U < 2) && (*puVar3 == 4)) {
        *DAT_40242564 = 99;
        FUN_40243384();
      }
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)
                  (PTR_s__I__ota_state_change____s__>__s_402434a4,
                   *(undefined4 *)(PTR_PTR_40242168 + uVar4 * 4),
                   *(undefined4 *)(PTR_PTR_40242168 + *puVar3 * 4));
      }
      FUN_4024346c();
      if (*puVar3 - 4 < 2) {
        *puVar3 = 0;
        return 0;
      }
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
