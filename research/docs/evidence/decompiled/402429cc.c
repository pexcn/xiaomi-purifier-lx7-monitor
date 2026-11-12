// Ghidra 12.1.4; synthetic ELF; 402429cc

int FUN_402429cc(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  uint *puVar8;
  char local_90 [64];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [7];
  undefined1 uStack_39;
  undefined1 uStack_38;
  undefined1 uStack_37;
  undefined1 uStack_36;
  char *pcStack_30;

  FUN_4024bf9c();
  FUN_40244184(0);
  (*DAT_4023c0bc)(auStack_50,PTR_s_down_update_fw_402429a0,0x10);
  (*DAT_4023c0bc)(auStack_40,PTR_s_error_402429a4,7);
  uVar6 = 0;
  uStack_39 = *PTR_DAT_402429a8;
  uStack_38 = PTR_DAT_402429a8[1];
  uStack_37 = PTR_DAT_402429a8[2];
  uStack_36 = PTR_DAT_402429a8[3];
  uVar1 = FUN_40241b60();
  do {
    pcStack_30 = local_90 + uVar6;
    iVar2 = FUN_40244130(pcStack_30);
    if (iVar2 == 1) {
      if (*pcStack_30 == '\r') {
        iVar2 = (*DAT_40241450)(local_90,PTR_s_get_down_3ffea8a5_5_402429ac,8);
        if (iVar2 == 0) {
          piVar7 = (int *)PTR_DAT_4023ccf0;
          uVar3 = (*DAT_4023d3c0)(auStack_50);
          FUN_40244068(0,auStack_50,uVar3);
          if (*piVar7 == 0) {
            FUN_4023f7b4();
            puVar4 = PTR_s__D__updatefw_sent_402429b0;
LAB_40242ae3:
            (*(code *)PTR_FUN_4023ccf8)(puVar4);
          }
        }
        else {
          puVar8 = (uint *)PTR_DAT_4023ccf0;
          iVar2 = (*DAT_40241450)(local_90,PTR_s_result__ready__402429b4,0xe);
          if (iVar2 == 0) {
            if (*puVar8 == 0) {
              FUN_4023f7b4();
              (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__result__ready__received__402429b8);
            }
            uVar1 = (*DAT_4023d3c0)(&uStack_39);
            FUN_40244068(0,&uStack_39,uVar1);
            iVar2 = FUN_40242850(param_1 + 8,param_2);
            if (-1 < iVar2) {
              FUN_4024270c();
              goto LAB_40242b53;
            }
            if (*puVar8 < 4) {
              FUN_4023f7b4();
              (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__mcu_ota_from_flash_failed__d_402429c8,iVar2);
            }
            goto LAB_40242b35;
          }
          uVar3 = (*DAT_4023d3c0)(auStack_40);
          FUN_40244068(0,auStack_40,uVar3);
          if (*puVar8 == 0) {
            FUN_4023f7b4();
            puVar4 = PTR_s__D__error_sent_402429bc;
            goto LAB_40242ae3;
          }
        }
        local_90[0] = '\0';
      }
      else {
        uVar6 = uVar6 + 1;
        if (uVar6 < 0x40) goto LAB_40242afc;
      }
      uVar6 = 0;
    }
LAB_40242afc:
    uVar5 = FUN_40241ba8(uVar1);
  } while (uVar5 < 0x7d1);
  puVar8 = (uint *)PTR_DAT_4023ccf0;
  if (*(uint *)PTR_DAT_4023ccf0 < 4) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__mcu_ota_handshake_timeout_402429c0);
  }
  if (*puVar8 < 4) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__set_mcu_to_ready_status_fail_402429c4);
  }
LAB_40242b35:
  iVar2 = -1;
LAB_40242b53:
  FUN_4024420c(0);
  FUN_4024bdec();
  return iVar2;
}
