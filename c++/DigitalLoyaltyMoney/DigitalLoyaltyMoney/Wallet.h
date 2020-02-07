#ifndef WALLET_H
#define WALLET_H

#include <cstdlib>
#include <map>
#include <vector>

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

class Wallet
{
private:
    //variables
    int randomSelectedKey[SECURITY_LOOP];
    std::map<int, primeNumberExpo_t> secretTable;
    primeNumberExpo_t mKey[SECURITY_LOOP];
    primeNumberExpo_t mnKey[SECURITY_LOOP];
    primeNumberExpo_t mKeyDecryptionVector[SECURITY_LOOP];
    primeNumberExpo_t mnKeyDecryptionVector[SECURITY_LOOP];

    //functions
    void randomSelection();
    bool verifyDecryptedKey();
    int primeMultiplication(std::vector<int> key, std::vector<int> decryptKey);
    int primeMultiplication(std::vector<int> key);
    void randomMGenerator();
    keyValuePair randomKeyGenerator();
    //TODO: type of n should be mpz_class
    void computeMN(int n, primeNumberExpo_t nKey);
    void encryptedSecret();
    void decryptSelectedKeys();

public:
    //variables
    //TODO: should be a map of <int,mpz_class>
    std::map<int, int> coinTable;
    //TODO: mValues and mnValues have type mpz_class
    int mValues[SECURITY_LOOP];
    int mnValues[SECURITY_LOOP];
    primeNumberExpo_t mEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP];

    //functions
    //TODO: should return <int,mpz_class>
    std::map<int, int> displayCoin();
    bool verify(int id);
    void addCoin(int id);
    void removeCoin(int id);
};

#endif //!ELEMENT_H