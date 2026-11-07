// Ghidra 12.1.4; synthetic ELF; 40257274

void FUN_40257274(void)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;

  puVar3 = (uint *)PTR_DAT_4023ccf0;
  piVar4 = DAT_4025726c;
  if (*(int *)PTR_DAT_4023ccf0 == 0) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__miio_app_thread_40257264);
    piVar4 = DAT_4025726c;
  }
  do {
    if (*puVar3 < 2) {
      FUN_4023f7b4();
      uVar1 = FUN_40204440();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__system_memory_left___u_40257268,uVar1);
    }
    if (*piVar4 == 0) {
      iVar2 = FUN_402432e4();
      if ((iVar2 != 0) && (*puVar3 < 4)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__ota_init_error_40257270);
      }
      *piVar4 = 1;
    }
    FUN_40241b98(300);
  } while( true );
}
