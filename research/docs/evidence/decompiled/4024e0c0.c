// Ghidra 12.1.4; synthetic ELF; 4024e0c0

int FUN_4024e0c0(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;

  FUN_40241f20(*(undefined4 *)(param_1 + 0x334),0xffffffff);
  iVar3 = param_1 + 8;
  iVar1 = FUN_402094fc(iVar3,0x32b,param_2);
  iVar2 = 0;
  if (iVar1 < 0x32b) {
    iVar2 = iVar1 + 1;
    *(undefined1 *)(param_1 + iVar1 + 8) = 0xd;
    FUN_40244068(param_1,iVar3,iVar2);
  }
  FUN_40241efc(*(undefined4 *)(param_1 + 0x334));
  return iVar2;
}
