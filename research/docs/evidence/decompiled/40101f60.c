// Ghidra 12.1.4; synthetic ELF; 40101f60

undefined4 FUN_40101f60(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;

  if (((*DAT_40101f50 == '\0') || (iVar1 = (*(code *)PTR_FUN_40101f54)(), iVar1 != 0)) &&
     (iVar1 = FUN_40101e40(), iVar1 != 0)) {
    FUN_40100518();
    (*(code *)PTR_FUN_40101f58)();
    *DAT_40101cbc = 1;
    FUN_40101ac8();
    uVar2 = FUN_40101a80(param_1);
    FUN_40101b08();
    *DAT_40101cbc = 0;
    (*(code *)PTR_FUN_40101f5c)();
    FUN_40100550();
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}
