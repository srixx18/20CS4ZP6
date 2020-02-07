#ifndef ADMIN_H
#define ADMIN_H

#include "Constant.h"

class Admin
{
public:
    //variables
    std::map<int, int> coinTable;
    int randomSelectedKey[SECURITY_LOOP];

    //functions
    std::map<int, int> Admin::displayCoin();
    void randomSelection();
    bool verifyDecryptedKey(int mValues[SECURITY_LOOP], primeNumberExpo_t mEncryptedKey[SECURITY_LOOP], 
                            primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP],
                            int mnValues[SECURITY_LOOP], primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP]);
    int primeMultiplication(std::vector<int> key, std::vector<int> decryptKey);
    std::map<int, int> displayCoin();
    void addCoin(int id, int val);
    void replaceCoinVal(int replacedID, int replacedValue);
};

#endif //!ADMIN_H