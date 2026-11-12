// Ghidra 12.1.4; synthetic ELF; 4024c954

void FUN_4024c954(void)

{
  int iVar1;

  FUN_4024e0c0(*DAT_4024b060,PTR_s_ok_3ffea4ff_0x17_4024c6a4);
  iVar1 = FUN_4023f2a0();
  if ((iVar1 == 1) &&
     ((iVar1 = FUN_402444dc(), iVar1 != 0 || (iVar1 = FUN_40241bc0(), iVar1 <= DAT_4024c94c)))) {
    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__local_restore_is_disabled_4024c950);
    }
  }
  else {
    iVar1 = FUN_40240790();
    if (iVar1 != 0) {
      FUN_402403bc();
    }
    FUN_40241b98(0x32);
    FUN_402425bc();
  }
  return;
}
