// Ghidra 12.1.4; synthetic ELF; 402083b0

undefined4 *
FUN_402083b0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  undefined4 *puVar1;

  puVar1 = (undefined4 *)0x0;
  if ((param_2 != 0) &&
     (puVar1 = (undefined4 *)(*(code *)PTR_FUN_40203658)(0x28,PTR_s_timers_c_402083ac,0xf8),
     puVar1 != (undefined4 *)0x0)) {
    FUN_402082b0();
    *puVar1 = param_1;
    puVar1[8] = param_4;
    puVar1[6] = param_2;
    puVar1[9] = param_5;
    puVar1[7] = param_3;
    FUN_4022a6b4(puVar1 + 1);
  }
  return puVar1;
}
