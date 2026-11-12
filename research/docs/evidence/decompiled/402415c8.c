// Ghidra 12.1.4; synthetic ELF; 402415c8

int FUN_402415c8(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  uint local_c0;
  undefined1 auStack_bc [64];
  int aiStack_7c [5];
  undefined1 auStack_68 [24];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  int *piStack_44;
  int iStack_40;
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [8];
  undefined4 uStack_30;
  int iStack_2c;
  int *piStack_28;
  int iStack_24;

  uStack_50 = DAT_4020a138;
  iVar8 = 0;
  uStack_4c = DAT_4020a138;
  iStack_40 = 0;
  uStack_30 = param_3;
  iVar1 = (*(code *)PTR_FUN_4023cf0c)(0x62);
  if (iVar1 == iVar8) {
    puVar5 = PTR_s_no_mem_4023fc84;
    iVar8 = -5;
  }
  else {
    (*DAT_4023d19c)(iVar1,iVar8,0x62);
    piVar2 = (int *)FUN_4024ac20(*param_1,param_1[2],PTR_s_ssid_3ffe8ea9_8_40241354,iVar1,0x21,
                                 auStack_38);
    puVar5 = PTR_s_Invalid_param__402400c8;
    iVar8 = DAT_402400c4;
    if (piVar2 == (int *)0x0) {
      iStack_2c = iVar1 + 0x21;
      piStack_28 = piVar2;
      FUN_4024ac20(*param_1,param_1[2],PTR_s_passwd_40241584,iStack_2c,0x42,auStack_3c);
      piStack_44 = piStack_28;
      iVar8 = FUN_4024ac20(*param_1,param_1[2],PTR_s_channel_40241588,PTR_DAT_40240f08,0x21,
                           &piStack_44);
      if (iVar8 == 0) {
        PTR_DAT_4023d7e0[0x28] = 0;
      }
      else {
        PTR_DAT_4023d7e0[8] = (char)piStack_28;
      }
      iVar8 = 0;
      local_c0 = 0;
      (*DAT_4023d19c)(auStack_bc,0,0x3d);
      aiStack_7c[0] = iVar8;
      iVar3 = FUN_4024ac20(*param_1,param_1[2],PTR_s_bind_key_4024158c,&local_c0,0x41,aiStack_7c);
      if (iVar3 == iVar8) {
        iVar8 = FUN_4023f3e8(&local_c0);
        piVar2 = (int *)PTR_DAT_4023ccf0;
        if ((iVar8 != 0) && (*(uint *)PTR_DAT_4023ccf0 < 3)) {
          piStack_28 = (int *)PTR_DAT_4023ccf0;
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__Failed_to_set_bindkey__ret___40241590,iVar8);
          piVar2 = piStack_28;
        }
        if (*piVar2 == 0) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__setting_bindkey___s_40241594,&local_c0);
        }
      }
      iVar3 = FUN_4024ab58(*param_1,param_1[2],DAT_40241598,&uStack_50);
      uVar6 = DAT_4020a138;
      uVar7 = DAT_4020a138;
      if (((iVar3 == 0) &&
          (iVar3 = FUN_4023fe28(uStack_50,uStack_4c), uVar6 = uStack_50, uVar7 = uStack_4c,
          iVar3 != 0)) && (*(uint *)PTR_DAT_4023ccf0 < 4)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__uid_config_in_psm_error_4024159c);
        uVar6 = uStack_50;
        uVar7 = uStack_4c;
      }
      FUN_4023d7e4(uVar6,uVar7);
      iVar3 = FUN_4024a87c(*param_1,param_1[2],PTR_s_wifi_config_402415a0);
      local_c0 = local_c0 & 0xff000000;
      if (((iVar3 != 0) &&
          (iVar3 = FUN_4024ac20(*param_1,iVar3,PTR_DAT_402415a4,&local_c0,3,0), iVar3 == 0)) &&
         (FUN_4023f6ec(&local_c0), *(int *)PTR_DAT_4023ccf0 == 0)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__setting_cc___s_402415a8,&local_c0);
      }
      iVar3 = FUN_4024aba8(*param_1,param_1[2],DAT_402415ac,&iStack_40);
      if (iVar3 == 0) {
        if (DAT_4023f7ac < (uint)(iStack_40 + DAT_4023f7a8)) {
          iStack_40 = DAT_4023f7a4;
        }
        *(int *)(PTR_DAT_4023d7e0 + 0x2c) = iStack_40;
        iVar3 = FUN_4023fef0();
        if ((iVar3 != 0) && (*(uint *)PTR_DAT_4023ccf0 < 4)) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__gmt_offset_in_psm_error_402415b0);
        }
      }
      (*DAT_4023d19c)(auStack_68,0,0x14);
      uStack_48 = 0;
      iVar3 = FUN_4024ac20(*param_1,param_1[2],PTR_s_country_domain_40240320,auStack_68,3,&uStack_48
                          );
      if (iVar3 == 0) {
        FUN_40240324(auStack_68);
        iVar4 = FUN_4024a074(PTR_DAT_402400cc);
        if (iVar4 != 0) {
          iStack_24 = *(int *)(iVar4 + 0x34);
          piStack_28 = *(int **)(iVar4 + 0x30);
          (*DAT_4023d19c)(aiStack_7c,iVar3,0x14);
          (*DAT_4023d19c)(&local_c0,iVar3,0x14);
          FUN_40204510(PTR_s_ott_io_mi_com_402415b4,aiStack_7c,0x14);
          FUN_40204510(PTR_s_ot_io_mi_com_402415b8,&local_c0,0x14);
          piVar2 = piStack_28 + 0x15;
          (*DAT_4023f16c)(piVar2,auStack_68);
          FUN_4022e8a8(piVar2,PTR_s___3ffea7dc_0x2b_402415bc);
          FUN_4022e8a8(piVar2,&local_c0);
          iVar3 = iStack_24 + 0x4f9;
          (*DAT_4023f16c)(iVar3,auStack_68);
          FUN_4022e8a8(iVar3,PTR_s___3ffea7dc_0x2b_402415bc);
          FUN_4022e8a8(iVar3,aiStack_7c);
        }
      }
      iVar3 = FUN_4023d764();
      iVar4 = FUN_4024136c(iVar1,iStack_2c);
      if (iVar4 == 0) {
        if (iVar3 != 0) {
          FUN_402446ac(param_2,uStack_30,iVar8);
          (*(code *)PTR_FUN_4023cf10)(iVar1);
          goto LAB_40241913;
        }
        iVar4 = FUN_402083b0(PTR_s_ap2staTmr_4024143c,300,0,iVar1,PTR_FUN_40241440);
        if (iVar4 != 0) {
          piStack_28 = (int *)iVar4;
          uVar6 = FUN_40207ca0();
          FUN_4020840c(piStack_28,iVar3,uVar6,iVar3,iVar3);
          FUN_402446ac(param_2,uStack_30,iVar8);
          return iVar8;
        }
        puVar5 = PTR_s_Config_router_fail_4024157c;
        iVar8 = DAT_40241580;
        if (*(uint *)PTR_DAT_4023ccf0 < 4) {
          FUN_4023f7b4();
          puVar5 = PTR_s__E__Create_station_timer_failed__402415c4;
          goto LAB_4024187b;
        }
      }
      else {
        puVar5 = PTR_s_Config_router_fail_4024157c;
        iVar8 = DAT_40241580;
        if (*(uint *)PTR_DAT_4023ccf0 < 4) {
          FUN_4023f7b4();
          puVar5 = PTR_s__E__Set_ap_to_psm_failed__402415c0;
LAB_4024187b:
          (*(code *)PTR_FUN_4023ccf8)(puVar5);
          puVar5 = PTR_s_Config_router_fail_4024157c;
          iVar8 = DAT_40241580;
        }
      }
    }
  }
  FUN_40244640(param_2,uStack_30,iVar8,puVar5);
  if (iVar1 != 0) {
    (*(code *)PTR_FUN_4023cf10)(iVar1);
  }
  FUN_402403bc();
LAB_40241913:
  FUN_402425bc();
  return iVar8;
}
