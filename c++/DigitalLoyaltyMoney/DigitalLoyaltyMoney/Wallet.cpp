#include <cstdlib>
#include <map>
#include <vector>
#include <cmath>
#include "Wallet.h"

//TODO: output should be mpz_class
int Wallet::primeMultiplication(std::vector<int> key, std::vector<int> decryptKey)
{
    //TODO: generate an array of PNUM_SIZE prime numbers
    int tempPrimeNumList[PNUM_SIZE] = { 1,2,3,5,7,9,11 };

    //TODO: type of val should be mpz_class
    int val = 0;
    for (int i = 0; i < PNUM_SIZE; i++)
    {
        //TODO: use GMP lib to add value into val
        val = val + pow(tempPrimeNumList[i], key[i] - decryptKey[i]);
    }
    return val;
}

//TODO: output should be mpz_class
int Wallet::primeMultiplication(std::vector<int> key)
{
    //TODO: given n is the size of the key, generate a list n of prime numbers
    int tempPrimeNumList[PNUM_SIZE] = { 1,2,3,5,7,9,11 };
    //TODO: type of val should be mpz_class
    int val = 0;
    for (int i = 0; i < PNUM_SIZE; i++)
    {
        //TODO: use GMP lib to add value into val
        val = val + pow(tempPrimeNumList[i], key[i]);
    }
    return val;
}

bool Wallet::verifyDecryptedKey()
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

void Wallet::randomSelection()
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        randomSelectedKey[i] = rand() % 2;
    }
}

void Wallet::randomMgenerator()
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        //TODO:mKey[i] should have more random length other than 7
        for (int i = 0; i < PNUM_SIZE; i++) {
            //TODO:generated random value could be set to wider range
            mKey[i].push_back(rand() % 2);
        }
        mValues[i] = primeMultiplication(mKey[i]);
    }
}

//TODO: input should be mpz_class n
void Wallet::computeMN(int n, primeNumberExpo_t nKey)
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        //TODO: use GMP lib to perform multiplication
        mnValues[i] = mValues[i] * n;
        for (int j = 0; j < PNUM_SIZE; j = j + 1)
        {
            mnKey[i].at(j) = mKey[i].at(j) + nKey.at(j);
        }
    }
}

void Wallet::encryptedSecret()
{
}

void Wallet::decryptSelectedKeys()
{
}

void Wallet::addCoin(int id, int value, primeNumberExpo_t secret)
{
}

void Wallet::removeCoin(int id)
{
}

std::map<int, int> Wallet::displayCoin()
{
    return std::map<int, int>();
}

bool Wallet::verify(int id)
{
    return false;
}

void Wallet::transferCoin(int id, int value, Wallet receiver)
{
}
