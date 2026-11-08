// Ghidra 12.1.4; synthetic ELF; 40219750

void FUN_40219750(uint param_1)

{
  char cVar1;
  undefined1 *puVar2;
  undefined *puVar3;
  undefined1 uVar4;
  uint uVar5;
  int iVar6;

  puVar2 = DAT_40219734;
  iVar6 = DAT_402190bc;
  if (param_1 == 0) {
    *DAT_40219728 = 0;
    *(undefined1 *)(iVar6 + 0xea) = 0;
    *(undefined1 *)(iVar6 + 0xe8) = 0;
    (*(code *)PTR_FUN_402021c0)(PTR_s_sleep__s_4021972c,PTR_s_disable_40219730);
  }
  else {
    cVar1 = *(char *)(DAT_402190bc + 0xea);
    uVar4 = *DAT_40219734;
    *(undefined1 *)(DAT_402190bc + 0xea) = 1;
    if (cVar1 == '\0') {
      uVar4 = 1;
    }
    *puVar2 = uVar4;
    (*(code *)PTR_FUN_402021c0)(PTR_s_sleep__s_40219738,PTR_s_enable_4021973c);
    puVar3 = PTR_s_light_sleep_is_not_supported_now_40219740;
    if ((param_1 == 1) || (param_1 == 2)) {
      uVar5 = (uint)*(byte *)(iVar6 + 0xe8);
      if (param_1 != uVar5) {
        if (param_1 == 1) {
          *DAT_40219728 = DAT_4021974c;
          FUN_4021bda8();
          uVar5 = param_1;
        }
        else {
          *DAT_40219728 = 0;
          (*(code *)PTR_FUN_402021c0)(puVar3);
          FUN_4021bda8(100);
          uVar5 = param_1;
        }
        *(char *)(iVar6 + 0xe8) = (char)uVar5;
      }
      (*(code *)PTR_FUN_402021c0)(PTR_s__type___d_40219744,uVar5);
    }
    else {
      *(char *)(iVar6 + 0xe9) = (char)param_1;
    }
  }
  (*(code *)PTR_FUN_402021c0)(PTR_DAT_40219748);
  return;
}
