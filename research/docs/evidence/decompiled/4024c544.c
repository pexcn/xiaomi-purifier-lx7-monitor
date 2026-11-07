// Ghidra 12.1.4; synthetic ELF; 4024c544

void FUN_4024c544(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;

  iVar1 = FUN_40240790();
  if (iVar1 == 0) {
    puVar4 = DAT_4024b060;
    iVar1 = FUN_402407d4();
    if (iVar1 == 0) {
      uVar2 = *puVar4;
      uVar3 = DAT_4024c530;
    }
    else {
      uVar2 = *puVar4;
      uVar3 = DAT_4024c52c;
    }
  }
  else {
    puVar4 = DAT_4024b060;
    iVar1 = FUN_4024334c();
    if (iVar1 == 0) {
      iVar1 = FUN_402444dc();
      if (iVar1 == 0) {
        iVar1 = FUN_402411e0();
        if (iVar1 == 3) {
          uVar2 = *puVar4;
          uVar3 = DAT_4024c53c;
        }
        else {
          uVar2 = *puVar4;
          uVar3 = DAT_4024c540;
        }
      }
      else {
        uVar2 = *puVar4;
        uVar3 = DAT_4024c538;
      }
    }
    else {
      uVar2 = *puVar4;
      uVar3 = DAT_4024c534;
    }
  }
  FUN_4024e0c0(uVar2,uVar3);
  return;
}
