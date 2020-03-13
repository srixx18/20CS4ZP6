#include "pch.h"
#include "Util.h"

uchar Util::get_left(uchar x) {
    // get left halfbyte of x
    return x >> 4;
}//end get_left


void Util::set_left(uchar& x, uchar a) {
    // set left half byte of x
    // first remember the right half
    unsigned y = x & 0x0F;
    x = a;
    x = x << 4;
    x = x & 0xF0;
    x = x + y;
}//end set_left

uchar Util::get_right(uchar x) {
    // get right half byte of x
    return x & 0x0F;
}//end get_right


void Util::set_right(uchar& x, uchar a) {
    // set right half byte of x
    x = x & 0xF0;
    x = x + a;
}//end set_right

void Util::swap(uchar& x) {
    // swap left and right halves
    // remember the left half
    uchar y = get_left(x);
    x = get_right(x);
    x = x << 4;
    x = y + x;
}//end swap

uchar Util::retswap(uchar x) {
    uchar y = x;
    swap(y);
    return y;
}//end retswap


void Util::showbyte(uchar x, char term) {
    uchar z = get_left(x);
    if (z < 10)
        printf("%c", '0' + z);
    else
        printf("%c", 'A' + z - 10);
    z = get_right(x);
    if (z < 10)
        printf("%c", '0' + z);
    else
        printf("%c", 'A' + z - 10);
    if (term == '\n')
        printf("%c", term);
}//end showbyte
void Util::GETCHAR() { putchar('\n'); }

void Util::showrbyte(uchar x, char term) {
    uchar z = get_right(x);
    if (z < 10)
        printf("%c", '0' + z);
    else
        printf("%c", 'A' + z - 10);
    z = get_left(x);
    if (z < 10)
        printf("%c", '0' + z);
    else
        printf("%c", 'A' + z - 10);
    if (term == '\n')
        printf("%c", term);
}//end showrbyte


void Util::s2hex(uchar& x, char a, char b) {
    char a1, b1;
    if (a >= '0' && a <= '9')
        a1 = a - '0';
    else
        a1 = 10 + a - 'A';
    if (b >= '0' && b <= '9')
        b1 = b - '0';
    else
        b1 = 10 + b - 'A';
    x = a1;
    x = x << 4;
    x = x + b1;
}//end s2hex

void Util::mult(uchar x, uchar y, uchar& res, uchar& carry) {
    uchar t = x * y + carry;
    res = get_right(t);
    carry = get_left(t);
}//end mult