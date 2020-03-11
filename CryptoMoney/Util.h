#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cstdarg>

typedef unsigned char uchar;
const long number_of_initial_coins = 10;
const long size_of_factorization = 10;
const long bound_for_factorization = 10;
const long starting_prime = 1000;
const long number_of_rounds = 5;


class Util
{
public:
    //#define _use_getchar
    #ifdef _use_getchar
    #define GETCHAR() getchar()
    #else
    void GETCHAR();
    #endif
    short __i = 1;
    uchar* __x = (uchar*)&__i;
    bool small_endian = ((__x[0] == 1) ? (true) : (false));
    bool big_endian = ((__x[0] == 1) ? (false) : (true));
    uchar get_left(uchar x);
    void set_left(uchar& x, uchar a);
    uchar get_right(uchar x);
    void set_right(uchar& x, uchar a);
    void swap(uchar& x);
    uchar retswap(uchar x);
    void showbyte(uchar x, char term = ' ');
    void showrbyte(uchar x, char term = ' ');
    void s2hex(uchar& x, char a, char b);
    void mult(uchar x, uchar y, uchar& res, uchar& carry);
};