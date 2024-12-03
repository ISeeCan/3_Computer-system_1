int __cdecl main(int argc, const char **argv, const char **envp)
{
  int i; // eax
  HANDLE Handles[2]; // [esp+8h] [ebp-Ch] BYREF

  sub_401020("plz input your flag:");
  sub_401050("%42s", byte_40336C);
  Handles[0] = CreateThread(0, 0, StartAddress, 0, 0, 0);
  Handles[1] = CreateThread(0, 0, loc_401200, 0, 0, 0);
  CreateThread(0, 0, sub_401240, 0, 0, 0);
  WaitForMultipleObjects(2u, Handles, 1, 0xFFFFFFFF);
  for ( i = 0; i < 42; ++i )
  {
    if ( byte_40336C[i] != byte_402150[i] )
    {
      sub_401020("error");
      exit(0);
    }
  }
  sub_401020("win");
  getchar();
  return 0;
}

int __userpurge sub_40120F@<eax>(int a1@<eax>, int a2@<ecx>, int a3)
{
  int v3; // eax
  char v4; // bl

  *(_BYTE *)(a1 + 15) = __ROR1__(*(_BYTE *)(a1 + 15), 182);
  v3 = 0;
  v4 = 100 * (*(_BYTE *)(a2 - 1240466363) + a2);
  do
    byte_40336C[v3++] += v4;
  while ( v3 < 42 );
  return 0;
}


00402150  DD 5B 9E 1D 20 9E 90 91  90 90 91 92 DE 8B 11 D1
00402160  1E 9E 8B 51 11 50 51 8B  9E 5D 5D 11 8B 90 12 91
00402170  50 12 D2 91 92 1E 9E 90  D2 9F 
                                         00 00 00 00 00 00
00402180  3F D3 CC 5E 00 00 00 00  02 00 00 00 59 00 00 00



.text:00401200                               loc_401200:                             ; DATA XREF: _main+4B↓o
.text:00401200 55                            push    ebp
.text:00401201 8B EC                         mov     ebp, esp
.text:00401203 51                            push    ecx
.text:00401204 53                            push    ebx
.text:00401205 56                            push    esi
.text:00401206 57                            push    edi
.text:00401207 64 A1 30 00 00 00             mov     eax, large fs:30h
.text:0040120F C0 48 0F B6                   ror     byte ptr [eax+0Fh], 0B6h
.text:00401213 40                            inc     eax
.text:00401214 02 89 45 FC 0F B6             add     cl, [ecx-49F003BBh]
.text:0040121A 4D                            dec     ebp
.text:0040121B FC                            cld
.text:0040121C 33 C0                         xor     eax, eax
.text:0040121E 6B D9 64                      imul    ebx, ecx, 64h ; 'd'
.text:0040121E
.text:00401221
.text:00401221                               loc_401221:                             ; CODE XREF: .text:0040122D↓j
.text:00401221 8A D3                         mov     dl, bl
.text:00401223 00 90 6C 33 40 00             add     byte_40336C[eax], dl
.text:00401229 40                            inc     eax
.text:0040122A 83 F8 2A                      cmp     eax, 2Ah ; '*'
.text:0040122D 7C F2                         jl      short loc_401221
.text:0040122D
.text:0040122F 5F                            pop     edi
.text:00401230 5E                            pop     esi
.text:00401231 33 C0                         xor     eax, eax
.text:00401233 5B                            pop     ebx
.text:00401234 8B E5                         mov     esp, ebp
.text:00401236 5D                            pop     ebp
.text:00401237 C2 04 00                      retn    4
.text:00401237
.text:00401237                               ; ---------------------------------------------------------------------------
.text:0040123A CC CC CC CC CC CC             align 10h

111111111111111111111111111111111111111111

222222222222222222222222222222222222222222
333333333333333333333333333333333333333333
444444444444444444444444444444444444444444



.text:00401120                               ; DWORD __stdcall StartAddress(LPVOID lpThreadParameter)
.text:00401120                               StartAddress:                           ; DATA XREF: _main+3A↓o
.text:00401120 55                            push    ebp
.text:00401121 8B EC                         mov     ebp, esp
.text:00401123 83 EC 0C                      sub     esp, 0Ch
.text:00401126 53                            push    ebx
.text:00401127 56                            push    esi
.text:00401128 57                            push    edi
.text:00401129 6A 00                         push    0
.text:0040112B 6A 00                         push    0
.text:0040112D 6A 00                         push    0
.text:0040112F 68 E0 10 40 00                push    offset sub_4010E0
.text:00401134 6A 00                         push    0
.text:00401136 6A 00                         push    0
.text:00401138 FF 15 0C 20 40 00             call    ds:CreateThread
.text:00401138
.text:0040113E 89 45 F8                      mov     [ebp-8], eax
.text:00401141 6A FF                         push    0FFFFFFFFh
.text:00401143 68 E0 10 40 00                push    offset sub_4010E0
.text:00401148 FF 15 04 20 40 00             call    ds:WaitForSingleObject
.text:00401148
.text:0040114E 89 45 F4                      mov     [ebp-0Ch], eax
.text:00401151
.text:00401151                               loc_401151:                             ; CODE XREF: .text:loc_401151↑j
.text:00401151 EB FF                         jmp     short near ptr loc_401151+1
.text:00401151
.text:00401151                               ; ---------------------------------------------------------------------------
.text:00401153 C0                            db 0C0h
.text:00401154 48 C7 45 FC 00 00 00 00       dd 0FC45C748h, 0
.text:0040115C EB 09 8B 45 FC 83 C0 01 89 45+dd 458B09EBh, 1C083FCh, 83FC4589h, 0F2AFC7Dh, 808Dh, 0FC4D8B00h
.text:00401174 0F B6 91                      db 0Fh, 0B6h, 91h
.text:00401177 6C 33 40 00                   dd offset byte_40336C
.text:0040117B C1                            db 0C1h
.text:0040117C FA 02 8B 45 FC 0F B6 88       dd 458B02FAh, 88B60FFCh
.text:00401184 6C 33 40 00                   dd offset byte_40336C
.text:00401188 C1 E1 06 33 D1 8B 45 FC       dd 3306E1C1h, 0FC458BD1h
.text:00401190 88 90                         db 88h, 90h
.text:00401192 6C 33 40 00                   dd offset byte_40336C
.text:00401196 8B 4D                         dw 4D8Bh
.text:00401198 FC 0F B6 91                   dd 91B60FFCh
.text:0040119C 6C 33 40 00                   dd offset byte_40336C
.text:004011A0 83 F2 23 8B 45 FC 88 90       dd 8B23F283h, 9088FC45h
.text:004011A8 6C 33 40 00                   dd offset byte_40336C
.text:004011AC 6A 06 FF 15                   dd 15FF066Ah
.text:004011B0 08 20 40 00                   dd offset Sleep
.text:004011B4 64 8B 1D 30 00 00 00 0F B6 5B+dd 301D8B64h, 0F000000h, 33025BB6h, 0E80575C0h, 1, 0C38358E8h, 50C30309h, 0FFEB90C3h, 4D8B48C0h, 91B60FFCh
.text:004011DC 6C 33 40 00                   dd offset byte_40336C
.text:004011E0 83 C2 23 8B 45 FC 88 90       dd 8B23C283h, 9088FC45h
.text:004011E8 6C 33 40 00                   dd offset byte_40336C
.text:004011EC E9 6D FF FF FF 33 C0 5F 5E 5B+dd 0FFFF6DE9h, 5FC033FFh, 0E58B5B5Eh, 4C25Dh, 0CCCCCCCCh
.text:00401200     