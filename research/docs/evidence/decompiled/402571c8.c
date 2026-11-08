// Ghidra 12.1.4; synthetic ELF; 402571c8

undefined4 FUN_402571c8(uint param_1,uint param_2)

{
  int iVar1;

  iVar1 = (param_1 & 0xff) * 0xf00;
  do {
    memw();
  } while (0x7d < (*(uint *)(iVar1 + DAT_40229a7c) >> 0x10 & 0xff));
  memw();
  *(uint *)(iVar1 + DAT_40243f68) = param_2 & 0xff;
  return 0;
}
