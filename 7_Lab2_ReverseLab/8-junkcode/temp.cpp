// // positive sp value has been detected, the output may be wrong!
// int __usercall sub_C6147C@<eax>(int a1@<ebp>)
// {
//   if ( !strcmp((const char *)(a1 - 280), "P1Ekb1UxW9ErWC6ZVUKiKgMaLSEgS5gpyZOrSQG3tP8g") )
//     puts("right!");
//   else
//     puts("wrong!");
//   system("pause");
//   return 10086;
// }

int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4[200]; // [esp+Ch] [ebp-118h] BYREF
  char v5[50]; // [esp+D4h] [ebp-50h] BYREF

  puts("Input the flag:");
  memset(v5, 0, sizeof(v5));
  memset(v4, 0, sizeof(v4));
  sub_C614D0("%s", (char)v5);
  JUMPOUT(0xC613C8);
}
int sub_C614D0(char *Format, ...)
{
  FILE *v1; // eax
  va_list va; // [esp+14h] [ebp+Ch] BYREF

  va_start(va, Format);
  v1 = _acrt_iob_func(0);
  return sub_C61330(v1, Format, 0, va);
}
int __cdecl sub_C61330(FILE *Stream, char *Format, _locale_t Locale, va_list Arglist)
{
  _DWORD *v4; // eax
  unsigned __int64 v6; // [esp-18h] [ebp-18h]

  v4 = (_DWORD *)sub_C61320();
  HIDWORD(v6) = v4[1];
  LODWORD(v6) = *v4 | 1;
  return _stdio_common_vfscanf(v6, Stream, Format, Locale, Arglist);
}

#include<stdio.h>

int main(void)
{
    int i=0;
    char temp;
    while(1)
    {
        scanf("%c",&temp);
        if(temp == '\n')
            break;
        i++;
    }

    printf("%d",i);

    return 0;
}