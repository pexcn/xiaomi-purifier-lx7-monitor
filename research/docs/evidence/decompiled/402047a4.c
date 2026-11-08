// Ghidra 12.1.4; synthetic ELF; 402047a4

uint FUN_402047a4(int param_1)

{
  short sVar1;
  int iVar2;
  uint uVar3;

  (*(code *)PTR_FUN_402026f0)();
  iVar2 = DAT_40202c34;
  if (param_1 != 1) {
    iVar2 = (*(code *)PTR_FUN_40203658)(0x48c,PTR_s_user_interface_c_40203654,0x6ae);
    sVar1 = (*DAT_40202278)(*(undefined4 *)(PTR_DAT_402026b4 + 4),
                            *(undefined4 *)(PTR_DAT_402026b4 + 0xc));
    FUN_40204b9c(sVar1 + -3,0,iVar2,0x48c);
  }
  uVar3 = (uint)*(byte *)(iVar2 + 8);
  if (3 < uVar3) {
    uVar3 = 2;
  }
  if (param_1 != 1) {
    (*(code *)PTR_FUN_40202710)(iVar2,PTR_s_user_interface_c_40203654,0x6b6);
  }
  (*(code *)PTR_FUN_40202570)();
  return uVar3 & 0xff;
}
