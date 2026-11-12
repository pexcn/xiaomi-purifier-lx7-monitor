// Ghidra 12.1.4; synthetic ELF; 4024ca4c

void FUN_4024ca4c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 *puVar4;

  puVar4 = DAT_4024b060;
  if (1 < param_1) {
    uVar2 = *(undefined4 *)(param_2 + 4);
    iVar1 = (*DAT_40249f84)(uVar2,DAT_4024ca44);
    if (iVar1 == 0) {
      iVar1 = FUN_40204820();
      if (iVar1 == 1) {
        uVar2 = 2;
LAB_4024ca90:
        FUN_402062f8(uVar2);
        uVar2 = *puVar4;
        puVar3 = PTR_s_ok_3ffea4ff_0x17_4024c6a4;
        goto LAB_4024ca99;
      }
    }
    else {
      iVar1 = (*DAT_40249f84)(uVar2,PTR_DAT_4024ca48);
      uVar2 = 0;
      if (iVar1 == 0) goto LAB_4024ca90;
    }
  }
  uVar2 = *puVar4;
  puVar3 = PTR_s_error_3ffea87d_0x22_4024c69c;
LAB_4024ca99:
  FUN_4024e0c0(uVar2,puVar3);
  return;
}
