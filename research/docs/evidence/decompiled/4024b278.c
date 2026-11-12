// Ghidra 12.1.4; synthetic ELF; 4024b278

void FUN_4024b278(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  int *piVar6;
  uint *puVar7;
  undefined4 *puVar8;

  piVar6 = DAT_4024b134;
  puVar7 = (uint *)PTR_DAT_4024b19c;
  if (*DAT_4024b134 != 0) {
    uVar1 = FUN_40241ba8(*(undefined4 *)(*DAT_4024b134 + 4));
    if (uVar1 < *(uint *)PTR_DAT_4024b19c) {
      uVar2 = *DAT_4024b060;
      puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
      goto LAB_4024b312;
    }
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__json_get_down1_time_out_4024b260);
    }
    FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
    puVar7 = (uint *)PTR_DAT_4024b19c;
  }
  while( true ) {
    iVar3 = FUN_4024cad0(*DAT_4024b268);
    *piVar6 = iVar3;
    if ((iVar3 == 0) || (uVar1 = FUN_40241ba8(*(undefined4 *)(iVar3 + 4)), uVar1 < *puVar7)) break;
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__json_get_down2_time_out_4024b264);
    }
    FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
  }
  piVar5 = (int *)*piVar6;
  if (piVar5 != (int *)0x0) {
    if ((*piVar5 == 0) || (*piVar5 == 1)) {
      FUN_4024e0c0(*DAT_4024b060,PTR_s_json_down__s_4024b270,piVar5 + 0x15);
    }
    else {
      puVar8 = DAT_4024b060;
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)
                  (PTR_s__E__unknown_down_command_type____4024b274,*(undefined4 *)*piVar6);
      }
      FUN_4024e0c0(*puVar8,PTR_s_json_down_none_4024b26c);
    }
    if (*piVar6 == 0) {
      return;
    }
    iVar3 = *(int *)(*piVar6 + 8);
    if (iVar3 != 0) {
      return;
    }
    (*(code *)PTR_FUN_4023cf10)();
    *piVar6 = iVar3;
    return;
  }
  uVar2 = *DAT_4024b060;
  puVar4 = PTR_s_json_down_none_4024b26c;
LAB_4024b312:
  FUN_4024e0c0(uVar2,puVar4);
  return;
}
