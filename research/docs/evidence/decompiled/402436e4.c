// Ghidra 12.1.4; synthetic ELF; 402436e4

int FUN_402436e4(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  undefined1 uVar5;
  uint uVar6;
  uint *puVar7;
  int local_40;
  int iStack_3c;
  undefined4 uStack_30;
  uint uStack_2c;

  uVar6 = *DAT_40242588 & 0xfffffffd;
  if ((uVar6 == 1) && (*(char *)(param_1 + 8) == '\0')) {
    local_40 = DAT_40242d4c;
    iStack_3c = *(int *)(param_1 + 0xc) + -4;
    iVar2 = FUN_402426ac(&local_40,*(undefined4 *)(param_1 + 4),8);
    uVar5 = (undefined1)uVar6;
    if (iVar2 != 0) {
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return iVar2;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__write_user_fw_magic_error__r_402436c0;
      goto LAB_40243810;
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 8;
    iVar1 = DAT_40242148;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 8;
    local_40 = iVar2;
    iStack_3c = iVar2;
    iVar2 = FUN_4023fa6c(*(undefined4 *)(iVar1 + 0x28),&local_40,8);
    if (iVar2 < 0) {
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return iVar2;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__ota_write__flash_read_error_402436b8;
      goto LAB_402438c0;
    }
    if (local_40 != DAT_40242d4c) {
      iVar2 = -1;
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return -1;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__firmware_header_write_or_rea_402436bc;
      goto LAB_402438c0;
    }
    *(undefined1 *)(param_1 + 8) = uVar5;
  }
  iVar2 = FUN_402426ac(param_2,*(undefined4 *)(param_1 + 4),param_3);
  if (iVar2 != 0) {
    if (3 < *(uint *)PTR_DAT_4023ccf0) {
      return iVar2;
    }
    FUN_4023f7b4();
    puVar3 = PTR_s__E__write_user_fw_error__return___402436c4;
LAB_40243810:
    (*(code *)PTR_FUN_4023ccf8)(puVar3,iVar2);
    return iVar2;
  }
  uVar4 = param_3 + *(int *)(param_1 + 4);
  uVar6 = *DAT_40242588;
  *(uint *)(param_1 + 4) = uVar4;
  if (((uVar6 == 2) && (*(byte *)(DAT_40242148 + 0x30) == 1)) &&
     (*(char *)(DAT_40242148 + 0x31) == '\0')) {
    if (uVar4 < *(uint *)(DAT_40242148 + 0x34)) {
      FUN_4025983c(DAT_402435b0,param_2,param_3);
    }
    else {
      uStack_30 = DAT_402435b0;
      iVar2 = DAT_40242148;
      uStack_2c = (uint)*(byte *)(DAT_40242148 + 0x30);
      FUN_4025983c(DAT_402435b0,param_2,(param_3 + *(uint *)(DAT_40242148 + 0x34)) - uVar4);
      FUN_40259854(uStack_30,DAT_40242258);
      *(char *)(iVar2 + 0x31) = (char)uStack_2c;
    }
  }
  if (*(int *)(param_1 + 4) != *(int *)(param_1 + 0xc)) {
    return param_3;
  }
  puVar7 = (uint *)PTR_DAT_4023ccf0;
  if (*(uint *)PTR_DAT_4023ccf0 < 2) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__ota_write_over__update_state_402436c8);
  }
  if ((*DAT_40242588 & 0xfffffffd) == 0) {
    if ((*DAT_40242588 != 2) || (*(char *)(DAT_40242148 + 0x30) != '\0')) goto LAB_402438dc;
    if (*puVar7 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__app_crc_check_____402436d8);
    }
    iVar2 = FUN_40242ca4(0,*(int *)(param_1 + 0xc) + -4);
    if (iVar2 != 0) {
      if (3 < *puVar7) {
        return iVar2;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__app_crc_check_error_402436dc;
      goto LAB_402438c0;
    }
    if (1 < *puVar7) goto LAB_402438dc;
    FUN_4023f7b4();
    puVar3 = PTR_s__I__app_crc_check_passed____402436e0;
  }
  else {
    if (*puVar7 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__mcu_crc_check_____402436cc);
    }
    iVar2 = FUN_40242ca4(8,*(int *)(param_1 + 0xc) + -0xc);
    if (iVar2 != 0) {
      if (3 < *puVar7) {
        return iVar2;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__mcu_crc_check_error_402436d0;
LAB_402438c0:
      (*(code *)PTR_FUN_4023ccf8)(puVar3);
      return iVar2;
    }
    if (1 < *puVar7) goto LAB_402438dc;
    FUN_4023f7b4();
    puVar3 = PTR_s__I__mcu_crc_check_passed____402436d4;
  }
  (*(code *)PTR_FUN_4023ccf8)(puVar3);
LAB_402438dc:
  FUN_402434a8(2);
  return param_3;
}
