// Ghidra 12.1.4; synthetic ELF; 4024bc9c

void FUN_4024bc9c(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;

  puVar5 = DAT_4024b060;
  if (2 < param_1) {
    uVar3 = *(undefined4 *)(param_2 + 4);
    uVar1 = (*DAT_4023d3c0)(uVar3);
    if (uVar1 < 0x21) {
      uVar6 = *(undefined4 *)(param_2 + 8);
      uVar1 = (*DAT_4023d3c0)(uVar6);
      if ((uVar1 < 0x41) && (iVar2 = FUN_40241454(uVar3,uVar6), iVar2 == 0)) {
        uVar3 = *puVar5;
        puVar4 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
        goto LAB_4024bce8;
      }
    }
  }
  uVar3 = *puVar5;
  puVar4 = PTR_s_error_3ffea87d_0x22_4024b1b0;
LAB_4024bce8:
  FUN_4024e0c0(uVar3,puVar4);
  return;
}
