// Ghidra 12.1.4; synthetic ELF; 4024d1a4

undefined4 FUN_4024d1a4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;

  *(undefined4 *)(param_1 + 0x30) = param_3;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iVar1 = (*DAT_4023d3c0)(param_2);
  if (*(uint *)(param_1 + 0x2c) < iVar1 + 1U) {
    iVar1 = (*(code *)PTR_FUN_4023e2a8)(*(undefined4 *)(param_1 + 0x28));
    if (iVar1 == 0) {
      if (3 < *(uint *)PTR_DAT_4023ccf0) {
        return 0xffffffff;
      }
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__realloc_new_prop_buf_error__4024d1a0);
      return 0xffffffff;
    }
    *(int *)(param_1 + 0x28) = iVar1;
  }
  iVar1 = *(int *)(param_1 + 0x28);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  iVar2 = (*DAT_4023d3c0)(param_2);
  *(int *)(param_1 + 0x2c) = iVar2 + 1;
  (*DAT_4023f16c)(iVar1,param_2);
  return 0;
}
