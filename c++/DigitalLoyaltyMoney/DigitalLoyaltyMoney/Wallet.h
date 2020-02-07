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

class Wallet
{

    //type declaration
    typedef std::vector<int> primeNumberExpo_t;

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
    void randomKeyGenerator(primeNumberExpo_t *key, int *value);
    void computeMN(int n, primeNumberExpo_t nKey);
    void encryptedSecret();
    void decryptSelectedKeys();

public:
    //variables
    std::map<int, int> coinTable;
    int mValues[SECURITY_LOOP];
    int mnValues[SECURITY_LOOP];
    primeNumberExpo_t mEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP];
    primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP];

    //functions
    std::map<int, int> displayCoin();
    bool verify(int id);
    void transferCoin(int id, Wallet receiver);
    void addCoin(int id);
    void removeCoin(int id);
};

#endif //!ELEMENT_H