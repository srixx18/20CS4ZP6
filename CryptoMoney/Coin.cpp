#include "pch.h"
#include "Vector.cpp"
#include <iostream>
/* *******************************************************************************
 *                        class Coin
 ********************************************************************************** */
class Coin {
public:
    long coinid;
    BigNum* secret;

    Coin(long coinid, BigNum* secret) {
        this->coinid = coinid;
        this->secret = new BigNum();
        *(this->secret) = *secret;
    }//end Coin

    Coin(long id, BigNum& secret) {
        this->coinid = coinid;
        this->secret = new BigNum();
        *(this->secret) = secret;
    }//end Coin

    ~Coin() { if (secret) delete secret; }

    void show(bool kind = true) {
        std::cout << coinid;
        //printf("%d,", coinid);
        if (kind)
            secret->show('\n');
        else
            secret->minishow('\n');
    }//end show
};// end class Coin


class ZK_INFO {
public:
    BigNum m[number_of_rounds];
    Vector left[number_of_rounds];
    Vector right[number_of_rounds];

    ZK_INFO(BigNum& N, Vector& v, long* left_keys, long* right_keys) {
        long i;
        // v is factorization of N
        BigNum T;
        for (i = 0; i < number_of_rounds; i++) {
            left[i] = v;
            left[i].random_delta();
            left[i].prod(m[i], starting_prime);
            //left[i] is factorization of m[i]
            right[i] = left[i] + v;
            //right[i] = left[i]+v is factorization of m[i]*N
        }
        // encode the vectors
        for (i = 0; i < number_of_rounds; i++) {
            left[i].encode(left_keys[i]);
            right[i].encode(right_keys[i]);
        }
    }//end ZK_INFO

    void show() {
        for (long i = 0; i < number_of_rounds; i++) {
            printf("round %d:\n", i);
            printf("    "); m[i].show('\n');
            printf("    "); left[i].show('\n');
            printf("    "); right[i].show('\n');
        }
    }//end show

    void show_decode(long* left_keys, long* right_keys) {
        Vector v;
        for (long i = 0; i < number_of_rounds; i++) {
            printf("round %d:\n", i);
            printf("    "); m[i].show('\n');
            v = left[i];
            v.decode(left_keys[i]);
            printf("    "); v.show('\n');
            v = right[i];
            v.decode(right_keys[i]);
            printf("    "); v.show('\n');
        }
    }
};


/* *******************************************************************************
 *                        class CoinMnode
 ********************************************************************************* */
class CoinMnode {
public:
    CoinMnode* prev, * next;
    Coin* coin;
    long walletid;

    CoinMnode(Coin* coin, long walletid) {
        this->coin = coin;
        this->walletid = walletid;
        prev = next = 0;
    }//end CoinMnode

    ~CoinMnode() { if (coin) delete coin; }

    void show(bool kind = true) {
        std::cout << "coin :";
        //printf("coin: ");
        coin->show(kind);
    }//end show
};//end class CoinMnode



/* *******************************************************************************
 *                        class CoinMlist
 ********************************************************************************** */
class CoinMlist {
public:
    CoinMnode* root;
    long size;

    CoinMlist() { root = 0; size = 0; }

    ~CoinMlist() {
        CoinMnode* q, * p = root;
        while (p != 0) {
            q = p->next;
            delete p;
            p = q;
        }
    }//end ~CoinMlist

    void insert(CoinMnode* n) {
        if (root == 0) {
            root = n;
            size = 1;
            return;
        }
        n->next = root;
        root = n;
        size++;
        return;
    }//end insert

    void insert(long coinid, BigNum* secret, long walletid) {
        Coin* c = new Coin(coinid, secret);
        CoinMnode* n = new CoinMnode(c, walletid);
        insert(n);
    }//end insert

    long walleid_count(long walletid) {
        long count = 0;
        if (root == 0) return count;
        CoinMnode* p;
        for (p = root; p != 0; p = p->next)
            if (p->walletid == walletid) count++;
        return count;
    }//end walletid_count

    void show(bool kind = true) {
        if (root == 0)
            std::cout << "empty" << std::endl;
            //printf("empty\n");
        else
            for (CoinMnode* p = root; p != 0; p = p->next)
                p->show(kind);
    }//end show
};//end class CoinMlist

/* *******************************************************************************
 *                        class CoinWnode
 ********************************************************************************** */
class CoinWnode {
public:
    CoinWnode* prev, * next;
    long coinid;
    BigNum* secret;
    Vector* vector;
    CoinWnode(long coinid, BigNum* secret, Vector* vector) {
        this->coinid = coinid;
        this->secret = new BigNum();
        *(this->secret) = *secret;
        this->vector = new Vector(10);
        *(this->vector) = *vector;
        prev = next = 0;
    }//end CoinWnode

    ~CoinWnode() { delete secret; delete vector; }

    void show(bool kind = true) {
        std::cout << "coin: " << coinid << std::endl;
        //printf("coin: %u,", coinid);
        if (kind) {
            std::cout << std::endl;
            putchar('\n');
            secret->show('\n');
        }
        else
            secret->minishow('\n');
        if (kind) {
            std::cout << "   " << std::endl;
            //printf("   ");
            vector->show('\n');
        }
    }//end show
};//end class CoinWnode

/* *******************************************************************************
 *                        class CoinWlist
 ********************************************************************************** */
class CoinWlist {
public:
    CoinWnode* root;
    long size;

    CoinWlist() { root = 0; size = 0; }

    ~CoinWlist() {
        CoinWnode* q, * p = root;
        while (p != 0) {
            q = p->next;
            delete p;
            p = q;
        }
    }//end ~CoinWlist

    void insert(long coinid, BigNum* secret, Vector* vector) {
        CoinWnode* n = new CoinWnode(coinid, secret, vector);
        if (root == 0) {
            root = n;
            size = 1;
            return;
        }
        n->next = root;
        root = n;
        size++;
        return;
    }//end insert

    void show(bool kind = true) {
        if (root == 0)
            std::cout << "empty" << std::endl;
            //printf("empty\n");
        else {
            for (CoinWnode* p = root; p != 0; p = p->next)
                p->show(kind);
        }
    }//end show
};//end class CoinWlist