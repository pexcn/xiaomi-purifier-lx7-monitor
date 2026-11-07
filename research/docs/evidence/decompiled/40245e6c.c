// Ghidra 12.1.4; synthetic ELF; 40245e6c

int FUN_40245e6c(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  byte *pbVar7;
  code *pcVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined *puVar11;
  char *pcVar12;
  uint uVar13;
  uint *puVar14;
  int iVar15;
  undefined8 uVar16;
  uint *local_f0 [4];
  uint uStack_e0;
  int iStack_dc;
  undefined4 *apuStack_9c [8];
  int iStack_7c;
  undefined4 *puStack_78;
  int iStack_74;
  int iStack_70;
  undefined4 *puStack_6c;
  int iStack_68;
  uint uStack_64;
  int iStack_60;
  undefined4 uStack_5c;
  ushort auStack_58 [4];
  uint *puStack_50;
  uint uStack_4c;
  undefined4 *puStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  uint uStack_2c;
  undefined4 *puStack_28;

  puVar14 = &uStack_e0;
  iStack_3c = FUN_4024ef00(param_1,&uStack_5c);
  puStack_50 = puVar14;
  if (iStack_3c == 0) {
    do {
      auStack_58[0] = 0;
      iStack_60 = 0;
      iVar2 = FUN_402408dc(uStack_5c,&iStack_60,auStack_58);
      if ((iVar2 != 0) || (uVar3 = (uint)auStack_58[0], uVar3 == 0)) break;
      iStack_44 = iStack_60;
      uStack_4c = uVar3;
      if (*(uint *)PTR_DAT_4023ccf0 < 2) {
        FUN_4023f7b4();
        (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__ott__dbytes_recvd_40245dc4,uStack_4c);
      }
      iStack_30 = param_1 + 0x40a;
      do {
        while( true ) {
          iVar2 = param_1 + 0x400;
          uVar3 = (uint)*(ushort *)(param_1 + 0x408);
          if ((uVar3 < 0x20) && (uStack_4c != 0)) {
            uVar4 = uStack_4c;
            if (0x20 - uVar3 < uStack_4c) {
              uVar4 = 0x20 - uVar3;
            }
            (*DAT_4023c0bc)(param_1 + uVar3 + 0x20,iStack_44,uVar4);
            iStack_44 = iStack_44 + uVar4;
            uStack_4c = uStack_4c - uVar4;
            *(short *)(iVar2 + 8) = (short)uVar4 + *(short *)(iVar2 + 8);
          }
          if (*(ushort *)(iVar2 + 8) < 0x20) goto LAB_40245f5c;
          if (*(ushort *)(param_1 + 0x20) == DAT_402451c8) break;
          for (pcVar12 = (char *)(param_1 + 0x20);
              (pcVar12 < (char *)(param_1 + 0x3f) && ((*pcVar12 != '!' || (pcVar12[1] != '1'))));
              pcVar12 = pcVar12 + 1) {
          }
          uVar3 = (param_1 + 0x40) - (int)pcVar12;
          *(short *)(iVar2 + 8) = (short)uVar3;
          (*DAT_4023c0bc)((char *)(param_1 + 0x20),pcVar12,uVar3 & 0xffff);
          if (*(uint *)PTR_DAT_4023ccf0 < 3) {
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__ott_Disorder_restructure_it__40245dc8);
          }
        }
        uVar3 = FUN_402650ec(*(undefined2 *)(param_1 + 0x22));
        if (uVar3 < 1000) {
          uVar4 = uVar3 - *(ushort *)(iVar2 + 8);
          if (uStack_4c < uVar4) {
            uVar4 = uStack_4c;
          }
          (*DAT_4023c0bc)(param_1 + *(ushort *)(iVar2 + 8) + 0x20,iStack_44,uVar4);
          *(short *)(iVar2 + 8) = (short)uVar4 + *(short *)(iVar2 + 8);
          uStack_4c = uStack_4c - uVar4;
          iStack_44 = iStack_44 + uVar4;
        }
        else {
          if (*(uint *)PTR_DAT_4023ccf0 < 4) {
            FUN_4023f7b4();
            (*(code *)PTR_FUN_4023ccf8)(PTR_s__E__ott_len__d__exceed__40245dcc,uVar3);
          }
          uVar4 = uVar3 - *(ushort *)(iVar2 + 8);
          if (uStack_4c < uVar4) {
            uVar4 = uStack_4c;
          }
          uVar13 = *(ushort *)(iVar2 + 8) + uVar4;
          iStack_44 = iStack_44 + uVar4;
          uStack_4c = uStack_4c - uVar4;
          if ((uVar13 & 0xffff) != uVar3) {
            *(short *)(iVar2 + 8) = (short)uVar13;
            break;
          }
          *(undefined2 *)(iVar2 + 8) = 0;
        }
        if (*(ushort *)(iVar2 + 8) == uVar3) {
          iStack_38 = FUN_402650ec(*(undefined2 *)(param_1 + 0x22));
          if (*(ushort *)(param_1 + 0x20) == DAT_402451c8) {
            iStack_34 = param_1 + 0x20;
            iVar5 = (*DAT_4023dedc)(param_1 + 0x24,iStack_30,8);
            if (iVar5 == 0) {
              uVar3 = 0x10;
              iVar5 = param_1 + 0x30;
              (*DAT_4023c0bc)(apuStack_9c,iVar5,0x10);
              (*DAT_4023c0bc)(iVar5,param_1 + 0x412,uVar3);
              uVar6 = FUN_402650ec(*(undefined2 *)(param_1 + 0x22));
              FUN_4023f8b8(iStack_34,uVar6,(int)local_f0 + uVar3);
              iStack_40 = (*DAT_4023dedc)(apuStack_9c,(int)local_f0 + uVar3,uVar3);
              if (iStack_40 == 0) {
                puVar9 = (undefined4 *)FUN_402650ec(*(undefined2 *)(param_1 + 0x22));
                iVar5 = iStack_40;
                if ((undefined4 *)0x20 < puVar9) {
                  apuStack_9c[0] = puVar9 + -8;
                  puStack_48 = apuStack_9c[0];
                  puStack_28 = puVar9;
                  iVar5 = (*(code *)PTR_FUN_4023cf0c)(puVar9);
                  if (iVar5 == 0) {
                    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                      FUN_4023f7b4();
                      puVar11 = PTR_s__W__ott__no_memory_for_decrypt__40245dec;
                      goto LAB_402462a0;
                    }
                  }
                  else {
                    (*DAT_4023c0bc)(&uStack_e0,iVar2 + 0x32,uVar3);
                    iVar2 = param_1 + 0x40;
                    local_f0[0] = &uStack_e0;
                    FUN_4023f864(iVar2,puStack_48,iVar5,apuStack_9c,param_1 + 0x422,uVar3);
                    (*DAT_4023c0bc)(iVar2,iVar5,puStack_48);
                    (*(code *)PTR_FUN_4023cf10)(iVar5);
                    pbVar7 = (byte *)((int)puStack_28 + iStack_34 + -1);
                    uVar4 = (uint)*pbVar7;
                    if (uVar4 <= uVar3) {
                      uVar4 = uVar4 - (int)pbVar7;
                      for (; ((uint)(pbVar7 + (uVar4 & 0xff)) & 0xff) != 0; pbVar7 = pbVar7 + -1) {
                        *pbVar7 = (byte)iStack_40;
                      }
                      iVar5 = 0;
                      goto LAB_402462a9;
                    }
                    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                      FUN_4023f7b4();
                      (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__ott_padding_err__u___40245de8,uVar4);
                    }
                  }
                  goto LAB_402462a6;
                }
              }
              else {
                if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                  FUN_4023f7b4();
                  puVar11 = PTR_s__W__ott_hash_wrong__40245de4;
LAB_402462a0:
                  (*(code *)PTR_FUN_4023ccf8)(puVar11);
                }
LAB_402462a6:
                iVar5 = -1;
              }
LAB_402462a9:
              uVar1 = FUN_402650ec(*(undefined2 *)(param_1 + 0x22));
              *(char *)(param_1 + 0x22) = (char)uVar1;
              *(char *)(param_1 + 0x23) = (char)((ushort)uVar1 >> 8);
              uVar6 = FUN_402405e4(*(undefined4 *)(param_1 + 0x2c));
              *(char *)(param_1 + 0x2c) = (char)uVar6;
              *(char *)(param_1 + 0x2d) = (char)((uint)uVar6 >> 8);
              *(char *)(param_1 + 0x2e) = (char)((uint)uVar6 >> 0x10);
              *(char *)(param_1 + 0x2f) = (char)((uint)uVar6 >> 0x18);
              if (iVar5 == 0) {
                iVar5 = FUN_40241c4c();
                iVar5 = iVar5 - *(int *)(param_1 + 0x2c);
                iVar2 = iVar5;
                if (iVar5 < 1) {
                  iVar2 = -iVar5;
                }
                if (5 < iVar2) {
                  puVar14 = (uint *)PTR_DAT_4023ccf0;
                  if (*(uint *)PTR_DAT_4023ccf0 < 2) {
                    FUN_4023f7b4();
                    (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__ott_ts_diff__d__40245df4,iVar5);
                  }
                  if (0x3c < iVar2) {
                    if (*puVar14 < 3) {
                      FUN_4023f7b4();
                      puVar11 = PTR_s__W__ott_out_of_sync__Skip__40245df8;
                      goto LAB_4024644f;
                    }
                    goto LAB_4024673d;
                  }
                }
                if (iStack_38 == 0x20) {
                  iVar2 = param_1 + 0x500;
                  if (*(int *)(param_1 + 0x544) != 0) {
                    iVar15 = *(int *)(param_1 + 0x570);
                    iVar5 = FUN_40241bd8();
                    *(int *)(iVar2 + 0x70) = iVar5 + iVar15;
                  }
                  *(undefined4 *)(iVar2 + 0x44) = 0;
                  puVar11 = PTR_LAB_4024583c;
                  *(int *)(iVar2 + 0x6c) = *(int *)(iVar2 + 0x6c) + 1;
                  iVar5 = FUN_4024a194(*(undefined4 *)(param_1 + 4),puVar11,DAT_40245840);
                  if ((iVar5 == 0) && (*(uint *)PTR_DAT_4023ccf0 < 2)) {
                    FUN_4023f7b4();
                    (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__Keepalive_acked___stop__40245dfc);
                  }
                  if (*(char *)(iVar2 + 0x7c) == '\x03') {
                    uVar3 = FUN_40241bfc();
                    uVar6 = 0;
                    if (0x71c < uVar3) {
                      uVar1 = FUN_40241b60();
                      uVar16 = (*DAT_40245e5c)(uVar1);
                      uVar16 = (*DAT_40245e60)((int)uVar16,(int)((ulonglong)uVar16 >> 0x20),
                                               DAT_4024451c,DAT_40245e00);
                      (*DAT_40245e64)((int)uVar16,(int)((ulonglong)uVar16 >> 0x20),DAT_4024451c,
                                      DAT_40245e04);
                      uVar6 = (*DAT_40245e68)();
                      if (*(int *)PTR_DAT_4023ccf0 == 0) {
                        FUN_4023f7b4();
                        (*(code *)PTR_FUN_4023ccf8)
                                  (PTR_s__D__Report_info_delay__u_ms__40245e08,uVar6);
                      }
                    }
                    FUN_4024a134(*(undefined4 *)(param_1 + 4),PTR_FUN_40245690,uVar6,param_1,0);
                    *(undefined1 *)(iVar2 + 0x7c) = 4;
                    FUN_4024a6b0(*(undefined4 *)(param_1 + 4),PTR_s_ot_online_40245e0c,0);
                  }
                }
                else {
                  iVar2 = (*(code *)PTR_FUN_4023cf0c)(DAT_40216e34);
                  if (iVar2 == 0) {
                    if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                      FUN_4023f7b4();
                      puVar11 = PTR_s__W__Json_alloc_err__40245e10;
                      goto LAB_4024644f;
                    }
                  }
                  else {
                    puStack_48 = (undefined4 *)(*(ushort *)(param_1 + 0x22) - 0x20);
                    FUN_40265704(&uStack_e0);
                    iVar5 = param_1 + 0x40;
                    uVar3 = FUN_40265408(&uStack_e0,iVar5,puStack_48,iVar2,200);
                    if (uVar3 == 0) {
                      *(undefined4 *)(iStack_dc * 0xc + iVar2) = 0;
                      puStack_6c = puStack_48;
                      iStack_70 = iVar5;
                      iStack_68 = iVar2;
                      uStack_64 = uVar3;
                      iVar15 = FUN_4024ab80(iVar5,iVar2,PTR_DAT_40245e18,&uStack_64);
                      if (iVar15 == 0) {
                        uVar3 = uStack_64;
                      }
                      uStack_64 = uVar3;
                      iVar15 = FUN_4024a87c(iVar5,iVar2,PTR_s_method_40245e1c);
                      iStack_40 = FUN_4024a87c(iVar5,iVar2,PTR_DAT_40245e20);
                      if (iVar15 == 0) {
                        if (uStack_64 != 0) {
                          if (*(uint *)PTR_DAT_4023ccf0 < 2) {
                            FUN_4023f7b4();
                            (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__ott_valid_up_ack__40245e50);
                          }
                          iStack_dc = 0;
                          uStack_e0 = uStack_64;
                          uVar3 = uStack_64;
                          FUN_402653d0(param_1,PTR_LAB_40245e54,&uStack_e0);
                          if (iStack_dc == 0) {
                            if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                              FUN_4023f7b4();
                              puVar11 = PTR_s__W__ott_no_session_resp_id__u__40245e58;
                              goto LAB_4024672e;
                            }
                          }
                          else {
                            iVar15 = param_1 + 0x500;
                            iVar5 = iStack_dc;
                            if (*(int *)(iStack_dc + 0x14) != 0) {
                              uStack_2c = *(uint *)(param_1 + 0x570);
                              iVar10 = FUN_40241bd8();
                              *(uint *)(iVar15 + 0x70) = iVar10 + uStack_2c;
                            }
                            *(undefined4 *)(iVar5 + 0x14) = 0;
                            *(int *)(iVar15 + 0x6c) = *(int *)(iVar15 + 0x6c) + 1;
                            FUN_4024a258(*(undefined4 *)(param_1 + 4),iVar5);
                            (**(code **)(iVar5 + 0xc))(&iStack_70,*(undefined4 *)(iVar5 + 0x10));
                            FUN_40265394(param_1,iVar5);
                            FUN_4024a698(iVar5);
                          }
                        }
                      }
                      else {
                        uStack_2c = (int)*(short *)(iVar15 + 8) - (int)*(short *)(iVar15 + 6);
                        if (0x1f < uStack_2c) {
                          uStack_2c = 0x1f;
                        }
                        (*DAT_4023c0bc)(apuStack_9c,iVar5 + *(short *)(iVar15 + 6),uStack_2c);
                        *(undefined1 *)((int)apuStack_9c + uStack_2c) = 0;
                        if (*(uint *)PTR_DAT_4023ccf0 < 2) {
                          FUN_4023f7b4();
                          (*(code *)PTR_FUN_4023ccf8)
                                    (PTR_s__I__ott_valid_down_req__s__40245e24,apuStack_9c);
                        }
                        uVar3 = uStack_64;
                        iVar5 = FUN_4024ac20(iStack_70,iStack_68,PTR_s_sid_3ffe8ea9_9_40245e28,
                                             &uStack_e0,0x41,0);
                        if (iVar5 != 0) {
                          uStack_e0 = uStack_e0 & 0xffffff00;
                        }
                        iVar5 = FUN_4024a87c(iStack_70,iStack_68,PTR_s_params_40245e2c);
                        if (iVar5 == 0) {
                          FUN_40245518(param_1,uVar3,DAT_40245e30,PTR_s_Req_object_invalid__40245e34
                                      );
                        }
                        else {
                          iStack_7c = iStack_70;
                          puStack_78 = puStack_6c;
                          puVar11 = PTR_s__JsDlgt_40245e3c;
                          if ((uStack_e0 & 0xff) != 0) {
                            puVar11 = PTR_s__JsDlgtS_40245e38;
                          }
                          iStack_74 = iVar5;
                          pcVar8 = (code *)FUN_4024ae40(0x2e,iStack_70 + *(short *)(iVar15 + 6),
                                                        (int)*(short *)(iVar15 + 8) -
                                                        (int)*(short *)(iVar15 + 6),puVar11,0);
                          if (uVar3 == 0) {
                            if (pcVar8 == (code *)0x0) {
                              puVar14 = puStack_50;
                              if ((uStack_e0 & 0xff) == 0) {
                                puVar14 = (uint *)0x0;
                              }
                              uVar3 = 0;
                              puVar11 = (undefined *)0x0;
                              puVar9 = (undefined4 *)0x0;
                              goto LAB_4024667d;
                            }
                            if ((uStack_e0 & 0xff) != 0) {
                              puVar11 = (undefined *)0x0;
                              puVar9 = (undefined4 *)0x0;
                              goto LAB_4024668d;
                            }
                            puVar11 = (undefined *)0x0;
                            puVar9 = (undefined4 *)0x0;
LAB_40246699:
                            (*pcVar8)(&iStack_7c,puVar11,puVar9);
                          }
                          else {
                            puStack_48 = (undefined4 *)FUN_4024a08c(param_1,PTR_FUN_40245e40,0x34);
                            puVar9 = (undefined4 *)FUN_40265324();
                            *(int *)(param_1 + 0x574) = *(int *)(param_1 + 0x574) + 1;
                            if (*(int *)PTR_DAT_4023ccf0 == 0) {
                              uStack_2c = param_1 + 0x500;
                              puStack_28 = puVar9;
                              FUN_4023f7b4();
                              (*(code *)PTR_FUN_4023ccf8)
                                        (PTR_s__D__bill_debug_ott_rpc_cnt__d_40245e44,
                                         *(undefined4 *)(uStack_2c + 0x74));
                              puVar9 = puStack_28;
                            }
                            *puVar9 = DAT_40245e48;
                            *(undefined1 *)(puVar9 + 9) = 0x74;
                            *(undefined1 *)((int)puVar9 + 0x25) = 99;
                            if ((iStack_40 == 0) ||
                               (puStack_28 = puVar9,
                               iVar5 = FUN_4024aae0(iStack_70,iStack_40,puVar9 + 1,0x20,0),
                               puVar9 = puStack_28, iVar5 != 0)) {
                              *(undefined1 *)(puVar9 + 1) = 0;
                            }
                            puVar9[10] = uVar3;
                            puVar9[0xc] = 0;
                            puVar9[0xb] = 0;
                            if (pcVar8 == (code *)0x0) {
                              puVar14 = puStack_50;
                              puVar11 = PTR_FUN_40245e4c;
                              puVar9 = puStack_48;
                              if ((uStack_e0 & 0xff) == 0) {
                                puVar14 = (uint *)0x0;
                              }
LAB_4024667d:
                              FUN_4024c4f4(&iStack_7c,uVar3,puVar14,puVar11,puVar9);
                            }
                            else {
                              puVar11 = PTR_FUN_40245e4c;
                              puVar9 = puStack_48;
                              if ((uStack_e0 & 0xff) == 0) goto LAB_40246699;
LAB_4024668d:
                              (*pcVar8)(&iStack_7c,&uStack_e0,puVar11,puVar9);
                            }
                          }
                        }
                      }
                    }
                    else if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                      FUN_4023f7b4();
                      puVar11 = PTR_s__W__ott_down_req_json_parse_err__40245e14;
LAB_4024672e:
                      (*(code *)PTR_FUN_4023ccf8)(puVar11,uVar3);
                    }
                    (*(code *)PTR_FUN_4023cf10)(iVar2);
                  }
                }
              }
              else if (*(uint *)PTR_DAT_4023ccf0 < 3) {
                FUN_4023f7b4();
                puVar11 = PTR_s__W__ott__sign_or_decrypt_error__40245df0;
                goto LAB_4024644f;
              }
            }
            else if (iStack_38 == 0x20) {
              iVar2 = param_1 + 0x500;
              puVar14 = (uint *)PTR_DAT_4023ccf0;
              if (*(int *)(param_1 + 0x548) != 0) {
                iVar15 = *(int *)(param_1 + 0x570);
                iVar5 = FUN_40241bd8();
                *(int *)(iVar2 + 0x70) = iVar5 + iVar15;
              }
              *(undefined4 *)(iVar2 + 0x48) = 0;
              *(int *)(iVar2 + 0x6c) = *(int *)(iVar2 + 0x6c) + 1;
              FUN_402405e4(*(undefined4 *)(param_1 + 0x2c));
              iVar5 = FUN_40241c6c();
              if (*puVar14 < 2) {
                FUN_4023f7b4();
                (*(code *)PTR_FUN_4023ccf8)(PTR_s__I__ott_recv_sync_diff__d__40245dd4,iVar5);
              }
              if (iVar5 < 1) {
                iVar5 = -iVar5;
              }
              iVar15 = *(int *)(iVar2 + 0x50);
              if (iVar5 < 5) {
                if (iVar15 <= DAT_40245ddc) {
                  iVar15 = iVar15 << 1;
                  goto LAB_40246154;
                }
              }
              else if (DAT_40245dd8 < iVar15) {
                iVar15 = iVar15 >> 1;
LAB_40246154:
                *(int *)(iVar2 + 0x50) = iVar15;
              }
            }
            else if (*(uint *)PTR_DAT_4023ccf0 < 3) {
              FUN_4023f7b4();
              puVar11 = PTR_s__W__ott_DID_err__40245de0;
              goto LAB_4024644f;
            }
          }
          else {
            if (2 < *(uint *)PTR_DAT_4023ccf0) goto LAB_4024673d;
            FUN_4023f7b4();
            puVar11 = PTR_s__W__ott_Ver_err__40245dd0;
LAB_4024644f:
            (*(code *)PTR_FUN_4023ccf8)(puVar11);
          }
LAB_4024673d:
          *(undefined2 *)(param_1 + 0x408) = 0;
        }
      } while (uStack_4c != 0);
LAB_40245f5c:
      iVar2 = FUN_402408fc(uStack_5c);
    } while (-1 < iVar2);
    FUN_402408cc(uStack_5c);
  }
  else if (*(uint *)PTR_DAT_4023ccf0 < 3) {
    FUN_4023f7b4();
    (*(code *)PTR_FUN_4023ccf8)(PTR_s__W__ott__recv_err__d___40245dc0,iStack_3c);
  }
  return iStack_3c;
}
