//原内容如下：


00000140003250  25 73 00 00 72 69 67 68  74 21 00 00 70 61 75 73
00000140003260  65 00 00 00 00 00 00 00  D0 40 00 40 01 00 00 00
00000140003270  70 41 00 40 01 00 00 00  00 00 00 00 00 00 00 00
00000140003280  FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF


0000000140004040  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
0000000140004050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
0000000140004060  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
0000000140004070  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
0000000140004080  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00


000001400040A0  00 00 00 00 00 00 00 00  
                                         00 00 00 00 00 00 00 00
000001400040B0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
000001400040C0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
000001400040D0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
000001400040E0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
000001400040F0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00

int __cdecl main(int argc, const char **argv, const char **envp)
{
  int j; // [rsp+20h] [rbp-18h]
  int i; // [rsp+24h] [rbp-14h]
  int v6; // [rsp+28h] [rbp-10h]

  sub_140001B80(&unk_140003250, Str, 40i64);
  if ( strlen(Str) == 32 )
  {
    dword_1400040A8[4] += 16;
    dword_1400040A8[3] += Str[3] * dword_1400040A8[4];
    dword_1400040A8[4] += 3;
    dword_1400040A8[3] += Str[2] * dword_1400040A8[4];
    dword_1400040A8[4] -= 10;
    dword_1400040A8[0] += Str[3] * dword_1400040A8[4];
    dword_1400040A8[4] -= 2;
    dword_1400040A8[1] += Str[2] * dword_1400040A8[4];
    dword_1400040A8[4] += 13;
    dword_1400040A8[0] += Str[1] * dword_1400040A8[4];
    dword_1400040A8[4] -= 8;
    dword_1400040A8[2] += Str[1] * dword_1400040A8[4];
    dword_1400040A8[4] -= 7;
    dword_1400040A8[2] -= 3481;
    dword_1400040A8[4] += 3;
    dword_1400040A8[1] -= 2422;
    dword_1400040A8[4] += 9;
    dword_1400040A8[0] += Str[2] * dword_1400040A8[4];
    dword_1400040A8[4] -= 2;
    dword_1400040A8[2] += Str[2] * dword_1400040A8[4];
    dword_1400040A8[4] -= 6;
    dword_1400040A8[0] -= 4518;
    dword_1400040A8[4] += 7;
    dword_1400040A8[3] -= 5006;
    dword_1400040A8[4] -= 9;
    dword_1400040A8[1] += Str[0] * dword_1400040A8[4];
    dword_1400040A8[4] += 5;
    dword_1400040A8[0] += Str[0] * dword_1400040A8[4];
    v6 = dword_1400040A8[4] + 1;
    dword_1400040A8[4] = v6;
    dword_1400040A8[2] += Str[0] * v6;
    dword_1400040A8[4] -= 8;
    dword_1400040A8[2] += Str[3] * dword_1400040A8[4];
    dword_1400040A8[4] += 14;
    dword_1400040A8[3] += Str[0] * dword_1400040A8[4];
    dword_1400040A8[4] -= 11;
    dword_1400040A8[1] += Str[3] * dword_1400040A8[4];
    dword_1400040A8[4] += 3;
    dword_1400040A8[3] += Str[1] * dword_1400040A8[4];
    dword_1400040A8[4] -= 2;
    dword_1400040A8[1] += Str[1] * dword_1400040A8[4];
    for ( i = 0; i < 4; ++i )
    {
      if ( dword_1400040A8[i] )
        goto LABEL_11;
    }
    qword_140004040 = 0x7C007C00100064i64;
    *(&qword_140004040 + 1) = 0x34002F00170022i64;
    *(&qword_140004040 + 2) = 0x3B000B00130013i64;
    *(&qword_140004040 + 3) = 0xF001B001Fi64;
    *(&qword_140004040 + 4) = 0x3C00720005001Ei64;
    *(&qword_140004040 + 5) = 0x40036001F0062i64;
    *(&qword_140004040 + 6) = 0x3F0032002E001Fi64;
    *(&qword_140004040 + 7) = 0i64;
    for ( j = 0; j < 28; ++j )
    {
      if ( (Str[j % 4] ^ Str[j + 4]) != *((char *)&qword_140004040 + 2 * j) )
        goto LABEL_11;
    }
    puts("right!");
  }
LABEL_11:
  system("pause");
  return 10086;
}



__int64 sub_140001B80(__int64 a1, ...)
{
  FILE *v1; // rax
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, a1);
  v1 = _acrt_iob_func(0);
  return (unsigned int)sub_140001010(v1, a1, 0i64, (__int64 *)va);
}

int __fastcall sub_140001010(FILE *a1, const char *a2, __crt_locale_pointers *a3, va_list a4)
{
  _QWORD *v4; // rax

  v4 = (_QWORD *)sub_140001000();
  return _stdio_common_vfscanf(*v4 | 1i64, a1, a2, a3, a4);
}

void *sub_140001000()
{
  return &unk_1400040C0;    //000000000000000
}



