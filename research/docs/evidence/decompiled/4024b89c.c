// Ghidra 12.1.4; synthetic ELF; 4024b89c

void FUN_4024b89c(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  undefined *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  uint *puVar9;
  char *local_20;
  char *apcStack_1c [6];

  piVar7 = DAT_4024b134;
  puVar6 = DAT_4024b268;
  puVar9 = (uint *)PTR_DAT_4024b19c;
  if (*DAT_4024b134 == 0) {
LAB_4024b938:
    while( true ) {
      iVar3 = FUN_4024cad0(*puVar6);
      *piVar7 = iVar3;
      if (iVar3 == 0) break;
      uVar1 = FUN_40241ba8(*(undefined4 *)(iVar3 + 4));
      if (uVar1 < *puVar9) {
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__deQ__s_4024b878,*piVar7 + 0x54);
        }
        break;
      }
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__get_down2_time_out_4024b87c);
      }
      FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
    }
    puVar6 = (undefined4 *)*piVar7;
    if (puVar6 == (undefined4 *)0x0) {
      FUN_4024e0c0(*DAT_4024b060,DAT_4024b880);
    }
    else {
      pcVar4 = (char *)*puVar6;
      puVar8 = DAT_4024b060;
      if (pcVar4 == (char *)0x0) {
        local_20 = pcVar4;
        apcStack_1c[0] = pcVar4;
        FUN_4024cd0c(puVar6 + 0x15,apcStack_1c,&local_20);
        if ((apcStack_1c[0] == (char *)0x0) || (*apcStack_1c[0] == '\0')) {
LAB_4024ba01:
          if (*piVar7 != 0) {
            FUN_4024b13c(DAT_402400b8,PTR_s_Invalid_json__4024b898);
          }
          uVar2 = *puVar8;
          puVar5 = DAT_4024b880;
          goto LAB_4024ba13;
        }
        if ((local_20 == (char *)0x0) || (*local_20 == '\0')) {
          puVar9 = (uint *)PTR_DAT_4023ccf0;
          FUN_4024e0c0(*puVar8,PTR_s_down__s_3ffea401_5_4024b884);
          if (*puVar9 < 2) {
            FUN_4023f7b4();
            puVar5 = PTR_s__I__tou_send_down__s_4024b888;
            pcVar4 = apcStack_1c[0];
            goto LAB_4024b9e8;
          }
        }
        else {
          puVar9 = (uint *)PTR_DAT_4023ccf0;
          FUN_4024e0c0(*puVar8,PTR_s_down__s__s_4024b88c);
          if (*puVar9 < 2) {
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)
                      (PTR_s__I__tou_send_down__s__s_4024b890,apcStack_1c[0],local_20);
          }
        }
      }
      else {
        if (pcVar4 != (char *)0x1) goto LAB_4024ba01;
        FUN_4024e0c0(*DAT_4024b060,PTR_s_down__s_3ffea401_5_4024b884,puVar6 + 0x15);
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          pcVar4 = (char *)(*piVar7 + 0x54);
          puVar5 = PTR_s__I__tou_send_down__s_4024b894;
LAB_4024b9e8:
          (*(code *)PTR_FUN_4023ccf8)(puVar5,pcVar4);
        }
      }
    }
    if ((*piVar7 != 0) && (iVar3 = *(int *)(*piVar7 + 8), iVar3 == 0)) {
      (*(code *)PTR_FUN_4023cf10)();
      *piVar7 = iVar3;
    }
  }
  else {
    uVar1 = FUN_40241ba8(*(undefined4 *)(*DAT_4024b134 + 4));
    if (*(uint *)PTR_DAT_4024b19c <= uVar1) {
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__get_down1_time_out_4024b874);
      }
      FUN_4024b13c(DAT_4024b1a4,PTR_s_UART_timeout_4024b1a8);
      puVar6 = DAT_4024b268;
      puVar9 = (uint *)PTR_DAT_4024b19c;
      goto LAB_4024b938;
    }
    uVar2 = *DAT_4024b060;
    puVar5 = PTR_s_error_3ffea87d_0x22_4024b1b0;
LAB_4024ba13:
    FUN_4024e0c0(uVar2,puVar5);
  }
  return;
}
