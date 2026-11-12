// Ghidra 12.1.4; synthetic ELF; 4024b60c

void FUN_4024b60c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar5 = *DAT_4024b3e0;
  iVar7 = 2;
  iVar6 = 0;
  if (param_1 < 3) {
    uVar1 = *DAT_4024b060;
    puVar3 = PTR_s_error_3ffea87d_0x22_4024b1b0;
  }
  else {
    do {
      iVar4 = 0x400 - iVar6;
      if (iVar7 == 2) {
        uVar1 = *(undefined4 *)(param_2 + 8);
        puVar3 = PTR_s___s_3ffea43b_0xa_4024b600;
      }
      else {
        uVar1 = *(undefined4 *)(iVar7 * 4 + param_2);
        puVar3 = PTR_DAT_4024b3e8;
      }
      iVar2 = FUN_4020a2fc(iVar5 + iVar6,iVar4,puVar3,uVar1);
      if (iVar4 < iVar2) {
        iVar2 = iVar4;
      }
      iVar6 = iVar6 + iVar2;
      iVar7 = iVar7 + 1;
    } while (iVar7 != param_1);
    FUN_4020a2fc(iVar5 + iVar6,0x400 - iVar6,DAT_4024b604);
    if (*(uint *)PTR_DAT_4023ccf0 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__up_store__s_4024b608,iVar5);
    }
    iVar5 = FUN_4024d6c8(*DAT_40242eb4,*(undefined4 *)(param_2 + 4),iVar5);
    if (iVar5 == 0) {
      uVar1 = *DAT_4024b060;
      puVar3 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
    }
    else {
      uVar1 = *DAT_4024b060;
      puVar3 = PTR_s_error_3ffea87d_0x22_4024b1b0;
    }
  }
  FUN_4024e0c0(uVar1,puVar3);
  return;
}
