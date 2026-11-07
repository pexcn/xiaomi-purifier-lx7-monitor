// Ghidra 12.1.4; synthetic ELF; 40241bfc

int FUN_40241bfc(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;

  uVar5 = (uint)*DAT_40241b5c;
  iVar4 = 0;
  piVar3 = DAT_40241bf8;
  if (uVar5 != 0) {
    iVar4 = (*DAT_40240608)(0xffffffff,*DAT_40241bf8 + 100);
    iVar4 = iVar4 * uVar5;
  }
  uVar1 = FUN_40241b60();
  iVar2 = (*DAT_40240608)(uVar1,*piVar3 + 100);
  return iVar2 + iVar4;
}
