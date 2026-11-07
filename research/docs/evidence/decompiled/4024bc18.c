// Ghidra 12.1.4; synthetic ELF; 4024bc18

void FUN_4024bc18(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;

  puVar3 = DAT_4024bc08;
  iVar1 = FUN_40241f20(*DAT_4024bc08,0);
  if (iVar1 == 0) {
    if (1 < param_1) {
      uVar4 = *(undefined4 *)(param_2 + 4);
      uVar2 = (*DAT_4023d3c0)(uVar4);
      iVar1 = FUN_40244520(DAT_4024451c,DAT_4024451c,uVar4,uVar2,PTR_FUN_4024bc14,puVar3);
      if (iVar1 == 0) {
        return;
      }
    }
    FUN_4024e0c0(*DAT_4024b060,PTR_s_error_3ffea87d_0x22_4024b1b0);
    FUN_40241efc(*puVar3);
  }
  else {
    FUN_4024e0c0(*DAT_4024b060,PTR_DAT_4024bc0c);
    if (*(uint *)PTR_DAT_4023ccf0 < 2) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__prop_busy_4024bc10);
    }
  }
  return;
}
