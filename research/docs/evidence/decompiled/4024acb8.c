// Ghidra 12.1.4; synthetic ELF; 4024acb8

undefined4 FUN_4024acb8(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;

  if (param_1 != 0) {
    iVar5 = 0;
    uVar1 = *(ushort *)(param_1 + 0x14) & 7;
    if (uVar1 == 1) {
      for (; iVar5 < (int)(uint)*(ushort *)(param_1 + 0x30); iVar5 = iVar5 + 1) {
        iVar3 = iVar5 * 8;
        if (param_3 == 0) {
          puVar4 = (undefined4 *)(*(int *)(param_1 + 0x28) + iVar3);
          iVar3 = (*DAT_40249f84)(param_2,**(int **)(param_1 + 0x34) + (uint)*(ushort *)(puVar4 + 1)
                                 );
          if (iVar3 == 0) goto LAB_4024ad6e;
        }
        else {
          iVar2 = FUN_40209084(param_2,param_3,
                               **(int **)(param_1 + 0x34) +
                               (uint)*(ushort *)(*(int *)(param_1 + 0x28) + iVar3 + 4));
          if (iVar2 == 0) goto LAB_4024ad54;
        }
      }
    }
    else {
      iVar5 = 0;
      if (uVar1 == 2) {
        for (; iVar5 < (int)(uint)*(ushort *)(param_1 + 0x30); iVar5 = iVar5 + 1) {
          iVar3 = iVar5 * 8;
          if (param_3 == 0) {
            puVar4 = (undefined4 *)(*(int *)(param_1 + 0x28) + iVar3);
            iVar3 = (*DAT_40249f84)(param_2,puVar4[1]);
            if (iVar3 == 0) goto LAB_4024ad6e;
          }
          else {
            iVar2 = FUN_40209084(param_2,param_3,
                                 *(undefined4 *)(*(int *)(param_1 + 0x28) + iVar3 + 4));
            if (iVar2 == 0) goto LAB_4024ad54;
          }
        }
      }
    }
  }
  return 0;
LAB_4024ad54:
  puVar4 = (undefined4 *)(*(int *)(param_1 + 0x28) + iVar3);
LAB_4024ad6e:
  return *puVar4;
}
