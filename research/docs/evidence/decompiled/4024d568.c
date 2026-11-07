// Ghidra 12.1.4; synthetic ELF; 4024d568

int FUN_4024d568(void)

{
  int iVar1;
  int local_20 [7];

  local_20[0] = FUN_4024d3cc();
  if (local_20[0] != 0) {
    iVar1 = FUN_40241e3c(local_20[0] + 0x430,10,1);
    if (iVar1 == 0) {
      FUN_40241ca0(local_20[0] + 0x42c,PTR_s_up_task_4024d560,PTR_FUN_4024d564,0x4c8);
    }
    else {
      FUN_4024d528(local_20);
      local_20[0] = 0;
    }
  }
  return local_20[0];
}
