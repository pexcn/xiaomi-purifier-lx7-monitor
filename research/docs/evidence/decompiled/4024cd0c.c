// Ghidra 12.1.4; synthetic ELF; 4024cd0c

int FUN_4024cd0c(int param_1,int *param_2,int *param_3)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 auStack_1b0 [96];
  undefined1 auStack_30 [4];
  int iStack_2c;

  *param_2 = 0;
  *param_3 = 0;
  FUN_40265704(auStack_30);
  uVar2 = (*DAT_4023d3c0)(param_1);
  iVar3 = FUN_40265408(auStack_30,param_1,uVar2,auStack_1b0,0x20);
  if (iVar3 == 0) {
    auStack_1b0[iStack_2c * 3] = 0;
    iVar4 = FUN_4024a87c(param_1,auStack_1b0,PTR_s_method_4024ccf8);
    if (iVar4 == 0) {
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return -1;
      }
      FUN_4023f7b4();
      puVar5 = PTR_s__E__error__no_method_found_4024ccfc;
    }
    else {
      sVar1 = *(short *)(iVar4 + 8);
      *param_2 = param_1 + *(short *)(iVar4 + 6);
      puVar5 = PTR_s_params_4024cd00;
      *(char *)(param_1 + sVar1) = (char)iVar3;
      iVar4 = FUN_4024a87c(param_1,auStack_1b0,puVar5);
      if (iVar4 == 0) {
        if (3 < *(uint *)PTR_DAT_4023ccf0) {
          return -1;
        }
        FUN_4023f7b4();
        puVar5 = PTR_s__E__error__no_params_found_4024cd04;
      }
      else {
        sVar1 = *(short *)(iVar4 + 8);
        *param_3 = param_1 + *(short *)(iVar4 + 6) + 1;
        *(char *)(param_1 + sVar1 + -1) = (char)iVar3;
        if (*(char *)*param_2 != '\0') {
          return iVar3;
        }
        if (3 < *(uint *)PTR_DAT_4023ccf0) {
          return -1;
        }
        FUN_4023f7b4();
        puVar5 = PTR_s__E__error__no_method_found_4024cd08;
      }
    }
    (*(code *)PTR_FUN_4023ccf8)(puVar5);
  }
  else if (*(uint *)PTR_DAT_4023ccf0 < 4) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__json_parse_err__d___4024ccf4,iVar3);
  }
  return -1;
}
