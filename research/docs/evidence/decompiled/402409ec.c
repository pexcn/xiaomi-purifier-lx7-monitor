// Ghidra 12.1.4; synthetic ELF; 402409ec

int FUN_402409ec(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar1 = 0;
  if ((param_3 != 0) &&
     (iVar1 = FUN_4020a2fc(param_1,param_2,PTR_s___s___402409dc,param_3), param_2 < iVar1)) {
    iVar1 = param_2;
  }
  iVar3 = param_2 - iVar1;
  iVar2 = FUN_4020a2fc(param_1 + iVar1,iVar3,PTR_DAT_402409e0,PTR_s_1_3_9_4023d004);
  if (iVar2 < iVar3) {
    iVar3 = iVar2;
  }
  iVar1 = iVar1 + iVar3;
  iVar3 = param_2 - iVar1;
  iVar2 = FUN_4020a2fc(param_1 + iVar1,iVar3,PTR_DAT_402409e4);
  if (iVar2 < iVar3) {
    iVar3 = iVar2;
  }
  iVar1 = iVar1 + iVar3;
  if (param_4 != 0) {
    param_2 = param_2 - iVar1;
    iVar3 = FUN_4020a2fc(param_1 + iVar1,param_2,PTR_s__s_3ffea401_0xa_402409e8,param_4);
    if (param_2 < iVar3) {
      iVar3 = param_2;
    }
    iVar1 = iVar1 + iVar3;
  }
  return iVar1;
}
