// Ghidra 12.1.4; synthetic ELF; 40101a80

undefined4 FUN_40101a80(uint param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;

  uVar1 = (*DAT_401011f8)(*(undefined4 *)(PTR_DAT_40101084 + 4),
                          *(undefined4 *)(PTR_DAT_40101084 + 0xc));
  if (((param_1 < uVar1) && (iVar2 = (*DAT_40101a78)(PTR_DAT_40101084), iVar2 == 0)) &&
     (iVar2 = (*DAT_40101a7c)(PTR_DAT_40101084,*(int *)(PTR_DAT_40101084 + 0xc) * param_1),
     iVar2 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}
