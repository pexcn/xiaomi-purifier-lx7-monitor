// Ghidra 12.1.4; synthetic ELF; 40243100

int FUN_40243100(undefined4 *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  undefined4 local_40;
  undefined4 uStack_3c;
  int iStack_30;
  undefined4 uStack_2c;

  iVar3 = 0;
  iVar4 = *(int *)(param_3 + 8);
  local_40 = 0;
  uStack_3c = 0;
  iStack_30 = param_3;
  uStack_2c = param_2;
  iVar1 = FUN_40265324(param_3);
  if (((uint)*(ushort *)(iVar4 + 0x10) == (DAT_402430d4 & 0xffff)) &&
     (iVar1 = (*DAT_4023dedc)(iVar1 + 0x28,&local_40,8), iVar1 != iVar3)) {
    FUN_402446ac(uStack_2c,iStack_30,0xffffffff);
    return iVar3;
  }
  if (*(int *)PTR_DAT_4023ccf0 == 0) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__a__a__a__there_is_ota_commin_402430d8);
  }
  uVar6 = (uint)*DAT_40242568;
  if (uVar6 != 0) {
    FUN_402446ac(uStack_2c,iStack_30,0);
    return 0;
  }
  uVar2 = (*(code *)PTR_FUN_4023cf0c)(0x200);
  if (uVar2 == 0) {
    iVar1 = -5;
    puVar5 = PTR_s_no_mem_402430d0;
    goto LAB_4024329d;
  }
  iVar3 = (*(code *)PTR_FUN_4023cf0c)(0x200);
  if (iVar3 == 0) {
    iVar1 = -5;
    puVar5 = PTR_s_no_mem_402430d0;
LAB_40243282:
    (*(code *)PTR_FUN_4023cf10)(uVar2);
  }
  else {
    iVar1 = FUN_4024ac20(*param_1,param_1[2],PTR_s_app_url_402430dc,uVar2,0x200,uVar6);
    if (iVar1 != 0) {
      (*(code *)PTR_FUN_4023cf10)(uVar2);
      uVar2 = uVar6;
    }
    iVar1 = FUN_4024ac20(*param_1,param_1[2],PTR_s_mcu_url_402430e0,iVar3,0x200,0);
    if (iVar1 != 0) {
      (*(code *)PTR_FUN_4023cf10)(iVar3);
      iVar3 = 0;
    }
    iVar4 = FUN_4024ac90(*param_1,param_1[2],PTR_s_signed_file_402430e4,DAT_402430e8);
    iVar1 = DAT_40242148;
    if (iVar4 != 0) {
      *(undefined1 *)(DAT_40242148 + 0x30) = 0;
    }
    if (*(char *)(iVar1 + 0x30) == '\x01') {
      iVar4 = FUN_4024ab80(*param_1,param_1[2],PTR_s_original_length_3ffe9963_5_402430ec,
                           DAT_402430f0);
      if (iVar4 == 0) {
        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)
                    (PTR_s__I__ota_verify_param__signed_fil_402430f4,*(undefined1 *)(iVar1 + 0x30),
                     *(undefined4 *)(iVar1 + 0x34));
        }
        (*DAT_4023d19c)(DAT_402430f8,0,0x90);
        *(undefined1 *)(iVar1 + 0x31) = 0;
        goto LAB_40243220;
      }
      iVar1 = -10;
      puVar5 = PTR_s_miss_original_length_402430cc;
    }
    else {
LAB_40243220:
      iVar1 = FUN_40242ee8(uVar2,iVar3);
      if (iVar1 == 0) {
        FUN_402446ac(uStack_2c,iStack_30,0);
        if (uVar2 != 0) {
          (*(code *)PTR_FUN_4023cf10)(uVar2);
        }
        if (iVar3 == 0) {
          return iVar1;
        }
        (*(code *)PTR_FUN_4023cf10)(iVar3);
        return iVar1;
      }
      puVar5 = PTR_s_ota_failed_402430c8;
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__update_fw_failed_in_httpc_st_402430fc,iVar1);
      }
    }
    if (uVar2 != 0) goto LAB_40243282;
  }
  if (iVar3 != 0) {
    (*(code *)PTR_FUN_4023cf10)(iVar3);
  }
LAB_4024329d:
  FUN_4024258c();
  FUN_40244640(uStack_2c,iStack_30,iVar1,puVar5);
  *DAT_40242564 = 0;
  return iVar1;
}
