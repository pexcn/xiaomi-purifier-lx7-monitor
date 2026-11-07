// Ghidra 12.1.4; synthetic ELF; 4024b3fc

void FUN_4024b3fc(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar6 = *DAT_4024b3e0;
  if (param_1 < 2) {
    uVar1 = *DAT_4024b060;
    puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
  }
  else {
    iVar2 = FUN_4020a2fc(iVar6,0x400,PTR_s___method____sync__s___params____4024b3e4,
                         *(undefined4 *)(param_2 + 4));
    if (0x400 < iVar2) {
      iVar2 = 0x400;
    }
    for (iVar7 = 2; iVar7 != param_1; iVar7 = iVar7 + 1) {
      iVar5 = 0x400 - iVar2;
      if (iVar7 == 2) {
        uVar1 = *(undefined4 *)(param_2 + 8);
        puVar4 = PTR_s__s_3ffea401_0xa_4024b3ec;
      }
      else {
        uVar1 = *(undefined4 *)(iVar7 * 4 + param_2);
        puVar4 = PTR_DAT_4024b3e8;
      }
      iVar3 = FUN_4020a2fc(iVar6 + iVar2,iVar5,puVar4,uVar1);
      if (iVar5 < iVar3) {
        iVar3 = iVar5;
      }
      iVar2 = iVar2 + iVar3;
    }
    FUN_4020a2fc(iVar6 + iVar2,0x400 - iVar2,PTR_s____3ffe9fc7_0x2a_4024b3f0);
    if (*(uint *)PTR_DAT_4023ccf0 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__up_call__s_4024b3f4,iVar6);
    }
    uVar1 = (*DAT_4023d3c0)(iVar6);
    iVar6 = FUN_40244520(DAT_4024451c,DAT_4024451c,iVar6,uVar1,PTR_FUN_4024b3f8,0);
    if (iVar6 == 0) {
      uVar1 = *DAT_4024b060;
      puVar4 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
    }
    else {
      uVar1 = *DAT_4024b060;
      puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
    }
  }
  FUN_4024e0c0(uVar1,puVar4);
  return;
}
