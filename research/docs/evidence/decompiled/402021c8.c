// Ghidra 12.1.4; synthetic ELF; 402021c8

void FUN_402021c8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;

  iVar1 = FUN_402129b4();
  if (iVar1 != 0) {
    (*(code *)PTR_FUN_402021c0)(PTR_s__s__u_402021ac,PTR_DAT_402021b0,0x140);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_402032e8(0,0x42c);
  FUN_402032e8(1,0x42c);
  FUN_4020dcc0();
  FUN_40224dcc(*(undefined4 *)(DAT_402021b4 + 0x370));
  FUN_40218ff4();
  FUN_4021e71c();
  FUN_4021d660();
  FUN_4021f610(DAT_402021b8,param_2);
  (*(code *)PTR_FUN_402021c4)(1);
  memw();
  memw();
  *(uint *)(DAT_402021bc + 0x200) = *(uint *)(DAT_402021bc + 0x200) & 0xffffffe0 | 1;
  FUN_4021b034();
  FUN_4021a810();
  FUN_4020dca8();
  FUN_402277d8(DAT_402021b8);
  FUN_4021ec4c();
  return;
}
