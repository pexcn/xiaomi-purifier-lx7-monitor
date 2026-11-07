// Ghidra 12.1.4; synthetic ELF; 4024bcfc

void FUN_4024bcfc(int param_1,int param_2)

{
  uint uVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;

  if (param_1 < 2) {
    uVar4 = *DAT_4024b060;
    puVar2 = (undefined *)FUN_4023f75c();
  }
  else {
    uVar4 = *(undefined4 *)(param_2 + 4);
    puVar3 = DAT_4024b060;
    uVar1 = (*DAT_4023d3c0)(uVar4);
    if (uVar1 < 3) {
      FUN_4023f6ec(uVar4);
      uVar4 = *puVar3;
      puVar2 = PTR_s_ok_3ffea4ff_0x17_4024b0e8;
    }
    else {
      uVar4 = *puVar3;
      puVar2 = PTR_s_error_3ffea87d_0x22_4024b1b0;
    }
  }
  FUN_4024e0c0(uVar4,puVar2);
  return;
}
