// Ghidra 12.1.4; synthetic ELF; 4023f1cc

undefined4 FUN_4023f1cc(undefined4 param_1,code *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 auStack_60 [64];
  undefined1 *puStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;

  puStack_20 = auStack_60;
  uVar1 = 0;
  if (param_2 != (code *)0x0) {
    uStack_18 = 0;
    (*DAT_4023f16c)(auStack_60,PTR_s___result____ok____4023f168);
    uStack_1c = 0x11;
    (*DAT_4023d19c)(DAT_4023f110,uVar1,0x41);
    uVar1 = (*param_2)(&puStack_20,param_3);
  }
  return uVar1;
}
