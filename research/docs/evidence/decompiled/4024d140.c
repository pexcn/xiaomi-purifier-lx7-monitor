// Ghidra 12.1.4; synthetic ELF; 4024d140

undefined4 FUN_4024d140(byte *param_1)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;

  if ((param_1 == (byte *)0x0) || (*param_1 == 0)) {
LAB_4024d195:
    uVar3 = 0xfffffffa;
  }
  else {
    uVar2 = (*DAT_4023d3c0)(param_1);
    if (uVar2 < 0x20) {
      for (; bVar1 = *param_1, bVar1 != 0; param_1 = param_1 + 1) {
        if (((9 < (byte)(bVar1 - 0x30)) && (0x19 < (byte)((bVar1 & 0xdf) + 0xbf))) &&
           (bVar1 != 0x5f)) goto LAB_4024d195;
      }
      uVar3 = 0;
    }
    else {
      uVar3 = 0xfffffffc;
    }
  }
  return uVar3;
}
