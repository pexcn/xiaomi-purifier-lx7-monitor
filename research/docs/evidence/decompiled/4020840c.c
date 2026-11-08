// Ghidra 12.1.4; synthetic ELF; 4020840c

void FUN_4020840c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  int iStack_20;

  if (*DAT_4020829c != 0) {
    local_30 = param_2;
    uStack_2c = param_3;
    uStack_28 = param_1;
    if (param_4 == 0) {
      piVar2 = DAT_4020829c;
      iStack_20 = param_4;
      iVar1 = FUN_402081e8();
      if (iVar1 == 1) {
        iVar1 = *piVar2;
      }
      else {
        iVar1 = *piVar2;
        param_5 = iStack_20;
      }
      FUN_4020711c(iVar1,&local_30,param_5);
    }
    else {
      FUN_402072e8(*DAT_4020829c,&local_30,param_4,0);
    }
  }
  return;
}
