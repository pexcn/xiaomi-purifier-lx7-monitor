// Ghidra 12.1.4; synthetic ELF; 40240d94

int FUN_40240d94(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;

  iVar1 = 0;
  if ((param_3 != 0) &&
     (iVar1 = FUN_4020a2fc(param_1,param_2,PTR_s___s___402409dc,param_3), param_2 < iVar1)) {
    iVar1 = param_2;
  }
  iVar3 = param_1 + iVar1;
  iVar4 = param_2 - iVar1;
  uVar2 = FUN_40206ea8();
  iVar3 = FUN_4020a2fc(iVar3,iVar4,PTR_DAT_40240c0c,uVar2);
  if (iVar3 < iVar4) {
    iVar4 = iVar3;
  }
  iVar1 = iVar1 + iVar4;
  if (param_4 != 0) {
    param_2 = param_2 - iVar1;
    iVar4 = FUN_4020a2fc(param_1 + iVar1,param_2,PTR_s__s_3ffea401_0xa_402409e8,param_4);
    if (param_2 < iVar4) {
      iVar4 = param_2;
    }
    iVar1 = iVar1 + iVar4;
  }
  return iVar1;
}
