#line 154 "bits.c"
int bitXor(int x, int y) {
    int c=  x & y;
    int not_c=  ~c;
    int not_x;int not_y;
    int res;

    x = x & not_c;
    not_x = ~x;

    y = y & not_c;
    not_y = ~y;

    res = not_x & not_y;

    return ~res;
}
#line 177
int tmin(void) {
#line 182
  return 1 << 31;
}
#line 192
int isTmax(int x) {
  int y=  x + 1;
  return !((~y) ^ x) & !!~x;
}
#line 203
int allOddBits(int x) {
  int y=  0xAA;
  y = y ^( 0xAA << 8);
  y = y ^( 0xAA << 16);
  y = y ^( 0xAA << 24);
  return !((y&x)^y);
}
#line 217
int negate(int x) {
  return (~x)+1;
}
#line 230
int isAsciiDigit(int x) {

  int lower=  x + ~0x30 + 1;
  int lowerNonNegative=  !(lower >> 31);


  int upper=  0x39 + ~x + 1;
  int upperNonNegative=  !(upper >> 31);


  return lowerNonNegative & upperNonNegative;
}
#line 249
int conditional(int x, int y, int z) {
  int a=  !!x;
  int b;
  b = ~a + 1;
  return (b&y) |(( ~b)&z);
}
#line 262
int isLessOrEqual(int x, int y) {
  int a=  ~x + 1;
  int b;
  b = a + y;
  return !(b >> 31);
}
#line 277
int logicalNeg(int x) {
  return 2;
}
#line 292
int howManyBits(int x) {
  return 0;
}
#line 307
unsigned float_twice(unsigned uf) {
  return 2;
}
#line 319
unsigned float_i2f(int x) {
  return 2;
}
#line 334
int float_f2i(unsigned uf) {
  return 2;
}
