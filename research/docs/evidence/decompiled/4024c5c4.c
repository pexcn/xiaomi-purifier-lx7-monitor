// Ghidra 12.1.4; synthetic ELF; 4024c5c4

void FUN_4024c5c4(int param_1,int param_2)

{
  int iVar1;
  undefined1 *puVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 auStack_50 [32];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  int iStack_20;
  int iStack_1c;
  int aiStack_14 [4];

  puVar5 = DAT_4024b060;
  if ((param_1 < 2) ||
     (iVar1 = (*DAT_40241450)(*(undefined4 *)(param_2 + 4),PTR_s_posix_4024c5b4,5), iVar1 != 0)) {
    aiStack_14[0] = FUN_4023ffc0();
    if (DAT_4023f7ac < (uint)(aiStack_14[0] + DAT_4023f7a8)) {
      aiStack_14[0] = DAT_4023f7a4;
    }
    iVar1 = FUN_40241c4c();
    aiStack_14[0] = aiStack_14[0] + iVar1;
    FUN_40209f78(aiStack_14,&uStack_30);
    FUN_4020a2fc(auStack_50,0x20,PTR_s__d__02d__02d__2d__02d__02d_4024c5bc,iStack_1c + 0x76c,
                 iStack_20 + 1,uStack_24,uStack_28,uStack_2c,uStack_30);
    uVar4 = *puVar5;
    puVar2 = auStack_50;
    puVar3 = PTR_s__s_3ffea401_0xa_4024c5c0;
  }
  else {
    uVar4 = *puVar5;
    puVar2 = (undefined1 *)FUN_40241c4c();
    puVar3 = PTR_DAT_4024c5b8;
  }
  FUN_4024e0c0(uVar4,puVar3,puVar2);
  return;
}
