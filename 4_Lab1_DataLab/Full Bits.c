/* 
 * CS:APP Data Lab
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will submit on ics.men.ci
 * 
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:  ////////////////////////////////////////////////
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:///////////////////////////////////////////////
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES////////////////////////////

For the problems that require you to implement floating-point operations,
the coding rules are less strict. You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according to the coding rules.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */





















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 使用 SSH 连接到远程主机                                      ////////////////////////////////////////////////////
// 打开终端（在命令提示符或终端中）。                                           /////////////////////////////////////
// 使用以下命令连接到远程主机：                                                            /////////////////////////
// ssh username@hostname
// 其中 username 是您在远程主机上的用户名，hostname 是远程主机的 IP 地址或域名。

// 使用 SCP 传输文件
// 将文件从本地系统复制到远程主机：
// scp local_file username@hostname:remote_directory
// 其中 local_file 是本地文件的路径，username 是远程主机上的用户名，hostname 是远程主机的 IP 地址或域名，remote_directory 是文件应该存储的远程目录。
// 将文件从远程主机复制到本地系统：
// scp username@hostname:remote_file local_directory
// 其中 username 是远程主机上的用户名，hostname 是远程主机的 IP 地址或域名，remote_file 是远程文件的路径，local_directory 是文件应该存储的本地目录。

// u2022201253  Otherthings.isc.123
// ics.ruc.rvalue.moe
                                                
// 2.使用 btest 进行测试  (translated by gpt)
// 该目录中的 Makefile 使用额外的代码编译您的 bits.c 版本，以创建一个名为 btest 的程序（或测试套件）。
// 要编译和运行 btest 程序，请执行以下命令：
// unix> make btest
// unix> ./btest [可选的命令行参数]

// 每次更改 bits.c 程序时，您都需要重新编译 btest。当从一个平台移动到另一个平台时，您应该摆脱旧版本的 btest 并生成一个新版本。使用以下命令：
// unix> make clean
// unix> make btest
// Btest 通过在每个函数上运行数百万个测试用例来检测代码的正确性。它测试整数谜题的各个方面，如 Tmin 和零，以及浮点谜题的零、无穷大以及非规格化和规格化数字之间的边界。当 btest 检测到函数中的错误时，它会打印出失败的测试、错误的结果和预期的结果，然后终止该函数的测试。

// 以下是 btest 的命令行选项：
// unix> ./btest -h
// 用法: ./btest [-hg] [-r <n>] [-f <name> [-1|-2|-3 <val>]*] [-T <time limit>]
// -1 <val>  指定第一个函数参数
// -2 <val>  指定第二个函数参数
// -3 <val>  指定第三个函数参数
// -f <name> 仅测试指定的函数
// -g        以不包含错误消息的自动分级格式输出
// -h        打印此消息
// -r <n>    为所有问题提供均匀权重 n
// -T <lim>  将超时限制设置为 lim

//compliance with the coding guidelines:      ./dlc bits.c
//if there are no problems with your code.    ./dlc -e bits.c

//scp "C:\Users\w1098\Documents\Code\Local\c_cpp\3_Computer system\4_Lab1\datalab-handout\bits.c" iseecan@192.168.186.129:Documents/3_ComputerSystem/4_Lab1/datalab-handout

//一键测试：./driver.pl
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>                                              /////////////////////////////////////////////////
                                                                /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}

/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int h249 = 73 | (1 << 9);
  return (0x49 << 24) | (h249 << 12) | h249;
}

/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 * 32767~-32768
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  int xhi16 = x >> 16;
  return ((~xhi16+1) + (~xhi16));
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  x+=1;
  return !(x+x)&!!(x);;
  //      tmax+tmax = -2
}

/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  return 2;
}

/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  return 2;
}

/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    return 2;
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    return 2;
}

/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  return 2;
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    return 2;
}

/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return 2;
}

/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  return 2;
}

/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  return 2;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  return 2;
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x7FFFFFFF (saturate to TMax)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  return 2;
}

/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  return 2;
}

/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x) {
    int m2=x>>2;
    int sign=x>>31;
    int last2=x&3;
    return x+~m2+!(last2&(~sign)); 
}

