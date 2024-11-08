#line 160 "bits.c"
int bitXor(int x, int y) {
    int oneIfBothOne=  x & y;
    int zeroIfBothOne=  ~oneIfBothOne;
    int oneIfContainsOne=  ~((~x) &( ~y));
    int result=  zeroIfBothOne & oneIfContainsOne;
    return result;
}
#line 173
int tmin(void) {
    int result=(  ~1 + 1) << 31;
    return result;
}
#line 185
int isTmax(int x) {


    int reversed=  !!(~x);


    return !(x + x + 1 + reversed);
}
#line 200
int allOddBits(int x) {
    int slice=  170;int oddOneEvenZero=170;
    oddOneEvenZero =( oddOneEvenZero << 8) + slice;
    oddOneEvenZero =( oddOneEvenZero << 8) + slice;
    oddOneEvenZero =( oddOneEvenZero << 8) + slice;
    return !(~(oddOneEvenZero & x) + oddOneEvenZero + 1);


}
#line 217
int negate(int x) {
    return (~x) + 1;
}
#line 230
int isAsciiDigit(int x) {
#line 239
    int diffSum=(  x << 1) +( ~105 + 1);
    return !(x >> 6 |( ~diffSum + 10) >> 31 |( diffSum + 9) >> 31);
}
#line 249
int conditional(int x, int y, int z) {
#line 262
    return ((~(!!x) + 1) & y) |(( ~(~(!!x) + 1)) & z);
}
#line 271
int isLessOrEqual(int x, int y) {
#line 279
    int xSign=(  x >> 31) & 1;
    int ySign=(  y >> 31) & 1;
    int xNegativeYNonNegativeFlag=  xSign & !ySign;
#line 285
    int diff=  x + ~y + 1;
    int diffSign=(  diff >> 31) & 1;
    int sameSignFlag=  !(xSign ^ ySign);
    int diffNonPositveFlag=  sameSignFlag &( ~(!!diff) | diffSign);


    return (xNegativeYNonNegativeFlag | diffNonPositveFlag);
}
#line 302
int logicalNeg(int x) {
#line 307
    int smeard=  x;
    smeard = smeard | smeard >> 16;
    smeard = smeard | smeard >> 8;
    smeard = smeard | smeard >> 4;
    smeard = smeard | smeard >> 2;
    smeard = smeard | smeard >> 1;
    return (~smeard & 1);
}
#line 327
int howManyBits(int x) {


    int y;int result;int mask16;int mask8;int mask4;int mask2;int mask1;int bitnum;

    mask1 = 0x2;
    mask2 = 0xC;
    mask4 = 0xF0;
    mask8 = 0xFF << 8;
    mask16 =( mask8 | 0xFF) << 16;

    result = 1;
    y = x ^( x >> 31);


    bitnum =( !!(y & mask16)) << 4;
    result += bitnum;
    y = y >> bitnum;

    bitnum =( !!(y & mask8)) << 3;
    result += bitnum;
    y = y >> bitnum;

    bitnum =( !!(y & mask4)) << 2;
    result += bitnum;
    y = y >> bitnum;

    bitnum =( !!(y & mask2)) << 1;
    result += bitnum;
    y = y >> bitnum;

    bitnum = !!(y & mask1);
    result += bitnum;
    y = y >> bitnum;

    return result +( y & 1);
}
#line 376
unsigned float_twice(unsigned uf) {
#line 388
    unsigned expMask=  0xFF;
    unsigned exp=  expMask &( uf >> 23);
    unsigned Mtail=(  uf << 9) >> 9;

    unsigned expAllZeroFlag=  !exp;
    unsigned expAllOneFlag=  !(exp ^ expMask);
    unsigned MtailAllZeroFlag=  !(Mtail);

    unsigned signBitExpMask=  0xff800000;
    unsigned signBitMask=  0x80000000;

    unsigned oneExp=  0x000800000;
#line 405
    if (expAllOneFlag) {


    } else if (expAllZeroFlag) {
        if (MtailAllZeroFlag) {

        } else {

            unsigned onlyKeepSignBit=  signBitMask & uf;
            uf = onlyKeepSignBit |( uf << 1);
        }
    } else {
        if (!((exp + 1) ^ 0xff)) {


            uf = uf + oneExp;


            uf = uf & signBitExpMask;
        } else {
            uf = uf + oneExp;
        }
    }
    return uf;
}
#line 440
unsigned float_i2f(int xi) {
    unsigned xu;unsigned signBit;unsigned temp;unsigned signBitMask;unsigned frac;unsigned bias;unsigned exp;unsigned firstOneMask;unsigned 
        xuWithOriginalFirstOneSetToZero;
#line 441
    unsigned 
                                         roundBitIdx;
#line 441
    unsigned 
                                                      roundBit;
#line 441
    unsigned 

        stickyBitSource;
#line 441
    unsigned 

                         guardBit;
    int firstOneIdx;

    signBitMask = 0x80000000;
    signBit = exp = frac = 0;
    xu = xi;


    signBit = xu & signBitMask;
    xu = signBit ? -xu : xu;
#line 456
    temp = xu;
    firstOneIdx = 31;
    for (; (firstOneIdx >= 0) && !(temp & signBitMask); ) {
        firstOneIdx = firstOneIdx - 1;
        temp = temp << 1;
    }


    bias = 0x7f;
    firstOneMask = 1 << firstOneIdx;
    xuWithOriginalFirstOneSetToZero = xu - firstOneMask;

    if (firstOneIdx <= 23) {
#line 472
        frac = xuWithOriginalFirstOneSetToZero <<( 23 - firstOneIdx);
    } else {
#line 478
        roundBitIdx = firstOneIdx - 24;
        roundBit =( xu >> roundBitIdx) & 1;
#line 483
        frac = xuWithOriginalFirstOneSetToZero >>( firstOneIdx - 23);

        if (roundBit) {

            stickyBitSource =( xu <<( 32 - roundBitIdx));
            if (stickyBitSource) {

                frac = frac + 1;
            } else {


                guardBit =( xu >>( roundBitIdx + 1)) & 1;
                if (guardBit) {
                    frac = frac + 1;
                }
            }
        }
    }
    exp = firstOneIdx + bias;
    return xu ? signBit +( exp << 23) + frac : 0;
}
#line 516
int float_f2i(unsigned uf) {
    unsigned res;unsigned expMask;unsigned exp;unsigned fracMask;unsigned frac;unsigned outOfRange;unsigned M;unsigned bias;unsigned temp;unsigned 
        fractionalFirstBitMask;
#line 517
    unsigned 
                                signBitMask;
#line 517
    unsigned 
                                             signBit;
    int firstOneInFractionalIdx;int E;


    if (!(uf << 1)) {
        return 0;
    }


    expMask = 0x7f800000;
    exp =( expMask & uf) >> 23;

    fracMask = 0x008ffff;
    frac = fracMask & uf;

    outOfRange = 0x80000000u;

    bias = 0x7f;

    if (exp == expMask) {
        res = outOfRange;
    } else if (!exp) {
        return 0;
    } else {
        E = exp - bias;

        if (E < 0) {

            return 0;
        } else if (E > 30) {

            return outOfRange;
        }

        temp = uf;
        firstOneInFractionalIdx = 22;
        fractionalFirstBitMask = 0x00400000;
        for (; (firstOneInFractionalIdx >= 0) && !(temp & fractionalFirstBitMask); ) {
            firstOneInFractionalIdx -= 1;
            temp = temp << 1;
        }


        M = 0x00800000 + frac;
        if (E > 23) {
            res = M <<( E - 23);
        } else {
            res = M >>( 23 - E);
        }
    }


    signBitMask = 0x80000000;
    signBit = signBitMask & uf;
    if (signBit) {
        res = -res;
    }
#line 609
    return res;
}
