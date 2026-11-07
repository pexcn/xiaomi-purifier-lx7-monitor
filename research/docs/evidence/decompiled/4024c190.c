// Ghidra 12.1.4; synthetic ELF; 4024c190

undefined4 FUN_4024c190(void)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  int *piVar8;
  char *local_c0 [32];
  uint auStack_40 [4];
  char *pcStack_30;
  int iStack_2c;

LAB_4024c256:
  do {
    do {
      if (*DAT_4024bdd4 != 0) {
        piVar8 = DAT_4024bdc4;
        puVar6 = DAT_4024b060;
        FUN_40241ee8(*DAT_4024bc08);
        FUN_4024df00(puVar6);
        if (*piVar8 != 0) {
          (*(code *)PTR_FUN_4023cf10)();
        }
        piVar7 = DAT_4024b3e0;
        iVar3 = *DAT_4024b3e0;
        *piVar8 = 0;
        iVar5 = 0;
        if (iVar3 != 0) {
          (*(code *)PTR_FUN_4023cf10)();
        }
        puVar1 = DAT_4024bdbc;
        *piVar7 = iVar5;
        *puVar1 = (char)iVar5;
        if (*(int *)PTR_DAT_4023ccf0 == 0) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__mcmd__killed_self____4024c18c);
        }
        FUN_40241cd4(0);
        return 0;
      }
      piVar8 = DAT_4024bdc4;
      puVar6 = DAT_4024b060;
      auStack_40[0] = (uint)*DAT_4024bdd4;
      iVar3 = FUN_4024df9c(*DAT_4024b060,*DAT_4024bdc4,0x400);
      if ((iVar3 != 0) && (*(int *)PTR_DAT_4023ccf0 == 0)) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__mcmd___s_4024c180,*piVar8);
      }
      FUN_4024c054(*piVar8,auStack_40,local_c0);
    } while ((int)auStack_40[0] < 1);
    if (local_c0[0] != (char *)0x0) {
      iVar5 = 0;
      iVar3 = 0x1e;
      pcStack_30 = local_c0[0];
      uVar4 = auStack_40[0];
      if (*local_c0[0] != '\0') {
        do {
          piVar8 = (int *)(PTR_PTR_4024b09c + iVar5 * 0xc);
          if ((*piVar8 != 0) &&
             (iStack_2c = iVar3, iVar2 = (*DAT_40249f84)(*piVar8,pcStack_30), iVar3 = iStack_2c,
             iVar2 == 0)) {
            iVar3 = (*DAT_40244c78)(pcStack_30,PTR_DAT_4024c184);
            if ((iVar3 == 0) && (uVar4 != 1)) {
              FUN_4024c0ec(auStack_40,local_c0);
            }
            if ((code *)piVar8[2] != (code *)0x0) {
              (*(code *)piVar8[2])(auStack_40[0],local_c0);
            }
            goto LAB_4024c256;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 != iVar3);
      }
    }
    FUN_4024e0c0(*puVar6,PTR_s_error___s_not_found__4024c188);
  } while( true );
}
