// Ghidra 12.1.4; synthetic ELF; 402488f4

undefined1 * FUN_402488f4(int param_1,int param_2,int param_3,char param_4,int param_5)

{
  undefined2 uVar1;
  undefined1 uVar2;
  int iVar3;
  int *piVar4;
  code *pcVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined *puVar8;
  undefined1 *puVar9;
  char *pcVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint *puVar14;
  undefined4 local_170;
  undefined1 *puStack_16c;
  int iStack_168;
  undefined1 auStack_15c [16];
  undefined1 auStack_14c [16];
  undefined1 auStack_13c [16];
  char acStack_12c [66];
  undefined2 auStack_ea [8];
  undefined1 auStack_da [48];
  undefined1 auStack_aa [32];
  undefined1 auStack_8a [34];
  int iStack_68;
  int iStack_64;
  int *piStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined1 *puStack_44;
  char *pcStack_40;
  undefined1 *puStack_3c;
  undefined1 *puStack_38;
  int iStack_34;
  uint uStack_30;
  int iStack_2c;
  undefined4 *puStack_28;

  uStack_30 = (uint)(param_4 != '\0');
  if ((param_4 != '\0') && (param_5 == 0)) {
    puStack_38 = (undefined1 *)0xffffffff;
    if (3 < *(uint *)PTR_DAT_4023ccf0) {
      return (undefined1 *)0xffffffff;
    }
    FUN_4023f7b4();
    puVar8 = PTR_s__E__neighbor_null__2_40248888;
LAB_40248967:
    (*(code *)PTR_FUN_4023ccf8)(puVar8);
    return puStack_38;
  }
  iStack_34 = (*(code *)PTR_FUN_4023cf0c)(DAT_40216e34);
  if (iStack_34 == 0) {
    puStack_38 = (undefined1 *)0xfffffffb;
    if (2 < *(uint *)PTR_DAT_4023ccf0) {
      return (undefined1 *)0xfffffffb;
    }
    FUN_4023f7b4();
    puVar8 = PTR_s__W__Json_alloc_err__4024888c;
    goto LAB_40248967;
  }
  param_2 = param_2 + 0x20;
  uVar11 = (uint)*(ushort *)(param_3 + 2);
  FUN_40265704(&local_170);
  iVar12 = uVar11 - 0x20;
  puStack_38 = (undefined1 *)FUN_40265408(&local_170,param_2,iVar12,iStack_34,200);
  if (puStack_38 != (undefined1 *)0x0) {
    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__otu_down_req_json_parse_err__40248890,puStack_38);
    }
    puStack_38 = (undefined1 *)0xffffffff;
    goto LAB_40248fd0;
  }
  *(undefined4 *)((int)puStack_16c * 0xc + iStack_34) = 0;
  iStack_54 = iStack_34;
  iStack_5c = param_2;
  iStack_58 = iVar12;
  puStack_44 = puStack_38;
  iVar12 = FUN_4024ab80(param_2,iStack_34,PTR_DAT_40248894,&puStack_44);
  if (iVar12 != 0) {
    puStack_44 = puStack_38;
  }
  iVar12 = FUN_4024a87c(param_2,iStack_34,PTR_s_method_40247a6c);
  iStack_2c = FUN_4024a87c(param_2,iStack_34,PTR_DAT_40248898);
  if (iVar12 == 0) {
    if (puStack_44 == (undefined1 *)0x0) goto LAB_40248fd0;
    puVar14 = (uint *)PTR_DAT_4023ccf0;
    if (*(uint *)PTR_DAT_4023ccf0 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__otu_valid_up_ack__402488e8);
    }
    puVar9 = puStack_44;
    (*DAT_4023d19c)(&local_170,0,0x10);
    puStack_16c = puVar9;
    FUN_402653d0(param_1,PTR_LAB_4024889c,&local_170);
    if (iStack_168 != 0) {
      iVar12 = iStack_168;
      if (*(int *)(iStack_168 + 0xc) != 0) {
        iVar3 = *(int *)(param_1 + 0x214);
        iVar13 = FUN_40241bd8();
        *(int *)(param_1 + 0x214) = iVar13 + iVar3;
      }
      *(int *)(param_1 + 0x210) = *(int *)(param_1 + 0x210) + 1;
      FUN_4024a258(*(undefined4 *)(param_1 + 4),iVar12);
      (**(code **)(iVar12 + 0x24))(&iStack_5c,*(undefined4 *)(iVar12 + 0x28));
      if (*(int *)(iVar12 + 0x18) != 0) {
        (*(code *)PTR_FUN_4023cf10)();
      }
      if (*(char *)(iVar12 + 0x2d) == '\0') {
        iVar13 = FUN_40241bd8(*(undefined4 *)(iVar12 + 0xc));
        *(int *)(param_1 + 0x204) = *(int *)(param_1 + 0x204) + 1;
        if (*(int *)(param_1 + 500) == 0) {
          *(int *)(param_1 + 500) = iVar13;
        }
        if (*(int *)(param_1 + 0x1f8) == 0) {
          *(int *)(param_1 + 0x1f8) = iVar13;
        }
        uVar6 = (*DAT_40240608)(iVar13 + *(int *)(param_1 + 500) * 9,10);
        *(undefined4 *)(param_1 + 500) = uVar6;
        uVar6 = (*DAT_40240608)(iVar13 + *(int *)(param_1 + 0x1f8) * 99,100);
        *(undefined4 *)(param_1 + 0x1f8) = uVar6;
        if (*puVar14 < 3) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__otu_sess_elapsed__u__402488ec,iVar13);
        }
      }
      FUN_40265394(param_1,iVar12);
      FUN_4024a698(iVar12);
      goto LAB_40248fd0;
    }
    if (2 < *puVar14) goto LAB_40248fd0;
    FUN_4023f7b4();
    puVar8 = PTR_s__W__otu_no_session_resp_id__u__402488f0;
