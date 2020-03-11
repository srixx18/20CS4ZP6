#include "Bignum.h"
/* *******************************************************************************
 *                        class Vector
 ********************************************************************************* */
class Vector {
public:
    long* vector;
    long vlen;
    int* _primes;

    Vector() {
        vector = 0;
        vlen = 0;
        _primes = 0;
    }//end Vector

    Vector(long vlen, ...) {
        long i;
        va_list args;
        vector = new long[vlen];
        this->vlen = vlen;

        va_start(args, vlen);
        for (i = 0; i < vlen; i++)
            vector[i] = va_arg(args, long);
        va_end(args);
        _primes = 0;
    }//end Vector

    Vector& operator=(Vector& x) {
        long i;
        if (x.vlen == 0)
            return *this;
        if (vlen < x.vlen) {
            if (vector) delete[] vector;
            vlen = x.vlen;
            vector = new long[vlen];
        }
        for (i = 0; i < vlen; i++)
            vector[i] = x.vector[i];
        return *this;
    }//end operator=

    Vector& operator+(Vector& x) {
        long i;
        if (x.vlen == 0)
            return *this;
        Vector* v = new Vector(x.vlen);
        for (i = 0; i < vlen; i++)
            v->vector[i] = vector[i] + x.vector[i];
        return *v;
    }//end operator+

    bool operator==(Vector& x) {
        long i;
        if (x.vlen != vlen) return false;
        for (i = 0; i < vlen; i++)
            if (vector[i] != x.vector[i]) return false;
        return true;
    }//end operator==

    bool operator!=(Vector& x) {
        long i;
        if (x.vlen != vlen) return true;
        for (i = 0; i < vlen; i++)
            if (vector[i] != x.vector[i]) return true;
        return false;
    }

    long& operator[](long i) { return vector[i]; }

    ~Vector() { if (vector) delete[] vector; }

    void primes(long from) {
        long n = vlen + from - 1;
        long i = 3, count, c;
        long j = 0;
        _primes = new int[vlen];

        for (count = 2; count <= n; ) {
            for (c = 2; c <= i - 1; c++)
                if (i % c == 0) break;
            if (c == i) {
                if (count >= from)
                    _primes[j++] = i;
                count++;
            }
            i++;
        }
    }//end primes

    void random(bool delta = false) {
        long i, j;
        static bool first = true;
        if (first) {
            srand((unsigned int)time(0));
            first = false;
        }
        if (delta) {
            for (i = 0; i < vlen; i++) {
                if (vector[i] == 0)
                    vector[i] = rand() % bound_for_factorization;
                else {
                    j = rand() % 2;
                    if (j == 0)
                        vector[i] = vector[i] - (rand() % vector[i]);
                    else
                        vector[i] = vector[i] + (rand() % vector[i]);
                }
            }
        }
        else {
            for (i = 0; i < vlen; i++)
                vector[i] = rand() % bound_for_factorization;
        }
    }//end random

    void random_delta() {
        random(true);
    }//end random_delta

    void show(char term = ' ') {
        for (long i = 0; i < vlen; i++)
            printf("%lu ", vector[i]);
        if (term == '\n')
            putchar('\n');
    }//end show


    void prod(BigNum& r, long from = starting_prime) {
        if (_primes == 0) primes(from);

        BigNum t, u;
        r = 1;
        for (long i = 0; i < vlen; i++) {
            if (vector[i] == 0) continue;
            if (vector[i] == 1)
                u = _primes[i];
            else {
                t = _primes[i];
                BigNum::exp(vector[i], t, u);
            }
            r.MultTo(u);
        }
    }//end prod

    void encode(long key) {
        for (long i = 0; i < vlen; i++)
            vector[i] = vector[i] ^ key;
    }//end encode

    void decode(long key) {
        for (long i = 0; i < vlen; i++)
            vector[i] = vector[i] ^ key;
    }//end decode
};//end class Vector
