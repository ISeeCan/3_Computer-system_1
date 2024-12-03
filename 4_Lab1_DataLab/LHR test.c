#include<stdio.h>
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/*basis logical equation*/
	return (~(x&y))&(~((~x)&(~y)));
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
	int x=73|73<<9;
  	return x|x<<18;
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
	int y=x<<16>>16;
  	return !(y^x);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number, and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {//6/5
	int y=x+1;
  	return !(y+y+!y);
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
int fitsBits(int x, int n) {//6/5
	int m=33+(~n);
	int y=x<<m>>m;
 	return !(y^x);
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {//5/4
	int y=~(!n);
  	return y<<31>>(n+y);
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0(0101, anyOddBit(0x7) = 1(0111
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
	int y=170;
	y|=y<<8;
	y|=y<<16;
    return !!(y&x);
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
int byteSwap(int x, int n, int m) {//16/10
	int nmove=n<<3;
	int mmove=m<<3;
	int nulln=255<<nmove;
	int nullm=255<<mmove;
	int nx=(x>>nmove<<mmove)&nullm;
	int mx=(x>>mmove<<nmove)&nulln;
    return (x&(~nullm)&(~nulln))|nx|mx;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {//4/3
	int sign=x>>31;
  	return (sign^x)+(sign&1);
}
/* (~(x&sign))+1+(x&(~sign))
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {//8/5
	int m=x>>n;
    return m+((x>>31)&(!!((m<<n)^x))); 
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but they are to be interpreted as the bit-level representations of single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  	unsigned r=uf^0x80000000 ;
  	unsigned t=r&uf;
	if (t > 0x7F800000 &&t<=0x7fffffff)
	r = uf;
	return r;
} 
/*  unsigned float_neg(unsigned uf) {
 	unsigned a=(uf>>23)&0xff;
	if(a==0xff&&(uf&0x7fffff)>0);
	return uf;
	else
 	return uf^sign;
}

 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	int f=~x+1;
	return ((f|x)>>31)+1;
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
	int f=(~0);
  	return (f<<lowbit)&(f+(1<<highbit<<1));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
	int f=~x;//8000000000
	return (((f|y)&((x^y)|(y+f+1)))>>31)&1;//(0x7fffffff,0x80000000)
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {//9/5
  return (x>>n)&(~((!!n)<<31)>>(n+(~0)));
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x7FFFFFFF (saturate to TMax)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3int satMul2(int x) {//6(0x30,0x80,0x60,0xf0
	int sign=1<<31;
	int y =x<<1;
	int b=y>>31;
	int six=x&sign;
  	return x+x;
}
 */
int satMul2(int x) {
    int x2 = x << 1;
    int overflow = (x2^ x) >> 31;
    int tmin = 1 << 31;
    int x2neg = x2 >> 31;
    return (~overflow & x2) |(overflow & (tmin ^ (x2neg)));	
}

/*y|b&six|six;
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
 	int t1 = x ;
    int t2 = y ;
    int t = t1 ^ t2;
    int cf = (x + ~y + 1) ;
    return ((t & (t1 ^ cf))>>31) + 1;
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
  return 2;
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
  return 2;
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
  return 0;
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
  return 2;
}
int main(){
    printf("%d\n",bitXor(7,5));//*
    printf("%o\n",thirdBits());
    printf("%d\n",fitsShort(32768));
    printf("%x\n",isTmax(2147483647));
    printf("%d\n",fitsBits(-4,3));
    printf("%x\n",upperBits(31));
    printf("%x\n",anyOddBit(5));
    printf("%x\n",byteSwap(0xDEADBEEF, 0, 2));
    printf("%d\n",absVal(-19876));
    printf("%d\n",divpwr2(-2147483647,4));
    printf("%x,%x\n",78.9,float_neg(78.9));
    printf("%d\n",logicalNeg(-214748364));
    printf("%x\n",bitMask(31,3));
    printf("%x\n",isGreater(0x80000000,0x7fffffff));
    printf("%x\n",logicalShift(0x87654321,0));
    printf("%x\n",satMul2(0x60000000));
    printf("%x\n",satMul2(0xf0000000));
    printf("%x\n",satMul2(0x80000000));
    printf("%x\n",satMul2(0x30000000));
    printf("%d\n",subOK(0x80000000,0x70000000));
  
	return 0; 
}
