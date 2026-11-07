// Ghidra 12.1.4; synthetic ELF; 4024c6b0

void FUN_4024c6b0(int param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined1 auStack_70 [64];
  uint auStack_30 [11];

  puVar4 = auStack_70;
  FUN_40240208(auStack_70,0x40);
  if (param_1 < 2) {
    FUN_4024e0c0(*DAT_4024b060,PTR_s__s_3ffea401_0xa_4024c5c0,auStack_70);
    if (1 < *(uint *)PTR_DAT_4023ccf0) {
      return;
    }
    FUN_4023f7b4();
    puVar3 = PTR_s__I__model_queried_by_mcu____s__4024c6ac;
  }
  else {
    iVar7 = 0;
    auStack_30[0] = 0;
    auStack_30[1] = 0;
    iVar10 = *(int *)(param_2 + 4);
    for (uVar6 = 0; uVar5 = (uint)*(byte *)(iVar10 + uVar6), uVar5 != 0; uVar6 = uVar6 + 1) {
      if (uVar5 == 0x2e) {
        if (iVar7 < 2) {
          auStack_30[iVar7] = uVar6;
          iVar7 = iVar7 + 1;
          goto LAB_4024c6fe;
        }
LAB_4024c729:
        bVar1 = true;
        goto LAB_4024c72b;
      }
LAB_4024c6fe:
      if ((((9 < uVar5 - 0x30) && (0x19 < ((uVar5 & 0xffffffdf) - 0x41 & 0xff))) && (uVar5 != 0x5f))
         && (1 < (uVar5 - 0x2d & 0xff))) goto LAB_4024c729;
    }
    bVar1 = false;
LAB_4024c72b:
    if ((((iVar7 != 2) || ((int)auStack_30[0] < 1)) ||
        (((int)(auStack_30[1] - auStack_30[0]) < 2 ||
         (((int)(uVar6 - auStack_30[1]) < 2 || (*(uint *)PTR_DAT_4023d3a8 < uVar6)))))) || (bVar1))
    {
      puVar9 = DAT_4024b060;
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)
                  (PTR_s__E__illegal_model_name___s_4024c698,*(undefined4 *)(param_2 + 4));
      }
      FUN_4024e0c0(*puVar9,PTR_s_error_3ffea87d_0x22_4024c69c);
      return;
    }
    puVar8 = (uint *)PTR_DAT_4023ccf0;
    puVar9 = DAT_4024b060;
    iVar7 = (*DAT_40241450)(auStack_70,iVar10,0x40);
    if (iVar7 != 0) {
      uVar2 = (*DAT_4023d3c0)(iVar10);
      iVar7 = FUN_402401d8(iVar10,uVar2);
      if ((iVar7 < 0) && (*puVar8 < 3)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__set_model_to_psm_failed____s_4024c6a0,auStack_70);
      }
    }
    FUN_4024e0c0(*puVar9,PTR_s_ok_3ffea4ff_0x17_4024c6a4);
    if (1 < *puVar8) {
      return;
    }
    FUN_4023f7b4();
    puVar4 = *(undefined1 **)(param_2 + 4);
    puVar3 = PTR_s__I__model_set_by_mcu____s__4024c6a8;
  }
  (*(code *)PTR_FUN_4023ccf8)(puVar3,puVar4);
  return;
}
