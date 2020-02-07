#pragma once
#include <iostream>
#include <cstdlib>
#include <map>
#include <list>
#include <vector>
#include <cmath>

//constant declaration
const int DECRYPT_M = 0;
const int DECRYPT_MN = 1;
const int PNUM_SIZE = 7;
const int SECURITY_LOOP = 10;

//type declaration
typedef std::vector<int> primeNumberExpo_t;

//struct declaration
struct keyValuePair {
    primeNumberExpo_t key;
    //TODO: type of value should be mpz_class
    int value;
};