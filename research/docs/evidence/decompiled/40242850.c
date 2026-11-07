// Ghidra 12.1.4; synthetic ELF; 40242850

int FUN_40242850(int param_1,uint param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_40 [4];
  int iStack_30;
  uint uStack_2c;

  iStack_30 = param_1;
  iVar1 = (*(code *)PTR_FUN_4023cf0c)(0x400);
  if (iVar1 == 0) {
    iVar3 = -1;
    if (*(uint *)PTR_DAT_4023ccf0 < 4) {
      FUN_4023f7b4();
      (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__malloc_buf_error_40242834);
    }
  }
  else {
    iVar3 = FUN_4024e224(local_40);
    uVar4 = 0;
    if (iVar3 < 0) {
      if (*(uint *)PTR_DAT_4023ccf0 < 4) {
        FUN_4023f7b4();
        puVar2 = PTR_s__E__xmodem_get_crc_error_40242838;
LAB_40242957:
        (*(code *)PTR_FUN_4023ccf8)(puVar2);
      }
    }
    else {
      while (uVar4 < param_2) {
        uStack_2c = param_2 - uVar4;
        if (0x400 < uStack_2c) {
          uStack_2c = 0x400;
        }
        iVar3 = FUN_4023fa6c(uVar4 + iStack_30,iVar1,uStack_2c);
        if (iVar3 != 0) {
          if (*(uint *)PTR_DAT_4023ccf0 < 4) {
            FUN_4023f7b4();
            puVar2 = PTR_s__E__read_from_flash_error_4024283c;
LAB_40242903:
            (*(code *)PTR_FUN_4023ccf8)(puVar2);
          }
LAB_40242981:
          FUN_4024e6f4();
          break;
        }
        uVar4 = uVar4 + uStack_2c;
        if (uVar4 < param_2) {
          if ((uStack_2c & 0x7f) != 0) {
            iVar3 = -1;
            if (*(uint *)PTR_DAT_4023ccf0 < 4) {
              FUN_4023f7b4();
              puVar2 = PTR_s__E__read_size_error_40242840;
              goto LAB_40242903;
            }
            goto LAB_40242981;
          }
          iVar3 = FUN_4024e2c4(local_40[0],iVar1,uStack_2c,0x80);
          if (iVar3 != 0) {
            if (*(uint *)PTR_DAT_4023ccf0 < 4) {
              FUN_4023f7b4();
              puVar2 = PTR_s__E__xmodem_transfer_end_error_40242844;
              goto LAB_40242957;
            }
            break;
          }
        }
        else {
          if (uVar4 != param_2) {
            iVar3 = -1;
            if (*(uint *)PTR_DAT_4023ccf0 < 4) {
              FUN_4023f7b4();
              puVar2 = PTR_s__E__read_flash_size_error_4024284c;
              goto LAB_40242903;
            }
            goto LAB_40242981;
          }
          iVar3 = FUN_4024e4b4(local_40[0],iVar1,uStack_2c,0x80);
          if (iVar3 != 0) {
            if (*(uint *)PTR_DAT_4023ccf0 < 4) {
              FUN_4023f7b4();
              puVar2 = PTR_s__E__xmodem_transfer_end_error_40242848;
              goto LAB_40242957;
            }
            break;
          }
        }
        iVar3 = 0;
      }
    }
    (*(code *)PTR_FUN_4023cf10)(iVar1);
  }
  return iVar3;
}
