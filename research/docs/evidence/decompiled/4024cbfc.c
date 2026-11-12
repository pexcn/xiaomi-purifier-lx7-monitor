// Ghidra 12.1.4; synthetic ELF; 4024cbfc

undefined4
FUN_4024cbfc(undefined4 *param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *local_40 [4];
  int iStack_30;
  undefined4 *puStack_2c;
  int iStack_28;

  iStack_30 = param_3;
  if (param_1 != (undefined4 *)0x0) {
    uVar1 = FUN_4024cb38();
    if (uVar1 < 8) {
      iStack_28 = (*DAT_4023d3c0)(param_2);
      local_40[0] = (undefined4 *)(*(code *)PTR_FUN_4023e2a4)(iStack_28 + 0x55,1);
      if (local_40[0] == (undefined4 *)0x0) {
        FUN_40244640(param_4,param_5,DAT_402455a4,PTR_s_Resp_general_error__4024cbf4);
        return 0xfffffffb;
      }
      local_40[0][2] = param_4;
      local_40[0][3] = param_5;
      puStack_2c = local_40[0];
      uVar2 = FUN_40241b60();
      puStack_2c[1] = uVar2;
      *local_40[0] = 0;
      local_40[0][0x14] = iStack_28;
      if (param_2 != 0) {
        (*DAT_40225f90)(local_40[0] + 0x15,param_2);
      }
      if (iStack_30 != 0) {
        (*DAT_40225f90)(local_40[0] + 4,iStack_30,0x40);
      }
      iVar3 = FUN_40241f94(*param_1,local_40,0);
      if (iVar3 == 0) {
        return 0;
      }
      if (local_40[0] != (undefined4 *)0x0) {
        (*(code *)PTR_FUN_4023cf10)();
      }
    }
    else if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__miio_down_manager_queue_full_4024cbf8);
    }
  }
  FUN_40244640(param_4,param_5,DAT_402455a4,PTR_s_Resp_general_error__4024cbf4);
  return 0xffffffff;
}
