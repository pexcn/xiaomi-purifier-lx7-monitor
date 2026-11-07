// Ghidra 12.1.4; synthetic ELF; 4023fc88

undefined4 FUN_4023fc88(undefined4 param_1,code *param_2,undefined4 param_3)

{
  int iVar1;
  uint extraout_a2;
  uint uVar2;
  undefined *puVar3;
  int extraout_a2_00;
  uint uVar4;
  undefined4 extraout_a3;
  undefined4 extraout_a3_00;
  uint uVar5;
  undefined4 extraout_a4;
  undefined4 extraout_a4_00;
  int iVar6;
  int iStack_40;
  int iStack_3c;
  uint uStack_30;

  iVar1 = (*(code *)PTR_FUN_4023cf0c)(0x100);
  if (iVar1 == 0) {
    if (param_2 != (code *)0x0) {
      FUN_40244640(param_2,param_3,0xfffffffb,PTR_s_no_mem_4023fc84);
    }
  }
  else {
    FUN_40205544();
    uVar2 = extraout_a2 & 0xff;
    puVar3 = PTR_s_NOTCONNECTED_4023fc64;
    if ((uVar2 == 0) || (puVar3 = PTR_s_NOTCONNECTED_4023fc68, uVar2 == 2)) {
      (*(code *)PTR_FUN_4023ccf8)(puVar3);
      puVar3 = PTR_s_NOTCONNECTED_4023fc50;
    }
    else if (uVar2 == 1) {
      (*(code *)PTR_FUN_4023ccf8)(PTR_s_CONNECTING_4023fc6c);
      puVar3 = PTR_s_CONNECTING_4023fc54;
    }
    else {
      puVar3 = PTR_s_unknown_4023fc58;
      if (uVar2 == 5) {
        (*(code *)PTR_FUN_4023ccf8)
                  (PTR_s_CONNECTED_4023fc70,extraout_a3,extraout_a4,PTR_s_unknown_4023fc58);
        FUN_402444dc();
        puVar3 = PTR_s_CONNECTED_3ffe94be_3_4023fc5c;
        if (extraout_a2_00 != 0) {
          (*(code *)PTR_FUN_4023ccf8)
                    (PTR_s_ONLINE_4023fc74,extraout_a3_00,extraout_a4_00,
                     PTR_s_CONNECTED_3ffe94be_3_4023fc5c);
          puVar3 = PTR_s_ONLINE_4023fc60;
        }
      }
    }
    uVar2 = FUN_4020a2fc(iVar1,0x100,PTR_s___result____state____s___auth_fa_4023fc78,puVar3,0,1,0,0)
    ;
    if (0x100 < uVar2) {
      uVar2 = 0x100;
    }
    uStack_30 = 0x100 - uVar2;
    uVar4 = FUN_4020a2fc(iVar1 + uVar2,uStack_30,PTR_s____3ffe9fc7_0x2a_4023fc7c);
    uVar5 = uStack_30;
    if (uVar4 < uStack_30) {
      uVar5 = uVar4;
    }
    iVar6 = uVar5 + uVar2;
    (*(code *)PTR_FUN_4023ccf8)(PTR_DAT_4023fc80,iVar1);
    (*DAT_4023d19c)(&iStack_40,0,0xc);
    iStack_40 = iVar1;
    iStack_3c = iVar6;
    if (param_2 != (code *)0x0) {
      (*param_2)(&iStack_40,param_3);
    }
    (*(code *)PTR_FUN_4023cf10)(iVar1);
  }
  return 0;
}
