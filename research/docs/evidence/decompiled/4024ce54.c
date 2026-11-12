// Ghidra 12.1.4; synthetic ELF; 4024ce54

void FUN_4024ce54(void)

{
  undefined *puVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;

  iVar2 = DAT_4024ce1c;
  (*DAT_4023d19c)(DAT_4024ce1c,0,0x38);
  uVar4 = 0xfff8;
  (*DAT_4023f16c)(DAT_4024ce20,PTR_DAT_4024ce24);
  uVar3 = 2;
  *(ushort *)(iVar2 + 0x14) = *(ushort *)(iVar2 + 0x14) & uVar4 | 2;
  *(undefined **)(iVar2 + 0x28) = PTR_PTR_4024ce28;
  *(undefined **)(iVar2 + 0x2c) = PTR_PTR_4024ce2c;
  *(short *)(iVar2 + 0x30) = (short)(DAT_4024ce30 >> 3);
  *(short *)(iVar2 + 0x32) = (short)(DAT_4024ce34 >> 3);
  FUN_4024af3c(iVar2);
  iVar2 = DAT_4024ce38;
  (*DAT_4023d19c)(DAT_4024ce38,0,0x38);
  (*DAT_4023f16c)(DAT_4024ce3c,PTR_DAT_4024ce40);
  *(undefined **)(iVar2 + 0x28) = PTR_PTR_4024ce2c;
  puVar1 = PTR_DAT_4024ce44;
  *(ushort *)(iVar2 + 0x14) = *(ushort *)(iVar2 + 0x14) & uVar4 | uVar3;
  *(undefined **)(iVar2 + 0x2c) = puVar1;
  *(short *)(iVar2 + 0x30) = (short)(DAT_4024ce48 >> 3);
  *(short *)(iVar2 + 0x32) = (short)(DAT_4024ce4c >> 3);
  FUN_4024b024(iVar2);
  if (*(int *)PTR_DAT_4023ccf0 == 0) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__xobj_sys_init_complete_4024ce50);
  }
  return;
}
