// Ghidra 12.1.4; synthetic ELF; 402087c0

void FUN_402087c0(ushort *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;

  uVar4 = (uint)*param_1;
  if (*(int *)(param_1 + 2) == 0) {
    memw();
    *DAT_40208660 = 0;
    memw();
    *DAT_40208664 = 0;
    memw();
    *DAT_40208668 = 0;
    memw();
    *DAT_4020866c = uVar4;
  }
  else if (*(int *)(param_1 + 2) == 2) {
    memw();
    *DAT_40208660 = 0;
    memw();
    *DAT_40208664 = 0;
    memw();
    *DAT_40208668 = uVar4;
    memw();
    *DAT_4020866c = 0;
  }
  uVar5 = 0;
  puVar3 = DAT_40208710;
  do {
    if ((uVar4 & 1 << ((byte)uVar5 & 0x1f)) != 0) {
      uVar2 = uVar5 & 0xff;
      puVar1 = DAT_40208784;
      if (((((uVar2 != 0) && (puVar1 = DAT_40208780, uVar2 != 1)) &&
           (puVar1 = DAT_40208788, uVar2 != 2)) &&
          (((puVar1 = DAT_4020878c, uVar2 != 3 && (puVar1 = DAT_40208790, uVar2 != 4)) &&
           ((puVar1 = DAT_40208794, uVar2 != 5 &&
            ((puVar1 = DAT_40208798, uVar2 != 6 && (puVar1 = DAT_4020879c, uVar2 != 7)))))))) &&
         ((puVar1 = DAT_402087a0, uVar2 != 8 &&
          (((((puVar1 = DAT_402087a4, uVar2 != 9 && (puVar1 = DAT_402087a8, uVar2 != 10)) &&
             (puVar1 = DAT_402087ac, uVar2 != 0xb)) &&
            ((puVar1 = DAT_402087b0, uVar2 != 0xc && (puVar1 = DAT_402087b4, uVar2 != 0xd)))) &&
           (puVar1 = DAT_402087b8, uVar2 == 0xe)))))) {
        puVar1 = DAT_402087bc;
      }
      if ((1 << ((byte)uVar5 & 0x1f) & 0x35U) == 0) {
        memw();
        memw();
        *puVar1 = *puVar1 & 0xfffffecf;
        memw();
        uVar2 = *puVar1 | 0x30;
      }
      else {
        memw();
        memw();
        *puVar1 = *puVar1 & 0xfffffecf;
        memw();
        uVar2 = *puVar1;
      }
      memw();
      *puVar1 = uVar2;
      memw();
      if (*(int *)(param_1 + 4) == 0) {
        uVar2 = *puVar1 & 0xffffff7f;
      }
      else {
        uVar2 = *puVar1 | 0x80;
      }
      memw();
      *puVar1 = uVar2;
      if (*(int *)(param_1 + 2) == 1) {
        (*(code *)PTR_FUN_402026f0)();
        memw();
        memw();
        *puVar3 = *puVar3 | 4;
LAB_40208934:
        (*(code *)PTR_FUN_40202570)();
      }
      else if (*(int *)(param_1 + 2) == 3) {
        (*(code *)PTR_FUN_402026f0)();
        memw();
        memw();
        *puVar3 = *puVar3 & 0xfffffffe | 1;
        memw();
        *DAT_40208714 = DAT_40204e44;
        goto LAB_40208934;
      }
      FUN_4020873c(uVar5,*(undefined4 *)(param_1 + 6));
    }
    uVar5 = uVar5 + 1;
    puVar3 = puVar3 + 1;
    if (uVar5 == 0x10) {
      return;
    }
  } while( true );
}
