// Ghidra 12.1.4; synthetic ELF; 4023f114

undefined4 FUN_4023f114(undefined4 param_1,code *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 auStack_60 [64];
  undefined1 *puStack_20;
  uint uStack_1c;
  undefined4 uStack_18;

  puStack_20 = auStack_60;
  uVar1 = 0;
  if (param_2 != (code *)0x0) {
    uStack_18 = 0;
    uStack_1c = 0;
    uStack_1c = FUN_4020a2fc(auStack_60,0x40,PTR_s___result___d__4023f10c,
                             *(undefined4 *)(DAT_4023f110 + 0x44));
    if (0x40 < uStack_1c) {
      uStack_1c = 0x40;
    }
    uVar1 = (*param_2)(&puStack_20,param_3);
  }
  return uVar1;
}
