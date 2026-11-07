// Ghidra 12.1.4; synthetic ELF; 4024bb84

void FUN_4024bb84(uint param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;

  if (((int)param_1 < 3) || ((param_1 & 1) == 0)) {
    if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4024bbec;
    FUN_4023f7b4();
    puVar2 = PTR_s__E__wrong_number_of_prop_arg_4024bb7c;
  }
  else {
    puVar4 = (undefined4 *)(param_2 + 4);
    iVar5 = 2;
    do {
      if ((int)param_1 <= iVar5) {
        uVar3 = *DAT_4024b060;
        puVar2 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
        goto LAB_4024bbf5;
      }
      iVar5 = iVar5 + 2;
      iVar1 = FUN_4024d5b0(*DAT_40242eb4,*puVar4,puVar4[1]);
      puVar4 = puVar4 + 2;
    } while (iVar1 == 0);
    if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4024bbec;
    FUN_4023f7b4();
    puVar2 = PTR_s__E__prop_invalid_4024bb80;
  }
  (*(code *)PTR_FUN_4023ccf8)(puVar2);
LAB_4024bbec:
  uVar3 = *DAT_4024b060;
  puVar2 = PTR_s_error_3ffea87d_0x22_4024b1b0;
LAB_4024bbf5:
  FUN_4024e0c0(uVar3,puVar2);
  return;
}
