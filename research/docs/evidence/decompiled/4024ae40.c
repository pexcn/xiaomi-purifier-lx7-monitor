// Ghidra 12.1.4; synthetic ELF; 4024ae40

void FUN_4024ae40(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5
                 )

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined1 auStack_90 [96];
  uint uStack_30;

  param_1 = param_1 & 0xff;
  if (param_3 == 0) {
    uVar1 = FUN_4020a2fc(auStack_90,0x52,PTR_s__s_3ffea401_0xa_4024ae3c,param_2);
    if (0x52 < uVar1) {
      uVar1 = 0x52;
    }
    uStack_30 = 0x52 - uVar1;
    uVar2 = FUN_4020a2fc(auStack_90 + uVar1,uStack_30,PTR_s__s_3ffea401_0xa_4024ae3c,param_4);
    uVar3 = uStack_30;
    if (uVar2 < uStack_30) {
      uVar3 = uVar2;
    }
    iVar4 = uVar3 + uVar1;
  }
  else {
    if (0x52 < param_3) {
      param_3 = 0x52;
    }
    (*DAT_4023c0bc)(auStack_90,param_2,param_3);
    uStack_30 = 0x52 - param_3;
    uVar1 = FUN_4020a2fc(auStack_90 + param_3,uStack_30,PTR_s__s_3ffea401_0xa_4024ae3c,param_4);
    if (uStack_30 < uVar1) {
      uVar1 = uStack_30;
    }
    iVar4 = uVar1 + param_3;
  }
  FUN_4024adc0(param_1,auStack_90,iVar4,param_5);
  return;
}
