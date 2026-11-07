// Ghidra 12.1.4; synthetic ELF; 4024adc0

int FUN_4024adc0(undefined1 param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar1 = FUN_4022e8c8(param_2,param_1);
  if (iVar1 == 0) {
    iVar2 = FUN_4024ad90(PTR_DAT_4024adbc,4);
    if (iVar2 != 0) {
      iVar1 = FUN_4024acb8(iVar2,param_2,param_3);
      goto LAB_4024ae28;
    }
  }
  else {
    iVar3 = 0;
    if (param_3 != 0) {
      iVar3 = (param_3 + -1) - (iVar1 - param_2);
    }
    iVar2 = FUN_4024ad90(param_2);
    if ((iVar2 != 0) && (iVar1 = FUN_4024acb8(iVar2,iVar1 + 1,iVar3), iVar1 != 0)) {
LAB_4024ae28:
      if (param_4 == (int *)0x0) {
        return iVar1;
      }
      *param_4 = iVar2;
      return iVar1;
    }
  }
  return 0;
}
