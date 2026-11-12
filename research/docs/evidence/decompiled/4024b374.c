// Ghidra 12.1.4; synthetic ELF; 4024b374

void FUN_4024b374(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined1 auStack_80 [124];

  puVar3 = auStack_80;
  iVar1 = FUN_402412dc();
  puVar2 = DAT_4024b060;
  if ((iVar1 == 1) && (iVar1 = FUN_402412f0(puVar3), iVar1 == 0)) {
    iVar1 = -(*(int *)PTR_DAT_4023d3bc + 0x10U & 0xfffffff0);
    FUN_40265168(puVar3,auStack_80 + iVar1);
    FUN_4024e0c0(*puVar2,PTR_s___s___hd_4024b370,auStack_80 + iVar1,(int)*(short *)(puVar3 + 0x68));
  }
  else {
    FUN_4024e0c0(*puVar2,PTR_s_error_3ffea87d_0x22_4024b1b0);
  }
  return;
}
