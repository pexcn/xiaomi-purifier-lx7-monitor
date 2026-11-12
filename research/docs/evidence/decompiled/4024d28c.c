// Ghidra 12.1.4; synthetic ELF; 4024d28c

int FUN_4024d28c(int *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int *piVar3;

  if (param_1 == (int *)0x0) {
    return -2;
  }
  iVar1 = FUN_4024d140(param_2);
  if (iVar1 < 0) {
    return iVar1;
  }
  if (param_3 == 0) {
    return -7;
  }
  uVar2 = (*DAT_4023d3c0)(param_3);
  if (899 < uVar2) {
    return -5;
  }
  iVar1 = FUN_40265790(param_3,uVar2);
  if (((iVar1 < 0) && (iVar1 = FUN_402657f0(param_3,uVar2), iVar1 < 0)) &&
     (iVar1 = FUN_4024d228(param_3,uVar2), iVar1 < 0)) {
    return -7;
  }
  FUN_40241f20(param_1[6],0xffffffff);
  for (piVar3 = (int *)*param_1; piVar3 != param_1; piVar3 = (int *)*piVar3) {
    iVar1 = (*DAT_40249f84)(param_2,piVar3 + 2);
    if (iVar1 == 0) {
      if (piVar3 != (int *)0x0) {
        iVar1 = FUN_4024d1a4(piVar3,param_3,param_4);
        if (iVar1 == 0) goto LAB_4024d379;
        goto LAB_4024d386;
      }
      break;
    }
  }
  uVar2 = (*DAT_4023d3c0)(param_3);
  if (uVar2 < 900) {
    iVar1 = (*(code *)PTR_FUN_4023cf0c)();
    if (iVar1 != 0) {
      piVar3 = (int *)(*(code *)PTR_FUN_4023cf0c)(0x3c);
      if (piVar3 == (int *)0x0) {
        (*(code *)PTR_FUN_4023cf10)(iVar1);
      }
      else {
        *piVar3 = (int)piVar3;
        piVar3[1] = (int)piVar3;
        (*DAT_40225f90)(piVar3 + 2,param_2,0x20);
        piVar3[10] = iVar1;
        piVar3[0xb] = uVar2 + 1;
        iVar1 = FUN_40241b60();
        piVar3[0xe] = iVar1 + -0x65;
        iVar1 = FUN_4024d1a4(piVar3,param_3,param_4);
        if (iVar1 == 0) {
          iVar1 = *param_1;
          *(int **)(iVar1 + 4) = piVar3;
          *piVar3 = iVar1;
          piVar3[1] = (int)param_1;
          *param_1 = (int)piVar3;
          iVar1 = 0;
LAB_4024d379:
          if (param_1[0x10c] != 0) {
            FUN_40241e88();
          }
          goto LAB_4024d386;
        }
      }
    }
  }
  iVar1 = -1;
LAB_4024d386:
  FUN_40241efc(param_1[6]);
  return iVar1;
}
