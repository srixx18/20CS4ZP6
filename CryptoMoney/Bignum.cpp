#include "pch.h"
#include "Bignum.h"
/* *******************************************************************************
 *                        class Bignum
 ********************************************************************************* */

BigNum& BigNum::operator=(unsigned long x) {
    Util util;
        if (body) delete[] body;
        if (x == 0) {
            body = 0;
            len = 0;
            return *this;
        }
        uchar y[4];
        unsigned long* z = (unsigned long*)&y;
        *z = x;
        uchar t[4];
        if (util.small_endian) {
            t[0] = y[0];
            t[1] = y[1];
            t[2] = y[2];
            t[3] = y[3];
        }
        else {
            t[0] = y[3];
            t[1] = y[2];
            t[2] = y[1];
            t[3] = y[0];
        }
        if (t[3] == '\0') {
            if (t[2] == '\0') {
                if (t[1] == '\0') {
                    body = new uchar[1];
                    len = 1;
                    util.swap(t[0]);
                    body[0] = t[0];
                    return *this;
                }
                else {
                    body = new uchar[2];
                    len = 2;
                    util.swap(t[0]);
                    util.swap(t[1]);
                    body[0] = t[0];
                    body[1] = t[1];
                    return *this;
                }
            }
            else {
                body = new uchar[3];
                len = 3;
                util.swap(t[0]);
                util.swap(t[1]);
                util.swap(t[2]);
                body[0] = t[0];
                body[1] = t[1];
                body[2] = t[2];
                return *this;
            }
        }
        else {
            body = new uchar[4];
            len = 4;
            util.swap(t[0]);
            util.swap(t[1]);
            util.swap(t[2]);
            util.swap(t[3]);
            body[0] = t[0];
            body[1] = t[1];
            body[2] = t[2];
            body[3] = t[3];
            return *this;
        }
    }//end oparetor=

    BigNum& BigNum::operator=(BigNum& x) {
        if (body) delete[] body;
        body = new uchar[x.len];
        for (long i = 0; i < x.len; i++)
            body[i] = x.body[i];
        len = x.len;
        return *this;
    }//end operator=

    BigNum& BigNum::operator=(char* x) {
        Util util;
        long j;
        if (body) delete[] body;
        long i = strlen(x);
        if (i == 1 && x[0] == '0') {
            len = 0;
            body = 0;
            return *this;
        }
        if ((i % 2) == 0) {
            // even length
            len = i / 2;
            body = new uchar[len];
            for (i--, j = 0; i > 0; i = i - 2, j++)
                util.s2hex(body[j], x[i], x[i - 1]);
            return *this;
        }
        else {
            // odd length
            len = i / 2 + 1;
            body = new uchar[len];
            for (i--, j = 0; i > 0; i = i - 2, j++)
                util.s2hex(body[j], x[i], x[i - 1]);
            util.s2hex(body[j + 1], x[0], '0');
            return *this;
        }
    }//end operator=

    bool BigNum::operator==(BigNum& x) {
        if (len != x.len) return false;
        for (long i = 0; i < len; i++)
            if (body[i] != x.body[i]) return false;
        return true;
    }//end operator==

    bool BigNum::operator!=(BigNum& x) {
        if (len != x.len) return true;
        for (long i = 0; i < len; i++)
            if (body[i] != x.body[i]) return true;
        return false;
    }//end operator!=

    

    void BigNum::blank() {
        if (body) {
            long i;
            for (i = 0; i < len; i++) body[i] = '\0';
        }
    }//end blank

    uchar BigNum::getraw(long i, long range_check) {
        Util util;
        if (i < 0) {
            printf("getraw index error");
            util.GETCHAR();
            exit(0);
        }
        if (i >= 2 * len) {
            if (range_check) {
                printf("getraw index error");
                util.GETCHAR();
                exit(0);
            }
            else {
                return '\0';
            }
        }
        long j = i / 2;
        if ((i % 2) == 0)
            return util.get_left(body[j]);
        else
            return util.get_right(body[j]);
    }//end getraw

    uchar BigNum::get(long i, long range_check) {
        Util util;
        if (i < 0) {
            printf("get index error");
            util.GETCHAR();
            exit(0);
        }
        if (i >= 2 * len) {
            if (range_check) {
                printf("get index error");
                util.GETCHAR();
                exit(0);
            }
            else
                return '\0';
        }
        long j = 2 * len - 1 - i;
        if ((j % 2) == 0) {
            // return left half byte of body[j]
            return util.get_left(body[j / 2]);
        }
        else {
            // return right half byte of body[j]
            return util.get_right(body[j / 2]);
        }
    }//end get

    void BigNum::setraw(long i, uchar a) {
        Util util;
        if (i < 0 || i >= 2 * len) {
            printf("settraw index error");
            util.GETCHAR();
            exit(0);
        }
        long j = i / 2;
        if ((i % 2) == 0)
            // set left half byte of body[j]
            util.set_left(body[j], a);
        else
            // set right half byte of body[j]
            util.set_right(body[j], a);
    }//end setraw

    void BigNum::set(long i, uchar a) {
        Util util;
        if (i < 0 || i >= 2 * len) {
            printf("set index error");
            util.GETCHAR();
            exit(0);
        }
        long j = i / 2;
        if ((i % 2) == 0)
            // set left half byte of body[j]
            util.set_left(body[j], a);
        else
            // set right half byte of body[j]
            util.set_right(body[j], a);
    }//end set

    void BigNum::showraw(char term) {
        Util util;
        if (len == 0) {
            printf("0%c", term);
            return;
        }
        for (long i = 0; i < len; i++)
            util.showbyte(body[i]);
        putchar(term);
    }//end showraw

    void BigNum::show(char term) {
        Util util;
        if (len == 0) {
            printf("0%c", term);
            return;
        }
        for (long i = len - 1; i >= 0; i--)
            util.showrbyte(body[i]);
        putchar(term);
    }//end show

    void BigNum::minishow(char term) {
        Util util;
        if (len == 0) {
            printf("0%c", term);
            return;
        }
        long i, j = 0;
        for (i = len - 1, j = 0; i >= 0 && j < 16; i--, j += 2)
            util.showrbyte(body[i]);
        printf("...%c", term);
    }//end minishow

    // this = this + x
    void BigNum::AddTo(BigNum& x) {
        BigNum y;
        y = *this;
        Add(x, y, *this);
    }//end AddTo

    // this = this * x
    void BigNum::MultTo(BigNum& x) {
        BigNum y;
        y = *this;
        Mult(x, y, *this);
    }//end MultTo