/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  return 2;
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned int ans = 0;
  unsigned int onebitmask = 1;
  unsigned s=0,e=0,f=0;
  unsigned int maxwhere=31;
  if(x == 0)
    return x;
  if(x < 0)
  {
    printf("x<0\n");
    s = (1 << 31);
    x = ~x;
  }
    printf("finalx: %x\n s:%x\n",x,s);
        //现在x符号位都是0了
  while(maxwhere > 0)
  {   //e.g.: 0x01   第一位为1，需要右移0位
    if(x >> (maxwhere - 1))
      break;
    maxwhere--;
  } //注意，此时的maxwhere表示的是从左边数第一个1在第几位，但是第i位表示的是2^（i-1）
    printf("where higbest 1:%d\n",maxwhere);
  e = 126+maxwhere; //(126=127-1)
    printf("now e is:%x\n",e); 
  unsigned int xx = x << (32 - maxwhere);   //把1扔到左边
  unsigned int makenofirst1 = ~(1 << 31);//0x7fffffff
  f = makenofirst1 & xx;       //第一位无了
  f = f >> 8;                 //扔到应有的位置
    printf("nofront ought f:%x\n",f);
  unsigned int whetherround = x & 0xff; //舍入
  unsigned int ifroundis1 = (whetherround > 128 || ((whetherround == 128) && (f & 1)));//判断
    printf("ifroundis1:%d\n",ifroundis1);
  e += ifroundis1;
    printf("rounded e is:%x\n",e);
  e = e << 23;
    printf("final e is:%x\n",e); 
  if(s) //是负数
    f = ~f <<9 >> 9; 
      printf("final f:%x\n",f);  
  // if(f >> 23) //就差这么一点  非规格化
  // {
  //   f &= (makenofirst1>>8); //删掉多出来的
  // }

  ans = s|e|f;
  return ans;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    unsigned int ALLS = x >> 31;         //右移出s
    unsigned int N1P0 = !(!ALLS);
    unsigned int PisPNisOp = x ^ ALLS;   //正数不变负数按位取反
    unsigned int Zero0El1 = !(!PisPNisOp);

    printf("first PisPNisOp:%x\n",PisPNisOp);

    int bit_16,bit_8,bit_4,bit_2,bit_1;   //有为1
    bit_16=!(!(PisPNisOp >> 16)) << 4;  
    PisPNisOp=PisPNisOp >> bit_16;  //有就看前面没有看后面
    bit_8=!(!(PisPNisOp >> 8)) << 3;
    PisPNisOp=PisPNisOp >> bit_8;
    bit_4=!(!(PisPNisOp >> 4)) << 2;
    PisPNisOp=PisPNisOp >> bit_4;
    bit_2=!(!(PisPNisOp >> 2)) << 1;
    PisPNisOp=PisPNisOp >> bit_2;
    bit_1=!(!(PisPNisOp >> 1));
    
    printf("x:%x alls %x, PisPNisOp %x, bit16 %x bit8 %x bit4 %x bit2 %x bit1 %x\n",x,ALLS,PisPNisOp,bit_16,bit_8,bit_4,bit_2,bit_1);
    printf("zero0el1:%x \n",Zero0El1);
    return (bit_16 | bit_8 | bit_4 | bit_2 | bit_1) + 1 + (Zero0El1 & 0x1);
}

/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  unsigned int s = uf & 0x80000000;
  unsigned int m = uf & 0x7f800000;
  unsigned int f = uf & 0x007fffff;
  unsigned int mf = uf & 0x7fffffff;
  unsigned int roundoff = !((uf & 3) ^ 3);
  if(m == 0x7f800000)       //无穷大或压根不是数
    return uf;
  else                      //好消息：这是个数；坏消息：这是个数
  {
    if(m > 0x00800000)
      m -= 0x00800000;        //好消息：还可以规格化
    else if (m == 0x00800000)
    {
        return s | (roundoff + ((uf & mf)>>1));
    }
    else 
    {
        unsigned int ff = f >> 1;         //没有好消息
        //printf("f:%x ff:%x",f,ff);
        return s|(ff + roundoff);
    }
  }
    
  return s | m | f;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{   printf("0-5:\n");
    printf("%x\n",bitXor(1,2));            //0                  
    printf("%x\n",thirdBits(/*void*/));
    printf("%x\n",fitsShort(0xffffffff));
    printf("%x\n",isTmax(0x7fffffff));
    // printf("%x\n\n",fitsBits(,));

    // printf("%x\n",upperBits());            //5
    // printf("%x\n",anyOddBit());
    // printf("%x\n",byteSwap(,,));
    // printf("%x\n",absVal());
    // printf("%x\n",divpwr2(,));

    // printf("10-15:\n");
    // printf("%x\n",float_neg());            //10
    // printf("%x\n",logicalNeg());
    // printf("%x\n",bitMask(,));
    // printf("%x\n",isGreater(,));
    // printf("%x\n\n",logicalShift(,));

    // printf("%x\n",satMul2());            //15
    // printf("%x\n",subOK(,));
     printf("%x\n",trueThreeFourths(0x7fffffff));
    // printf("%x\n",isPower2());
     //printf("int2float:%x\n",float_i2f(0x80800000));

    // printf("20-25:\n");
     //printf("howmanybits:%x\n",howManyBits(0x80000000));            //20
     //printf("%x\n",float_half(0x1));


    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //25
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //30
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //35
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //40
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);


    // printf("%x\n",);            //45
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //50
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);

    // printf("%x\n",);            //55
    // printf("%x\n",);
    // printf("%x\n",);
    // printf("%x\n",);
    
    return 0;
}