//用程序模拟如下
#include <iostream>
#include <stdio.h>
using namespace std;
int dword[4] = {0,0,0,0};
int dwords[4][5]={0};
int Str[4] = {1,1,1,1};
//str实际上是32个char，但是我们把他当成4个qword读入了
void change(int dwordwhat, int strwhat, int dowrd4)
{ //str==4时是常数更改
  dwords[dwordwhat][strwhat] += dowrd4;
}

int main(void)
{
  int j; // [rsp+20h] [rbp-18h]
  int i; // [rsp+24h] [rbp-14h]
  int v6; // [rsp+28h] [rbp-10h]

  cout << "dwords" << endl;
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<5;j++)
      {
        cout << dwords[i][j] << ' ';
      }
      cout << endl;
    }
    cout << endl;

  //sub_140001B80(&unk_140003250, Str, 40i64);    //猜测为读入函数

  //现在是一堆dword进行乱七八糟的操作
    dword[4] += 16;                         //0-16
    dword[3] += Str[3] * dword[4];
    change(3,3,dword[4]);


    dword[4] += 3;                          //16-19
    dword[3] += Str[2] * dword[4];
    change(3,2,dword[4]);
  
    dword[4] -= 10;                         //19-20
    dword[0] += Str[3] * dword[4];
        change(0,3,dword[4]);
  
    dword[4] -= 2;                          //9-20
    dword[1] += Str[2] * dword[4];
        change(1,2,dword[4]);
  
    dword[4] += 13;                         //7-20
    dword[0] += Str[1] * dword[4];
        change(0,1,dword[4]);
  
    dword[4] -= 8;                          //20-12
    dword[2] += Str[1] * dword[4];
        change(2,1,dword[4]);
  
    dword[4] -= 7;                          //12-5
    dword[2] -= 3481;
        change(2,4,-3481);
  
    dword[4] += 3;                          //5-8
    dword[1] -= 2422;
        change(1,4,-2422);
  
    dword[4] += 9;                          //8-17
    dword[0] += Str[2] * dword[4];
        change(0,2,dword[4]);
  
    dword[4] -= 2;                          //17-15
    dword[2] += Str[2] * dword[4];
        change(2,2,dword[4]);
  
    dword[4] -= 6;                          //15-9
    dword[0] -= 4518;
        change(0,4,-4518);
  
    dword[4] += 7;                          //9-16
    dword[3] -= 5006;
        change(3,4,-5006);
  
    dword[4] -= 9;                          //16-7
    dword[1] += Str[0] * dword[4];
        change(1,0,dword[4]);
  
    dword[4] += 5;                          //7-12
    dword[0] += Str[0] * dword[4];
        change(0,0,dword[4]);
  
    v6 = dword[4] + 1;                      //12
    dword[4] = v6;                          //12-13
    dword[2] += Str[0] * v6;
        change(2,0,dword[4]);
  
    dword[4] -= 8;                          //13-5
    dword[2] += Str[3] * dword[4];
        change(2,3,dword[4]);
  
    dword[4] += 14;                         //5-19
    dword[3] += Str[0] * dword[4];
        change(3,0,dword[4]);
  
    dword[4] -= 11;                         //19-8
    dword[1] += Str[3] * dword[4];
        change(1,3,dword[4]);
  
    dword[4] += 3;                          //8-11
    dword[3] += Str[1] * dword[4];
        change(3,1,dword[4]);
  
    dword[4] -= 2;                          //11-9
    dword[1] += Str[1] * dword[4];
        change(1,1,dword[4]);


    // for ( i = 0; i < 4; ++i )
    // {
    //   if ( dword[i] )
    //     goto LABEL_11;
    // }
    // qword_140004040 = 0x7C007C00100064i64;
    // *(&qword_140004040 + 1) = 0x34002F00170022i64;
    // *(&qword_140004040 + 2) = 0x3B000B00130013i64;
    // *(&qword_140004040 + 3) = 0xF001B001Fi64;
    // *(&qword_140004040 + 4) = 0x3C00720005001Ei64;
    // *(&qword_140004040 + 5) = 0x40036001F0062i64;
    // *(&qword_140004040 + 6) = 0x3F0032002E001Fi64;
    // *(&qword_140004040 + 7) = 0i64;
    // for ( j = 0; j < 28; ++j )
    // {
    //   if ( (Str[j % 4] ^ Str[j + 4]) != *((char *)&qword_140004040 + 2 * j) )
    //     goto LABEL_11;
    // }
    // puts("right!");

    char ans[32] ={0};
    ans[0]=81;
    ans[1]=84;
    ans[2]=69;
    ans[3]=77;

    cout << "dword:";
    cout << dword[4]<< endl;
    
    cout << "dwords" << endl;
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<5;j++)
      {
        cout << dwords[i][j] << ' ';
      }
      cout << endl;
    }
    cout << endl << endl;




    //char x1[8] = 0x 7C 00 7C 00 10 00 64;
    char x1[8] = {0x00,0x7c,0x00,0x7c,0x00,0x10,0x00,0x64};
    // *(&qword_140004040 + 1) = 0x34 00 2F 00 17 00 22;
    char x2[8] = {0x00,0x34,0x00,0x2f,0x00,0x17,0x00,0x22};
    // *(&qword_140004040 + 2) = 0x 3B 00 0B 00 13 00 13;
    char x3[8] = {0x00,0x3b,0x00,0x0b,0x00,0x13,0x00,0x13};
    // *(&qword_140004040 + 3) = 0xF 00 1B 00 1F;
    char x4[8] = {0x00,0x00,0x00,0x0f,0x00,0x1b,0x00,0x1f};
    // *(&qword_140004040 + 4) = 0x 3C 00 72 00 05 00 1E;
    char x5[8] = {0x00,0x3c,0x00,0x72,0x00,0x05,0x00,0x1e};
    // *(&qword_140004040 + 5) = 0x4 00 36 00 1F 00 62;
    char x6[8] = {0x00,0x04,0x00,0x36,0x00,0x1f,0x00,0x62};
    // *(&qword_140004040 + 6) = 0x3F 00 32 00 2E 00 1F;
    char x7[8] = {0x00,0x3f,0x00,0x32,0x00,0x2e,0x00,0x1f};
    // *(&qword_140004040 + 7) = 0  i64;
    char x8[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    char xall[64] = {0};
    for(int i=0;i<64;i++)
    { 
      int ii=i/8;
      if(ii==0)
      {
        xall[i] = x1[7-i%8];
      }
      else if (ii==1)
      {
        xall[i] = x2[7-i%8];
      }
      else if (ii==2)
      {
        xall[i] = x3[7-i%8];
      }
      else if (ii==3)
      {
        xall[i] = x4[7-i%8];
      }
      else if (ii==4)
      {
        xall[i] = x5[7-i%8];
      }
      else if (ii==5)
      {
        xall[i] = x6[7-i%8];
      }
      else if (ii==6)
      {
        xall[i] = x7[7-i%8];
      }
      else if (ii==7)
      {
        xall[i] = x8[7-i%8];
      }
    }
    // for ( j = 0; j < 28; ++j )
    // {
    //   if ( (Str[j % 4] ^ Str[j + 4]) != *((char *)&qword_140004040 + 2 * j) )
    //     goto LABEL_11;
    // }
    cout << "now output x1 for test" << endl;
    for(int i=0; i<8;i++)
      printf("%02x",x1[i]);
    cout << endl;
    cout << "now output xall for test" << endl;
    for(int i=0; i<64;i++)
      printf("i:%d:%02x\n",i,xall[i]);
    cout << endl << endl;
    

    cout << "now begin test" << endl;
    for(int i=0;i<28;i++)
    {
      char temp=0;
      for(temp=0;temp<=255;temp++)
      {
        cout << "begin try :" << temp << endl;
        if ( (ans[i % 4] ^ temp) != xall[2*i])
          continue;
        else
        {
          ans[i+4] = temp;
          break;
        }
        cout << "tried temp :" << temp << endl;
      }
      cout << "tried i : " << i << endl;
    }

    cout << "ans:"  << endl;
    for(int i=0; i<32;i++)
      cout << ans[i];
    cout << endl;


    return 0;
}


//str 81 84 69 77
//ans QTEM5D91sCjyBGNvNOJMOQ7q3KsINzwr