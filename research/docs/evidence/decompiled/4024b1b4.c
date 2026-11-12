// Ghidra 12.1.4; synthetic ELF; 4024b1b4

void FUN_4024b1b4(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;

  puVar5 = DAT_4024b060;
  if ((*DAT_4024b134 != 0) && (1 < param_1)) {
    uVar3 = *(undefined4 *)(param_2 + 4);
    piVar2 = DAT_4024b134;
    uVar1 = FUN_40241ba8(*(undefined4 *)(*DAT_4024b134 + 4));
    if (uVar1 < *(uint *)PTR_DAT_4024b19c) {
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I___s_4024b1ac,uVar3);
      }
      local_20 = uVar3;
      uStack_1c = (*DAT_4023d3c0)(uVar3);
      iVar4 = 0;
      uStack_18 = 0;
      (**(code **)(*piVar2 + 8))(&local_20,*(undefined4 *)(*piVar2 + 0xc));
      FUN_4024e0c0(*puVar5,PTR_s_ok_3ffea4ff_0x17_4024b0e8);
      (*(code *)PTR_FUN_4023cf10)(*piVar2);
      *piVar2 = iVar4;
      return;
    }
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__sending_result_time_out_4024b1a0);
    }
    FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
  }
  FUN_4024e0c0(*puVar5,PTR_s_error_3ffea87d_0x22_4024b1b0);
  return;
}
