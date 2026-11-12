// Ghidra 12.1.4; synthetic ELF; 402400dc

int FUN_402400dc(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  uint *puVar4;
  byte local_30 [44];

  iVar1 = FUN_4024abf8(*param_1,param_1[2],DAT_402400b4,local_30);
  if (iVar1 == 0) {
    puVar4 = (uint *)PTR_DAT_4023ccf0;
    if (*(int *)PTR_DAT_4023ccf0 == 0) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__D__set_value_is__u_402400c0,local_30[0]);
    }
    if (local_30[0] < 2) {
      iVar2 = FUN_4024a074(PTR_DAT_402400cc);
      if (iVar2 == 0) {
        FUN_40244640(param_2,param_3,DAT_402400d0,PTR_s_OTd_not_available__402400d4);
        iVar1 = -1;
        if (*puVar4 < 4) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__not_find_otd_402400d8);
        }
      }
      else {
        local_30[0] = local_30[0] != 0;
        uVar3 = *(ushort *)(*(int *)(iVar2 + 0x30) + 0x1ec);
        if ((uVar3 & 1) != (ushort)local_30[0]) {
          if ((bool)local_30[0]) {
            uVar3 = uVar3 | 1;
          }
          else {
            uVar3 = uVar3 & 0xfffe;
          }
          *(ushort *)(*(int *)(iVar2 + 0x30) + 0x1ec) = uVar3;
        }
        FUN_40240074();
        FUN_402446ac(param_2,param_3,0);
      }
    }
    else {
      FUN_40244640(param_2,param_3,DAT_402400c4,PTR_s_Invalid_param__402400c8);
      iVar1 = -1;
    }
  }
  else {
    FUN_40244640(param_2,param_3,DAT_402400b8,PTR_s_Invalid_json__402400bc);
  }
  return iVar1;
}
