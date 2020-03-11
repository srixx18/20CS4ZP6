#include "Util.h"

class BigNum {
public:
    uchar* body;
    long len;
    BigNum() { body = 0; len = 0; }  // set it to 0
    BigNum& operator=(unsigned long x);
    BigNum& operator=(BigNum& x);
    BigNum& operator=(char* x);
    bool operator==(BigNum& x);
    bool operator!=(BigNum& x);
    ~BigNum() { if (body) delete[] body; };
    void blank();
    uchar getraw(long i, long range_check = 1);
    uchar get(long i, long range_check = 1);
    void setraw(long i, uchar a);
    void set(long i, uchar a);
    void showraw(char term = '\0');
    void show(char term = '\0');
    void minishow(char term = '\0');
    // z = x + y
    static void Add(BigNum& x, BigNum& y, BigNum& z) {
        z.len = x.len;
        if (z.len < y.len)
            z.len = y.len;
        z.len++;
        long m = 2 * z.len;
        if (z.body)
            delete[] z.body;
        z.body = new uchar[m];
        long i;
        uchar a, b, c, carry = '\0';
        for (i = 0; i < m; i++) {
            a = x.getraw(i, 0);
            b = y.getraw(i, 0);
            c = a + b + carry;
            if (c >= 16) {
                carry = 1;
                c -= 16;
            }
            else {
                carry = 0;
            }
            z.setraw(i, c);
        }
        while (z.body[z.len - 1] == '\0') z.len--;
    }//end Add
    void AddTo(BigNum& x);
    // z = x * y
    static void Mult(BigNum& x, BigNum& y, BigNum& z) {
        Util util;
        long m = x.len + y.len + 1;
        if (z.len < m) {
            if (z.body) delete[] z.body;
            z.body = new uchar[m];
            z.len = m;
        }
        z.blank();
        BigNum h;
        if (h.len < m) {
            if (h.body) delete[] h.body;
            h.body = new uchar[m];
            h.len = m;
        }

        long i, j, start, k;
        uchar a, b, res, carry = '\0';
        long len1 = 2 * x.len;
        long len2 = 2 * y.len;
        for (start = i = 0; i < len1; i++, start++) {
            a = x.getraw(i, 0);
            h.blank();
            for (j = 0, k = start; j < len2; j++, k++) {
                b = y.getraw(j, 0);
                util.mult(a, b, res, carry);
                h.setraw(k, res);
            }
            if (carry) {
                h.setraw(k, carry);
                carry = 0;
            }
            z.AddTo(h);
        }
    }//end MUlt
    void MultTo(BigNum& x);
    // y = x^n
    static void exp(long n, BigNum& x, BigNum& y) {
        Util util;
        if (n < 0) {
            printf("exp error");
            util.GETCHAR();
            exit(0);
        }
        if (n == 0) {
            y = 1;
            return;
        }
        long i;
        y = x;
        for (i = 1; i < n; i++)
            y.MultTo(x);
    }//end exp
};