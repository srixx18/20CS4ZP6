#ifndef WALLET_H
#define WALLET_H

#include <cstdlib>;
#include <map>;
#include <vector>;

class Wallet
{
    //default constructor
    Wallet()
    {

    }

    //constant declaration
    const int DECRYPT_M = 0;
    const int DECRYPT_MN = 1;

    //type declaration
    typedef std::vector<int> primeNumberExpo_t;

private:
    //variables
    int randomSelectedKey[10];
    std::map<int, primeNumberExpo_t> secretTable;
    primeNumberExpo_t mKey[10];
    primeNumberExpo_t mnKey[10];
    primeNumberExpo_t mKeyDecryptionVector[10];
    primeNumberExpo_t mnKeyDecryptionVector[10];

    //functions
    void randomSelection();
    bool verifyDecryptedKey();
    int primeMultiplication(std::vector<int> key, std::vector<int> decryptKey);
    int primeMultiplication(std::vector<int> key);
    void randomMgenerator();
    void computeMN(int n, primeNumberExpo_t nKey);
    void encryptedSecret();
    void decryptSelectedKeys();
    void addCoin(int id, int value, primeNumberExpo_t secret);
    void removeCoin(int id);

public:
    //variables
    std::map<int, int> coinTable;
    int mValues[10];
    int mnValues[10];
    primeNumberExpo_t mEncryptedKey[10];
    primeNumberExpo_t mnEncryptedKey[10];
    primeNumberExpo_t decryptedSelectedKey[10];

    //functions
    std::map<int, int> displayCoin();
    bool verify(int id);
    void transferCoin(int id, int value, Wallet receiver);
};

#endif //!ELEMENT_H