// Ghidra 12.1.4; synthetic ELF; 4024ba38

void FUN_4024ba38(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  int local_30;

  iVar1 = (*(code *)PTR_FUN_4023e2a4)(0x20,1);
  if (param_1 < 2) {
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      puVar4 = PTR_s__E__wrong_number_of_event_arg_4024ba24;
LAB_4024bac7:
      (*(code *)PTR_FUN_4023ccf8)(puVar4);
    }
LAB_4024bacd:
    uVar5 = *DAT_4024b060;
    puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
  }
  else {
    puVar10 = (undefined4 *)(param_2 + 8);
    iVar9 = 0;
    uVar8 = 0x20;
    for (local_30 = 2; local_30 != param_1; local_30 = local_30 + 1) {
      iVar2 = (*DAT_4023d3c0)(*puVar10);
      iVar3 = iVar1;
      if (uVar8 <= iVar2 + iVar9 + 1U) {
        uVar8 = iVar2 + iVar9 + 2;
        if (0x2ff < uVar8) {
          if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4024bacd;
          FUN_4023f7b4();
          puVar4 = PTR_s__E__event_string_too_long_4024ba2c;
          goto LAB_4024bac7;
        }
        iVar3 = (*(code *)PTR_FUN_4023e2a8)(iVar1,uVar8);
        if (iVar3 == 0) {
          if (3 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4024bacd;
          FUN_4023f7b4();
          puVar4 = PTR_s__E__realloc_event_buf_error__4024ba28;
          goto LAB_4024bac7;
        }
      }
      iVar1 = iVar3;
      if (local_30 != 2) {
        uVar7 = uVar8 - iVar9;
        uVar6 = FUN_4020a2fc(iVar3 + iVar9,uVar7,PTR_DAT_4024ba30);
        if (uVar7 < uVar6) {
          uVar6 = uVar7;
        }
        iVar9 = iVar9 + uVar6;
        iVar1 = iVar3;
      }
      uVar7 = uVar8 - iVar9;
      uVar6 = FUN_4020a2fc(iVar1 + iVar9,uVar7,PTR_s__s_3ffea401_0xa_4024b3ec,*puVar10);
      if (uVar7 < uVar6) {
        uVar6 = uVar7;
      }
      iVar9 = iVar9 + uVar6;
      puVar10 = puVar10 + 1;
    }
    iVar9 = FUN_4024d798(*DAT_40242eb4,*(undefined4 *)(param_2 + 4),iVar1);
    if (iVar9 == 0) {
      uVar5 = *DAT_4024b060;
      puVar4 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
    }
    else {
      puVar10 = DAT_4024b060;
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__event_invalid_4024ba34);
      }
      uVar5 = *puVar10;
      puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
    }
  }
  FUN_4024e0c0(uVar5,puVar4);
  if (iVar1 != 0) {
    (*(code *)PTR_FUN_4023cf10)(iVar1);
  }
  return;
}
