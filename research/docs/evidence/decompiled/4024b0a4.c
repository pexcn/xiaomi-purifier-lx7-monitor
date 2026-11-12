// Ghidra 12.1.4; synthetic ELF; 4024b0a4

void FUN_4024b0a4(void)

{
  undefined *puVar1;
  int *piVar2;
  int *piVar3;

  piVar3 = (int *)(PTR_PTR_4024b09c + 0x168);
  for (piVar2 = (int *)PTR_PTR_4024b09c; piVar2 != piVar3; piVar2 = piVar2 + 3) {
    if (*piVar2 != 0) {
      puVar1 = (undefined *)piVar2[1];
      if ((undefined *)piVar2[1] == (undefined *)0x0) {
        puVar1 = PTR_DAT_4024b098;
      }
      FUN_4024e0c0(*DAT_4024b060,PTR_s__s__s_4024b0a0,*piVar2,puVar1);
    }
  }
  return;
}
