// Ghidra 12.1.4; synthetic ELF; 4024b13c

void FUN_4024b13c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;

  iVar1 = *(int *)(*DAT_4024b134 + 8);
  piVar3 = DAT_4024b134;
  if (iVar1 != 0) {
    FUN_40244640(iVar1,*(undefined4 *)(*DAT_4024b134 + 0xc),param_1,param_2);
  }
  if (*(uint *)PTR_DAT_4023ccf0 < 2) {
    FUN_4023f7b4();
    iVar1 = *piVar3;
    uVar2 = FUN_40241ba8(*(undefined4 *)(iVar1 + 4));
    (*(code *)PTR_FUN_4023ccf8)
              (PTR_s__I__discard__s__err__s_t__d__4024b138,iVar1 + 0x54,param_2,uVar2);
  }
  (*(code *)PTR_FUN_4023cf10)(*piVar3);
  *piVar3 = 0;
  return;
}
