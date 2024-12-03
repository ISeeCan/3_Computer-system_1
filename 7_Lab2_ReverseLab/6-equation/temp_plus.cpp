//解释版内容如下
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int j; // [rsp+20h] [rbp-18h]
  int i; // [rsp+24h] [rbp-14h]
  int v6; // [rsp+28h] [rbp-10h]

  sub_140001B80(&unk_140003250, Str, 40i64);    //猜测为读入函数

  //现在是一堆dword进行乱七八糟的操作(32位)   qword是64位
  if ( strlen(Str) == 32 )
  {
    dword[4] += 16;
    dword[3] += Str[3] * dword[4];
    dword[4] += 3;
    dword[3] += Str[2] * dword[4];
    dword[4] -= 10;
    dword[0] += Str[3] * dword[4];
    dword[4] -= 2;
    dword[1] += Str[2] * dword[4];
    dword[4] += 13;
    dword[0] += Str[1] * dword[4];
    dword[4] -= 8;
    dword[2] += Str[1] * dword[4];
    dword[4] -= 7;
    dword[2] -= 3481;
    dword[4] += 3;
    dword[1] -= 2422;
    dword[4] += 9;
    dword[0] += Str[2] * dword[4];
    dword[4] -= 2;
    dword[2] += Str[2] * dword[4];
    dword[4] -= 6;
    dword[0] -= 4518;
    dword[4] += 7;
    dword[3] -= 5006;
    dword[4] -= 9;
    dword[1] += Str[0] * dword[4];
    dword[4] += 5;
    dword[0] += Str[0] * dword[4];
    v6 = dword[4] + 1;
    dword[4] = v6;
    dword[2] += Str[0] * v6;
    dword[4] -= 8;
    dword[2] += Str[3] * dword[4];
    dword[4] += 14;
    dword[3] += Str[0] * dword[4];
    dword[4] -= 11;
    dword[1] += Str[3] * dword[4];
    dword[4] += 3;
    dword[3] += Str[1] * dword[4];
    dword[4] -= 2;
    dword[1] += Str[1] * dword[4];
    for ( i = 0; i < 4; ++i )
    {
      if ( dword[i] )
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


