// Ghidra 12.1.4; synthetic ELF; 40242178

void FUN_40242178(undefined4 param_1,code *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined1 auStack_40 [32];
  undefined1 *puStack_20;
  uint uStack_1c;
  undefined4 uStack_18;

  uVar1 = *(undefined4 *)(PTR_PTR_40242168 + *DAT_4024216c * 4);
  if (*(int *)PTR_DAT_4023ccf0 == 0) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__ota_state__s_40242170,uVar1);
  }
  puStack_20 = auStack_40;
  uStack_1c = FUN_4020a2fc(auStack_40,0x20,PTR_s___result____s___40242174,uVar1);
  if (0x20 < uStack_1c) {
    uStack_1c = 0x20;
  }
  uStack_18 = 0;
  (*param_2)(&puStack_20,param_3);
  return;
}
