// Ghidra 12.1.4; synthetic ELF; 4024b4e8

void FUN_4024b4e8(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_40;
  int iStack_3c;
  undefined4 uStack_38;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;

  iVar4 = *DAT_4024b3e0;
  iStack_30 = param_2;
  if ((1 < param_1) && (*DAT_4024b134 != 0)) {
    piVar5 = DAT_4024b134;
    uVar1 = FUN_40241ba8(*(undefined4 *)(*DAT_4024b134 + 4));
    if (uVar1 < *(uint *)PTR_DAT_4024b19c) {
      iVar2 = FUN_4020a2fc(iVar4,0x400,PTR_s___result____s_4024b4dc,*(undefined4 *)(iStack_30 + 4));
      if (0x400 < iVar2) {
        iVar2 = 0x400;
      }
      iVar3 = 2;
      iVar6 = 0x400;
      while (iVar3 != param_1) {
        iStack_28 = iVar6 - iVar2;
        iStack_2c = iVar3;
        iStack_24 = iVar6;
        iVar6 = FUN_4020a2fc(iVar4 + iVar2,iStack_28,PTR_DAT_4024b3e8,
                             *(undefined4 *)(iVar3 * 4 + iStack_30));
        if (iStack_28 < iVar6) {
          iVar6 = iStack_28;
        }
        iVar2 = iVar2 + iVar6;
        iVar6 = iStack_24;
        iVar3 = iStack_2c + 1;
      }
      iVar6 = 0x400 - iVar2;
      iVar3 = FUN_4020a2fc(iVar4 + iVar2,iVar6,DAT_4024b4e0);
      if (iVar3 < iVar6) {
        iVar6 = iVar3;
      }
      iVar2 = iVar2 + iVar6;
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I___s_4024b4e4,iVar4);
      }
      iVar6 = 0;
      uStack_38 = 0;
      local_40 = iVar4;
      iStack_3c = iVar2;
      (**(code **)(*piVar5 + 8))(&local_40,*(undefined4 *)(*piVar5 + 0xc));
      FUN_4024e0c0(*DAT_4024b060,PTR_s_ok_3ffea4ff_0x17_4024b0e8);
      (*(code *)PTR_FUN_4023cf10)(*piVar5);
      *piVar5 = iVar6;
      return;
    }
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__sending_result_time_out_4024b4d8);
    }
    FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
  }
  FUN_4024e0c0(*DAT_4024b060,PTR_s_error_3ffea87d_0x22_4024b1b0);
  return;
}
