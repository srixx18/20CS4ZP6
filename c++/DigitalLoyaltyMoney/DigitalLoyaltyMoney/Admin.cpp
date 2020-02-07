#include "Admin.h"

std::map<int, int> Admin::displayCoin()
{
    return coinTable;
}

void Admin::addCoin(int id, int val)
{
    coinTable.insert(std::pair<int, int>(id, val));
}

void Admin::replaceCoinVal(int replacedID, int replacedValue)
{
    coinTable.at(replacedID) = replacedValue;
}

//TODO: output should be mpz_class
int Admin::primeMultiplication(std::vector<int> key, std::vector<int> decryptKey)
{
    //TODO: generate an array of PNUM_SIZE prime numbers
    int tempPrimeNumList[PNUM_SIZE] = { 1,2,3,5,7,9,11 };

    //TODO: type of val should be mpz_class
    int val = 1;
    for (int i = 0; i < PNUM_SIZE; i++)
    {
        //TODO: use GMP lib to add value into val
        val = val * pow(tempPrimeNumList[i], key[i] - decryptKey[i]);
    }
    return val;
}

void Admin::randomSelection()
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        randomSelectedKey[i] = rand() % 2;
    }
}

bool Admin::verifyDecryptedKey(int mValues[SECURITY_LOOP], primeNumberExpo_t mEncryptedKey[SECURITY_LOOP], 
                               primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP],
                               int mnValues[SECURITY_LOOP], primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP])
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        if (randomSelectedKey[i] == DECRYPT_M) {
            if ((mValues[i]) != primeMultiplication(mEncryptedKey[i], decryptedSelectedKey[i])) {
                return false;
            }
        }
        else if (randomSelectedKey[i] == DECRYPT_MN) {
            if ((mnValues[i]) != primeMultiplication(mnEncryptedKey[i], decryptedSelectedKey[i])) {
                return false;
            }
        }
    }
    return true;
}