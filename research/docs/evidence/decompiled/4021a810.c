// Ghidra 12.1.4; synthetic ELF; 4021a810

void FUN_4021a810(void)

{
  undefined4 uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 auStack_10 [4];

  puVar3 = PTR_FUN_4021a7e8;
  iVar6 = DAT_402190bc;
  *(undefined1 *)(DAT_402190bc + 0xe6) = 2;
  *(uint *)(iVar6 + 0x30) = *(uint *)(iVar6 + 0x30) & 0xfffffffc | 0xc;
  FUN_40202de4(iVar6 + 0x6c,puVar3,0);
  uVar4 = DAT_4021a7ec;
  uVar2 = DAT_40219bc4;
  uVar1 = DAT_40219bc0;
  uVar5 = DAT_4021974c;
  *(undefined1 *)(iVar6 + 0xe8) = 2;
  *(undefined4 *)(iVar6 + 0x4c) = uVar1;
  *(undefined1 *)(iVar6 + 0xea) = 1;
  *(undefined4 *)(iVar6 + 0x48) = uVar5;
  *(undefined1 *)(iVar6 + 0xe7) = 0;
  *(undefined1 *)(iVar6 + 0xe9) = 0;
  *(short *)(iVar6 + 0x28) = (short)uVar4;
  puVar3 = PTR_LAB_4021a7f0;
  *(uint *)(iVar6 + 0x30) = *(uint *)(iVar6 + 0x30) & 0xffffffdf & uVar2;
  *(undefined1 *)(iVar6 + 0x32) = 0;
  FUN_4021c518(puVar3,5);
  FUN_4021c518(PTR_LAB_4021a7f4,6);
  FUN_40202de4(DAT_402198dc,PTR_FUN_4021a7f8,0);
  FUN_40202de4(DAT_402198d8,PTR_LAB_4021a7fc,0);
  FUN_40202de4(DAT_4021a4d0,PTR_LAB_4021a800,0);
  FUN_40202de4(DAT_40219cbc,PTR_LAB_4021a804,0);
  uVar5 = FUN_40207080(4,4,0);
  puVar3 = PTR_DAT_4021a808;
  *(undefined4 *)(iVar6 + 0x118) = uVar5;
  FUN_4020773c(PTR_LAB_4021a80c,puVar3,0x180,0,1,auStack_10,0,0);
  *(undefined1 *)(iVar6 + 0x35) = 1;
  FUN_40219cc0();
  return;
}
