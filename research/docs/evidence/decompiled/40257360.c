// Ghidra 12.1.4; synthetic ELF; 40257360

void FUN_40257360(void)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined1 auStack_30 [44];

  iVar1 = FUN_4023db7c(auStack_30,PTR_s_ot_config_40257350);
  if (iVar1 == 0) {
    puVar3 = PTR_s_xiaomi_dev_v4_4023d3a4;
    puVar4 = PTR_s_psm_model_40257358;
    iVar1 = FUN_4023dc44(auStack_30,PTR_s_psm_model_40257358,PTR_s_xiaomi_dev_v4_4023d3a4,0x1f);
    if (iVar1 != 0) {
      puVar2 = PTR_s_xiaomi_dev_lx1_4025735c;
      FUN_4023dbe0(auStack_30,puVar4,PTR_s_xiaomi_dev_lx1_4025735c);
      (*DAT_4023c0bc)(puVar3,puVar2,0xf);
    }
  }
  else if (*(uint *)PTR_DAT_4023ccf0 < 4) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__open_psm_ot_config_error_40257354);
  }
  FUN_4023dbc0(auStack_30);
  return;
}
