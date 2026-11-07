// Ghidra 12.1.4; synthetic ELF; 40241b60

void FUN_40241b60(void)

{
  int iVar1;

  iVar1 = FUN_40207ca0();
  if (iVar1 < 0) {
    *DAT_40241b58 = '\x01';
  }
  else if (*DAT_40241b58 == '\x01') {
    *DAT_40241b58 = '\0';
    *DAT_40241b5c = *DAT_40241b5c + 1;
  }
  return;
}
