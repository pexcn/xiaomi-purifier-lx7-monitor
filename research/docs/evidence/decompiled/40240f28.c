// Ghidra 12.1.4; synthetic ELF; 40240f28

int FUN_40240f28(int param_1,uint param_2,int param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined *puVar9;
  undefined1 auStack_70 [64];
  int iStack_30;
  undefined *puStack_2c;
  uint uStack_28;

  iStack_30 = param_3;
  uVar1 = FUN_40241bfc();
  uVar2 = FUN_4020a2fc(param_1,param_2,PTR_s__life___u__40240ed4,uVar1);
  if (param_2 < uVar2) {
    uVar2 = param_2;
  }
  uVar7 = param_2 - uVar2;
  uVar3 = FUN_4020a2fc(param_1 + uVar2,uVar7,PTR_s__token____40240ed8);
  if (uVar3 < uVar7) {
    uVar7 = uVar3;
  }
  iVar8 = uVar7 + uVar2;
  iVar4 = FUN_4024a074(PTR_DAT_402400cc);
  if ((iVar4 == 0) && (*(uint *)PTR_DAT_4023ccf0 < 4)) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__not_find_otd_in_dev__40240edc);
  }
  iVar6 = DAT_40240450;
  if (*(int *)(iVar4 + 0x30) != 0) {
    iVar6 = *(int *)(iVar4 + 0x30) + 0x234;
  }
  iVar4 = FUN_4020984c(param_1 + iVar8,param_2 - iVar8,iVar6,0x10,0);
  iVar4 = iVar4 + iVar8;
  uVar7 = param_2 - iVar4;
  uVar2 = FUN_4020a2fc(param_1 + iVar4,uVar7,PTR_DAT_40240ee0);
  if (uVar7 < uVar2) {
    uVar2 = uVar7;
  }
  iVar4 = uVar2 + iVar4;
  puVar9 = PTR_DAT_40240ee8;
  iVar8 = FUN_40240b88(param_1 + iVar4,param_2 - iVar4,PTR_DAT_40240ee4,PTR_DAT_40240ee8);
  iVar4 = iVar4 + iVar8;
  iVar8 = FUN_402409ec(param_1 + iVar4,param_2 - iVar4,PTR_s_fw_ver_3ffe971e_5_40240eec,puVar9);
  iVar4 = iVar4 + iVar8;
  uStack_28 = param_2 - iVar4;
  uVar7 = FUN_4020a2fc(param_1 + iVar4,uStack_28,PTR_s__hw_ver____s___40240ef0,
                       PTR_s_ESP8266_40240ef4);
  uVar2 = uStack_28;
  if (uVar7 < uStack_28) {
    uVar2 = uVar7;
  }
  iVar4 = uVar2 + iVar4;
  puVar5 = (undefined *)FUN_4023f3d8();
  if (puVar5 != (undefined *)0x0) {
    if (*(int *)PTR_DAT_4023ccf0 == 0) {
      puStack_2c = puVar5;
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__got_bindkey___s_40240ef8,puStack_2c);
      puVar5 = puStack_2c;
    }
    uStack_28 = param_2 - iVar4;
    uVar2 = FUN_4020a2fc(param_1 + iVar4,uStack_28,PTR_s__bindkey____s___40240efc,puVar5);
    if (uStack_28 < uVar2) {
      uVar2 = uStack_28;
    }
    iVar4 = iVar4 + uVar2;
  }
  puVar5 = PTR_DAT_4023d7e0;
  if (*(int *)PTR_DAT_4023d7e0 != 0 || *(int *)(PTR_DAT_4023d7e0 + 4) != 0) {
    puStack_2c = PTR_DAT_4023d7e0;
    FUN_4024d01c(*(int *)PTR_DAT_4023d7e0,*(int *)(PTR_DAT_4023d7e0 + 4),auStack_70);
    uStack_28 = param_2 - iVar4;
    uVar2 = FUN_4020a2fc(param_1 + iVar4,uStack_28,PTR_DAT_40240f00,auStack_70);
    if (uStack_28 < uVar2) {
      uVar2 = uStack_28;
    }
    iVar4 = iVar4 + uVar2;
    puVar5 = puStack_2c;
  }
  if (puVar5[8] != '\0') {
    uStack_28 = param_2 - iVar4;
    uVar2 = FUN_4020a2fc(param_1 + iVar4,uStack_28,PTR_s__channel____s___40240f04,PTR_DAT_40240f08);
    if (uStack_28 < uVar2) {
      uVar2 = uStack_28;
    }
    iVar4 = iVar4 + uVar2;
  }
  iVar8 = FUN_40240c10(param_1 + iVar4,param_2 - iVar4,PTR_s_model_3ffe95c2_0xe_40240f0c,puVar9);
  uStack_28 = iVar8 + iVar4;
  iVar4 = FUN_40240cec(param_1 + uStack_28,param_2 - uStack_28,PTR_s_mcu_fw_ver_40240f10,puVar9);
  uStack_28 = uStack_28 + iVar4;
  iVar4 = FUN_40240d94(param_1 + uStack_28,param_2 - uStack_28,PTR_s_wifi_fw_ver_40240f14,puVar9);
  uStack_28 = uStack_28 + iVar4;
  iVar4 = FUN_40240e14(param_1 + uStack_28,param_2 - uStack_28,PTR_DAT_40240f18,PTR_DAT_40240f1c);
  uStack_28 = uStack_28 + iVar4;
  iVar4 = FUN_40240a88(param_1 + uStack_28,param_2 - uStack_28,PTR_s_netif_40240f20,puVar9);
  uStack_28 = uStack_28 + iVar4;
  puStack_2c = (undefined *)(param_1 + uStack_28);
  uVar2 = param_2 - uStack_28;
  uVar1 = FUN_40204440();
  uVar7 = FUN_4020a2fc(puStack_2c,uVar2,PTR_s__mmfree___u_40240f24,uVar1);
  if (uVar7 < uVar2) {
    uVar2 = uVar7;
  }
  iVar4 = uVar2 + uStack_28;
  if (iStack_30 != 0) {
    param_2 = param_2 - iVar4;
    uVar2 = FUN_4020a2fc(param_1 + iVar4,param_2,PTR_s__s_3ffea401_0xa_402409e8,iStack_30);
    if (param_2 < uVar2) {
      uVar2 = param_2;
    }
    iVar4 = iVar4 + uVar2;
  }
  return iVar4;
}
