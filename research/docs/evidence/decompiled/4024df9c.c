// Ghidra 12.1.4; synthetic ELF; 4024df9c

undefined4 FUN_4024df9c(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char local_40;
  char acStack_3f [15];
  uint uStack_30;
  uint uStack_2c;

  iVar3 = param_1 + 0x300;
  uStack_30 = param_3;
  if (*(char *)(param_1 + 0x338) != '\0') {
    FUN_4024df30(param_1,PTR_DAT_4024df8c);
  }
  do {
    *(undefined4 *)(param_1 + 4) = 0;
LAB_4024e0a2:
    do {
      uStack_2c = (uint)*(byte *)(iVar3 + 0x39);
      if (uStack_2c != 0) {
LAB_4024e04d:
        *(undefined1 *)(param_2 + *(int *)(param_1 + 4)) = 0;
        *(undefined1 *)(iVar3 + 0x39) = 0;
        return *(undefined4 *)(param_1 + 4);
      }
      iVar1 = FUN_402440b0(param_1,acStack_3f,1);
      if (iVar1 != 1) {
        if (*(uint *)PTR_DAT_4023ccf0 < 4) {
          FUN_4023f7b4();
          (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__Blocking_uart_read_error__by_4024df98,iVar1);
        }
        goto LAB_4024e0a2;
      }
      if (*(char *)(iVar3 + 0x38) != '\0') {
        if (acStack_3f[0] == '\r') {
          FUN_4024df30(param_1,PTR_DAT_4024df90);
        }
        else {
          uVar2 = uStack_2c;
          if (acStack_3f[0] == '\x7f') {
            uVar2 = 1;
          }
          if (((uVar2 & 0xff) == 0) && (acStack_3f[0] != '\b')) {
            local_40 = acStack_3f[0];
            FUN_40241f20(*(undefined4 *)(param_1 + 0x334),0xffffffff);
            FUN_40244068(param_1,&local_40,iVar1);
            FUN_40241efc(*(undefined4 *)(param_1 + 0x334));
          }
          else if (*(int *)(param_1 + 4) != 0) {
            FUN_4024df30(param_1,PTR_s__c__c_4024df94,8,8);
            *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -1;
          }
        }
      }
      if (acStack_3f[0] == '\r') goto LAB_4024e04d;
      if (((byte)(acStack_3f[0] - 0x20U) < 0x5f) &&
         ((iVar1 = *(int *)(param_1 + 4), iVar1 != 0 || (acStack_3f[0] != ' ')))) {
        *(int *)(param_1 + 4) = iVar1 + 1;
        *(char *)(param_2 + iVar1) = acStack_3f[0];
      }
    } while (*(uint *)(param_1 + 4) < uStack_30);
  } while( true );
}
