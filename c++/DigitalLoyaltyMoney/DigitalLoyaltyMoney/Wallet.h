#ifndef WALLET_H
#define WALLET_H

#include "Constant.h"

class Wallet
{
public:
    //variables
    std::map<int, primeNumberExpo_t> secretTable;
    primeNumberExpo_t mKey[SECURITY_LOOP];
    primeNumberExpo_t mnKey[SECURITY_LOOP];
    primeNumberExpo_t mKeyDecryptionVector[SECURITY_LOOP];
    primeNumberExpo_t mnKeyDecryptionVector[SECURITY_LOOP];
    //TODO: should be a map of <int,mpz_class>
    std::map<int, int> coinTable;
    //TODO: mValues and mnValues have type mpz_class
    int mValues[SECURITY_LOOP];
    int mnValues[SECURITY_LOOP];
    primeNumberExpo_t mEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP];

    //functions
    int primeMultiplication(std::vector<int> key);
    void randomMGenerator();
    keyValuePair randomKeyGenerator();
    //TODO: type of n should be mpz_class
    void computeMN(int id);
    void encryptedSecret();
    void decryptSelectedKeys(int randomSelectedKey[SECURITY_LOOP]);
    //TODO: should return <int,mpz_class>
    std::map<int, int> displayCoin();
    void addCoin(int id);
    void removeCoin(int id);
};

#endif //!ELEMENT_H