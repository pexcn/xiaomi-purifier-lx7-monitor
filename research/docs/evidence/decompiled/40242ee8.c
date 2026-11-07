// Ghidra 12.1.4; synthetic ELF; 40242ee8

int FUN_40242ee8(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;

  if ((param_2 == 0) && (param_1 == 0)) {
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      puVar3 = PTR_s__E__Ota_url_is_null__40242eb0;
LAB_40242f0f:
      (*(code *)PTR_FUN_4023ccf8)(puVar3);
    }
LAB_40242f15:
    iVar4 = -1;
  }
  else {
    FUN_4024256c();
    *DAT_40242564 = 0x14;
    FUN_4024d5b0(*DAT_40242eb4,PTR_s_ota_progress_40242eb8,PTR_DAT_40242ebc);
    if (param_2 == 0) {
      *DAT_40242588 = 2;
      if (param_1 != 0) {
        puVar6 = (uint *)PTR_DAT_4023ccf0;
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__OTA_app_fw_begin__40242ed8);
        }
        iVar4 = (*DAT_4023d3c0)(param_1);
        iVar4 = (*(code *)PTR_FUN_4023cf0c)(iVar4 + 0x19);
        if (iVar4 == 0) {
          if (*puVar6 < 4) {
            FUN_4023f7b4();
            puVar3 = PTR_s__E__app_ctx_malloc_failed__40242edc;
            goto LAB_40242f0f;
          }
          goto LAB_40242f15;
        }
        iVar1 = (*DAT_4023d3c0)(param_1);
        (*DAT_4023d19c)(iVar4,0,iVar1 + 0x19);
        uVar2 = (*DAT_4023f16c)(iVar4 + 0x18,param_1);
        puVar3 = PTR_PTR_40242ee0;
        *(undefined4 *)(iVar4 + 0x14) = 0;
        *(undefined4 *)(iVar4 + 0x10) = 0;
        iVar1 = FUN_402445f4(uVar2,0,puVar3,iVar4);
        if (iVar1 != 0) {
          FUN_4024258c();
          FUN_40242e98(iVar4);
          if (2 < *puVar6) {
            return iVar1;
          }
          FUN_4023f7b4();
          puVar3 = PTR_s__W__OTA_failed_because_ot_httpc_s_40242ee4;
          goto LAB_402430ac;
        }
      }
    }
    else {
      puVar6 = (uint *)PTR_DAT_4023ccf0;
      if (param_1 == 0) {
        puVar5 = DAT_40242588;
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__OTA_mcu_fw_begin__40242ec8);
        }
        *puVar5 = 1;
      }
      else {
        puVar5 = DAT_40242588;
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__OTA_app_fw_and_mcu_fw_both__40242ec0);
        }
        *puVar5 = 3;
        iVar4 = (*DAT_4023d3c0)(param_1);
        iVar4 = (*(code *)PTR_FUN_4023cf0c)(iVar4 + 1);
        *DAT_40242584 = iVar4;
        if (iVar4 == 0) {
          FUN_4024258c();
          if (*puVar6 < 4) {
            FUN_4023f7b4();
            puVar3 = PTR_s__E__app_url_malloc_failed__40242ec4;
            goto LAB_40242f0f;
          }
          goto LAB_40242f15;
        }
        (*DAT_4023f16c)(iVar4,param_1);
      }
      iVar4 = (*DAT_4023d3c0)(param_2);
      iVar4 = (*(code *)PTR_FUN_4023cf0c)(iVar4 + 0x19);
      if (iVar4 == 0) {
        FUN_4024258c();
        if (*puVar6 < 4) {
          FUN_4023f7b4();
          puVar3 = PTR_s__E__mcu_ctx_malloc_failed__40242ecc;
          goto LAB_40242f0f;
        }
        goto LAB_40242f15;
      }
      iVar1 = (*DAT_4023d3c0)(param_2);
      (*DAT_4023d19c)(iVar4,0,iVar1 + 0x19);
      uVar2 = (*DAT_4023f16c)(iVar4 + 0x18,param_2);
      puVar3 = PTR_PTR_40242ed0;
      *(undefined4 *)(iVar4 + 0x14) = 0;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar1 = FUN_402445f4(uVar2,0,puVar3,iVar4);
      if (iVar1 != 0) {
        FUN_4024258c();
        FUN_40242e98(iVar4);
        if (2 < *puVar6) {
          return iVar1;
        }
        FUN_4023f7b4();
        puVar3 = PTR_s__W__OTA_failed_because_ot_httpc_s_40242ed4;
LAB_402430ac:
        (*(code *)PTR_FUN_4023ccf8)(puVar3,iVar1);
        return iVar1;
      }
    }
    iVar4 = 0;
  }
  return iVar4;
}
