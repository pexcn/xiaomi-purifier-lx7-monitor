// Ghidra 12.1.4; synthetic ELF; 40207e78

void FUN_40207e78(int param_1)

{
  int iVar1;

  if (param_1 != 0) {
    FUN_40207c60();
    memw();
    param_1 = param_1 + *DAT_40207684;
    memw();
    (*(code *)PTR_FUN_40207910)(*DAT_40207680 + 4);
    FUN_40207694(param_1);
    iVar1 = FUN_40207d08();
    if (iVar1 != 0) {
      return;
    }
  }
  (*(code *)PTR_FUN_40203040)(1);
  return;
}
