
char __cdecl sub_81080(int a1)
{
    int v2[7]; // [esp+0h] [ebp-2Ch] BYREF
    __int16 v3; // [esp+1Ch] [ebp-10h]
    int v4; // [esp+20h] [ebp-Ch]
    int j; // [esp+24h] [ebp-8h]
    int i; // [esp+28h] [ebp-4h]

    memset(v2, 0, sizeof(v2));
    v3 = 0;
    for ( i = 0; i < 20; ++i )
    {
        v4 = a1 - 64;                   //i+ai位的取值
        *((_BYTE *)v2 + i) = byte_83000[*(char *)(i + a1)];
    }
    for ( j = 0; j < 20; ++j )
    {
        if ( *((char *)v2 + j) != byte_83080[j] )   //要相等才满足
            return 0;
    }
    return 1;
}

00083000  FF FF FF FF 01 00 00 00  00 00 00 00 00 00 00 00  //15
                                7
00083010  01 00 00 00 4E E6 40 BB  B1 19 BF 44 01 00 00 00  //31
                                23
00083020  7E 7D 7C 7B 7A 79 78 77  76 75 74 73 72 71 70 6F  //47
                                39
00083030  6E 6D 6C 6B 6A 69 68 67  66 65 64 63 62 61 60 5F  //63
                                55
00083040  5E 5D 5C 5B 5A 59 58 57  56 55 54 53 52 51 50 4F  //79
                                71
00083050  4E 4D 4C 4B 4A 49 48 47  46 45 44 43 42 41 40 3F  //95
                                87
00083060  3E 3D 3C 3B 3A 39 38 37  36 35 34 33 32 31 30 2F  //111
                                103
00083070  2E 2D 2C 2B 2A 29 28 27  26 25 24 23 22 21 20 00  //127
                                119

00083080  38 32 3D 37 23 2B 31 3B  3F 35 30 3A 39 26 3F 39  //V2得是这个
00083090  3D 2B 25 21 
                      00 00 00 00  00 00 00 00 00 00 00 00
102 108 97  103 123 115 109 99       95 105 110 100 101 120 95 101
97  115 121 125

flag{smc_index_easy}

102 107 95  100 119 110 103 92       87 96  100 89  89  107 81 86
81  98  103 106

f k _ d w n g \ W ` d Y Y k Q V
Q b g j

fk_dwng\W`dYYkQVQbgj

int __cdecl main(int argc, const char **argv, const char **envp)
{
  puts("Please input flag:");
  sub_81040("%20s", (char)byte_833FC);
  if ( strlen(byte_833FC) == 20 && (unsigned __int8)sub_81080(byte_833FC) )
    puts("Right!");
  else
    puts("Wrong!");
  system("pause");
  return 10086;
}


/*
输入为20byte长，

*/