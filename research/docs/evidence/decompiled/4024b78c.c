// Ghidra 12.1.4; synthetic ELF; 4024b78c

void FUN_4024b78c(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 local_40;
  int iStack_3c;
  undefined4 uStack_38;
  int iStack_30;

  uVar4 = *DAT_4024b3e0;
  puVar3 = DAT_4024b060;
  if ((*DAT_4024b134 == 0) || (param_1 < 2)) goto LAB_4024b801;
  iStack_30 = DAT_40244634;
  piVar2 = DAT_4024b134;
  if (param_1 == 2) {
LAB_4024b7ce:
    iVar5 = iStack_30;
  }
  else {
    iVar5 = FUN_4020a250(*(undefined4 *)(param_2 + 8));
    if ((DAT_40244638 <= iVar5) || (iVar5 < iStack_30)) goto LAB_4024b7ce;
  }
  iStack_30 = iVar5;
  uVar1 = FUN_40241ba8(*(undefined4 *)(*piVar2 + 4));
  if (uVar1 < *(uint *)PTR_DAT_4024b19c) {
    iStack_3c = FUN_4020a2fc(uVar4,0x400,PTR_s___error____code___d__message___s_4024b784,iStack_30,
                             *(undefined4 *)(param_2 + 4));
    if (0x400 < iStack_3c) {
      iStack_3c = 0x400;
    }
    if (*(uint *)PTR_DAT_4023ccf0 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I___s_4024b788,uVar4);
    }
    iVar5 = 0;
    uStack_38 = 0;
    local_40 = uVar4;
    (**(code **)(*piVar2 + 8))(&local_40,*(undefined4 *)(*piVar2 + 0xc));
    FUN_4024e0c0(*puVar3,PTR_s_ok_3ffea4ff_0x17_4024b0e8);
    (*(code *)PTR_FUN_4023cf10)(*piVar2);
    *piVar2 = iVar5;
    return;
  }
  if (*(uint *)PTR_DAT_4023ccf0 < 4) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__sending_error_time_out_4024b780);
  }
  FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
LAB_4024b801:
  FUN_4024e0c0(*puVar3,PTR_s_error_3ffea87d_0x22_4024b1b0);
  return;
}
