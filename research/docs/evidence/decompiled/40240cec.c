// Ghidra 12.1.4; synthetic ELF; 40240cec

int FUN_40240cec(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;

  pcVar3 = DAT_40240ce4;
  iVar1 = FUN_40240274(DAT_40240ce4,0xc);
  if (iVar1 == 0) {
    iVar1 = 0;
    if (*pcVar3 != '\0') {
      iVar1 = 0;
      if (param_3 != 0) {
        iVar1 = FUN_4020a2fc(param_1,param_2,PTR_s___s___402409dc,param_3);
        if (param_2 < iVar1) {
          iVar1 = param_2;
        }
      }
      iVar4 = param_2 - iVar1;
      iVar2 = FUN_4020a2fc(param_1 + iVar1,iVar4,PTR_DAT_40240c0c,pcVar3);
      if (iVar2 < iVar4) {
        iVar4 = iVar2;
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
    }
  }
  else {
    iVar1 = 0;
    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__get_mcu_version_info_error__40240ce8);
    }
  }
  return iVar1;
}