LAB_40248fca:
    (*(code *)PTR_FUN_4023ccf8)(puVar8,puVar9);
    goto LAB_40248fd0;
  }
  puStack_28 = (undefined4 *)((int)*(short *)(iVar12 + 8) - (int)*(short *)(iVar12 + 6));
  if ((undefined4 *)0x1f < puStack_28) {
    puStack_28 = (undefined4 *)0x1f;
  }
  (*DAT_4023c0bc)(auStack_8a,param_2 + *(short *)(iVar12 + 6),puStack_28);
  puVar9 = puStack_44;
  auStack_8a[(int)puStack_28] = 0;
  if (puVar9 != (undefined1 *)0x0) {
    (*DAT_4023d19c)(&local_170,0,0x10);
    local_170 = 1;
    puStack_16c = puVar9;
    FUN_402653d0(param_1,PTR_LAB_4024889c,&local_170);
    if (iStack_168 != 0) {
      FUN_4024f0f8(param_1,*(undefined4 *)(iStack_168 + 0x18),*(undefined2 *)(iStack_168 + 0x14),
                   iStack_168 + 0x1c,*(undefined2 *)(iStack_168 + 0x20));
      if (2 < *(uint *)PTR_DAT_4023ccf0) goto LAB_40248fd0;
      FUN_4023f7b4();
      puVar9 = auStack_8a;
      puVar8 = PTR_s__W__otu_repeated_dn_req__s__acke_402488a0;
      goto LAB_40248fca;
    }
  }
  if (*(uint *)PTR_DAT_4023ccf0 < 2) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__otu_valid_down_req__s__402488a4,auStack_8a);
  }
  iVar13 = 0;
  pcStack_40 = acStack_12c;
  if (uStack_30 == 0) {
    param_5 = 0;
  }
  puStack_3c = puStack_44;
  iVar3 = FUN_4024ac20(iStack_5c,iStack_54,PTR_s_sid_3ffe8ea9_9_40247a7c,acStack_12c,0x41,0);
  if (iVar3 != iVar13) {
    acStack_12c[0] = (char)iVar13;
  }
  piVar4 = (int *)FUN_4024a87c(iStack_5c,iStack_54,PTR_s_params_40247a70);
  uVar6 = DAT_40245e30;
  puVar8 = PTR_s_Req_object_invalid__402488a8;
  if (piVar4 == (int *)0x0) {
LAB_40248b83:
    FUN_40247020(param_1,puStack_3c,uVar6,puVar8,param_1 + 0xa0,*(undefined2 *)(param_1 + 0xa4));
  }
  else {
    iStack_64 = iStack_58;
    iStack_68 = iStack_5c;
    piStack_60 = piVar4;
    iVar13 = FUN_40209084(iStack_5c + *(short *)(iVar12 + 6),
                          (int)*(short *)(iVar12 + 8) - (int)*(short *)(iVar12 + 6),
                          PTR_s__otd_redirect_402488ac);
    if (iVar13 == 0) {
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__otu_native_method___otd_redi_402488b0);
      }
      auStack_ea[0] = 0;
      iVar12 = iStack_5c;
      iVar13 = FUN_4024abd0(iStack_5c,piVar4,DAT_40246d28,auStack_ea);
      uVar6 = DAT_402400c4;
      puVar8 = PTR_s_Invalid_param__4024887c;
      if (((iVar13 != 0) ||
          (iVar12 = FUN_4024ac20(iVar12,piVar4,PTR_DAT_402488b4,&local_170,0x40,0),
          uVar6 = DAT_402400c4, puVar8 = PTR_s_Invalid_param__4024887c, iVar12 != 0)) ||
         (iVar12 = FUN_40247210(param_1,&local_170,auStack_ea[0]), uVar6 = DAT_40248880,
         puVar8 = PTR_s_redirect_failed__40248884, iVar12 != 0)) goto LAB_40248b83;
    }
    else {
      iVar13 = FUN_40209084(iStack_5c + *(short *)(iVar12 + 6),
                            (int)*(short *)(iVar12 + 8) - (int)*(short *)(iVar12 + 6),
                            PTR_s__otd_neighbor_402488b8);
      if (iVar13 != 0) {
        puVar8 = PTR_s__JsDlgt_402488d8;
        if (acStack_12c[0] != '\0') {
          puVar8 = PTR_s__JsDlgtS_402488d4;
        }
        pcVar5 = (code *)FUN_4024ae40(0x2e,iStack_5c + *(short *)(iVar12 + 6),
                                      (int)*(short *)(iVar12 + 8) - (int)*(short *)(iVar12 + 6),
                                      puVar8,0);
        if (puStack_3c == (undefined1 *)0x0) {
          if (pcVar5 != (code *)0x0) {
            if (acStack_12c[0] == '\0') {
              uVar6 = 0;
              puVar8 = (undefined *)0x0;
              goto LAB_40248ec5;
            }
            uVar6 = 0;
            puVar8 = (undefined *)0x0;
            goto LAB_40248eba;
          }
          pcVar10 = pcStack_40;
          if (acStack_12c[0] == '\0') {
            pcVar10 = (char *)0x0;
          }
          uVar6 = 0;
          puVar9 = (undefined1 *)0x0;
          puVar8 = (undefined *)0x0;
        }
        else {
          uVar6 = FUN_4024a08c(param_1,PTR_FUN_402488dc,0x44);
          puVar7 = (undefined4 *)FUN_40265324();
          *puVar7 = DAT_40245e48;
          *(undefined1 *)(puVar7 + 9) = 0x75;
          uVar2 = 0x6c;
          if (param_5 == 0) {
            uVar2 = 99;
          }
          *(undefined1 *)((int)puVar7 + 0x25) = uVar2;
          if ((iStack_2c == 0) ||
             (puStack_28 = puVar7, iVar12 = FUN_4024aae0(iStack_5c,iStack_2c,puVar7 + 1,0x20,0),
             puVar7 = puStack_28, iVar12 != 0)) {
            *(undefined1 *)(puVar7 + 1) = 0;
          }
          *(int *)(param_1 + 0x218) = *(int *)(param_1 + 0x218) + 1;
          if (*(int *)PTR_DAT_4023ccf0 == 0) {
            puStack_28 = puVar7;
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)
                      (PTR_s__D__bill_debug_rpc_cnt__d_402488e0,*(undefined4 *)(param_1 + 0x218));
            puVar7 = puStack_28;
          }
          puVar7[0xd] = *(undefined4 *)(param_1 + 0xa0);
          uVar1 = *(undefined2 *)(param_1 + 0xa4);
          puVar7[0xc] = puStack_3c;
          *(undefined2 *)(puVar7 + 0xe) = uVar1;
          puVar7[0x10] = 0;
          puVar7[0xf] = 0;
          if (param_5 == 0) {
            (*DAT_4023d19c)(puVar7 + 10,0,8);
          }
          else {
            (*DAT_4023c0bc)();
          }
          if (pcVar5 != (code *)0x0) {
            puVar8 = PTR_FUN_402488e4;
            if (acStack_12c[0] == '\0') {
LAB_40248ec5:
              (*pcVar5)(&iStack_68,puVar8,uVar6);
              goto LAB_40248fd0;
            }
LAB_40248eba:
            (*pcVar5)(&iStack_68,acStack_12c,puVar8,uVar6);
            goto LAB_40248fd0;
          }
          puVar9 = puStack_3c;
          pcVar10 = (char *)0x0;
          puVar8 = PTR_FUN_402488e4;
          if (acStack_12c[0] != '\0') {
            pcVar10 = acStack_12c;
          }
        }
        FUN_4024c4f4(&iStack_68,puVar9,pcVar10,puVar8,uVar6);
        goto LAB_40248fd0;
      }
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__otu_native_method___otd_neig_402488bc);
      }
      if ((*piVar4 == 3) && (uVar11 = (uint)(char)piVar4[1], 0 < (int)uVar11)) {
        uStack_30 = uVar11;
        if (7 < (int)uVar11) {
          uStack_30 = 7;
        }
        *(undefined1 *)(param_1 + 0x440) = 1;
        iStack_2c = param_1 + 0x264;
        piVar4 = piVar4 + 3;
        iVar13 = 0;
        iVar12 = iStack_5c;
        do {
          uStack_48 = 0;
          uStack_50 = DAT_4024451c;
          uStack_4c = DAT_4024451c;
          (*DAT_4023d19c)(&local_170,0,0x44);
          iVar3 = FUN_4024ac20(iVar12,piVar4,PTR_DAT_40246d24,auStack_aa,0x20,&uStack_48);
          if (((iVar3 != 0) ||
              (iVar3 = FUN_4024ac58(iVar12,piVar4,DAT_402488c0,auStack_15c,0x10,0), iVar3 != 0)) ||
             (iVar3 = FUN_4024ab58(iVar12,piVar4,PTR_DAT_402488c4,&uStack_50), iVar3 != 0)) {
            *(undefined1 *)(param_1 + 0x440) = 1;
            uVar6 = DAT_402400c4;
            puVar8 = PTR_s_Invalid_param__4024887c;
            goto LAB_40248b83;
          }
          iVar3 = iVar13;
          if (*(int *)PTR_DAT_4023ccf0 == 0) {
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__delme_get_u64_did__u_402488c8,uStack_50);
            iVar3 = iVar13;
          }
          FUN_40265194(uStack_50,uStack_4c,&local_170);
          FUN_4023f4f4(&local_170,8,0);
          FUN_40240918(auStack_aa);
          iStack_168 = FUN_402405e4();
          if (*(uint *)PTR_DAT_4023ccf0 < 2) {
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)
                      (PTR_s__I__otu_neighbor_slot__u____u__s_402488cc,iVar3,uStack_50,auStack_aa);
          }
          FUN_4023f8b8(auStack_15c,0x10,auStack_14c);
          (*DAT_4023c0bc)(auStack_ea,auStack_14c,0x10);
          (*DAT_4023c0bc)(auStack_da,auStack_15c,0x10);
          FUN_4023f8b8(auStack_ea,0x20,auStack_13c);
          (*DAT_4023c0bc)(iStack_2c,&local_170,0x44);
          piVar4 = (int *)FUN_40265710(piVar4);
          iStack_2c = iStack_2c + 0x44;
          iVar13 = iVar3 + 1;
        } while (iVar13 < (int)uStack_30);
        uVar11 = iVar3 + 2U & 0xff;
        *(char *)(param_1 + 0x440) = (char)(iVar3 + 2U);
        if (uVar11 < 8) {
          (*DAT_4023d19c)(param_1 + uVar11 * 0x44 + 0x220,0,0x44);
        }
        puVar8 = PTR_FUN_402488d0;
        iVar12 = FUN_4024a194(*(undefined4 *)(param_1 + 4),PTR_FUN_402488d0,0);
        if (iVar12 == 0) {
          FUN_4024a134(*(undefined4 *)(param_1 + 4),puVar8,0,param_1);
        }
      }
    }
    FUN_402470f4(param_1,puStack_3c,param_1 + 0xa0,*(undefined2 *)(param_1 + 0xa4));
  }
LAB_40248fd0:
  (*(code *)PTR_FUN_4023cf10)(iStack_34);
  return puStack_38;
}
