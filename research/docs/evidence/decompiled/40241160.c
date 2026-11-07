// Ghidra 12.1.4; synthetic ELF; 40241160

undefined4 FUN_40241160(undefined4 param_1,code *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int local_20;
  int iStack_1c;
  undefined4 uStack_18;

  iVar1 = (*(code *)PTR_FUN_4023cf0c)(1000);
  if (iVar1 == 0) {
    FUN_40244640(param_2,param_3,0xfffffffb,PTR_s_Mem_error__4024115c);
  }
  else {
    (*DAT_4023f16c)(iVar1,PTR_s___result____40241158);
    iStack_1c = FUN_40240f28(iVar1 + 0xb,0x3dd,0);
    iVar2 = iVar1 + iStack_1c;
    iStack_1c = iStack_1c + 0xe;
    *(undefined1 *)(iVar2 + 0xb) = 0x7d;
    *(undefined1 *)(iVar2 + 0xc) = 0x7d;
    *(undefined1 *)(iVar2 + 0xd) = 0;
    uStack_18 = 0;
    local_20 = iVar1;
    if (param_2 != (code *)0x0) {
      (*param_2)(&local_20,param_3);
    }
    (*(code *)PTR_FUN_4023cf10)(iVar1);
  }
  return 0;
}
