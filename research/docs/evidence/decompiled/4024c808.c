// Ghidra 12.1.4; synthetic ELF; 4024c808

void FUN_4024c808(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int in_a15;
  undefined1 auStack_40 [16];
  byte *pbStack_30;

  puVar4 = DAT_4024b060;
  if (param_1 < 2) {
LAB_4024c8b0:
    FUN_4024e0c0(*puVar4,PTR_s_error_3ffea87d_0x22_4024c69c);
  }
  else {
    pbStack_30 = *(byte **)(param_2 + 4);
    iVar1 = (*DAT_4023d3c0)(pbStack_30);
    if (iVar1 == 4) {
      if ((((9 < *pbStack_30 - 0x30) || (9 < pbStack_30[1] - 0x30)) || (9 < pbStack_30[2] - 0x30))
         || (9 < pbStack_30[3] - 0x30)) {
        if (*(uint *)PTR_DAT_4023ccf0 < 4) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)
                    (PTR_s__E__mcu_version_illegal___s_4024c800,*(undefined4 *)(param_2 + 4));
        }
        goto LAB_4024c8b0;
      }
      uVar5 = DAT_40240ce4;
      (*DAT_4023f16c)(DAT_40240ce4);
      FUN_4024e0c0(*puVar4,PTR_s_ok_3ffea4ff_0x17_4024c6a4);
      iVar1 = FUN_40240274(auStack_40,8);
      if ((iVar1 < 1) || (iVar1 = (*DAT_40249f84)(auStack_40,uVar5), iVar1 != 0)) {
        uVar2 = (*DAT_4023d3c0)(uVar5);
        in_a15 = FUN_40240248(uVar5,uVar2);
      }
      (*DAT_4023f16c)(uVar5,auStack_40);
      if (in_a15 == 0) {
        return;
      }
      if (2 < *(uint *)PTR_DAT_4023ccf0) {
        return;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__W__save_mcu_version_to_psm_fail_4024c804;
    }
    else {
      FUN_4024e0c0(*puVar4,PTR_s_error_3ffea87d_0x22_4024c69c);
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return;
      }
      FUN_4023f7b4();
      puVar3 = PTR_s__E__mcu_version_illegal___s_4024c7fc;
    }
    (*(code *)PTR_FUN_4023ccf8)(puVar3,*(undefined4 *)(param_2 + 4));
  }
  return;
}
