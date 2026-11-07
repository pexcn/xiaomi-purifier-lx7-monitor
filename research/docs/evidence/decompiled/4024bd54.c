// Ghidra 12.1.4; synthetic ELF; 4024bd54

void FUN_4024bd54(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 *puVar4;

  puVar4 = DAT_4024b060;
  if (param_1 < 2) {
LAB_4024bd64:
    uVar1 = *puVar4;
    puVar3 = PTR_s_error_3ffea87d_0x22_4024b1b0;
  }
  else {
    uVar1 = *(undefined4 *)(param_2 + 4);
    iVar2 = (*DAT_40249f84)(uVar1,DAT_4024bd4c);
    if (iVar2 == 0) {
      FUN_40265860(*puVar4);
      uVar1 = DAT_40245dd8;
    }
    else {
      iVar2 = (*DAT_40249f84)(uVar1,PTR_DAT_4024bd50);
      if (iVar2 != 0) goto LAB_4024bd64;
      FUN_4026586c(*puVar4);
      uVar1 = 1000;
    }
    *(undefined4 *)PTR_DAT_4024b19c = uVar1;
    uVar1 = *puVar4;
    puVar3 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
  }
  FUN_4024e0c0(uVar1,puVar3);
  return;
}
