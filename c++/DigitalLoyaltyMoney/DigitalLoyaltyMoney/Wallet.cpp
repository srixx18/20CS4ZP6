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

void Wallet::randomMGenerator()
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        randomKeyGenerator(&mKey[i], &mValues[i]);
    }
}

void Wallet::randomKeyGenerator(primeNumberExpo_t *key, int *value)
{
    for (int i = 0; i < PNUM_SIZE; i++) {
        //TODO:generated random value could be set to wider range
        *key[i].push_back(rand() % 2);
    }
    *value = primeMultiplication(key);
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
    for( int i = 0; i < SECURITY_LOOP; i = i + 1 ) {
        for (int j = 0; j < PNUM_SIZE; j = j + 1)
        {
            //TODO:generated random value could be set to wider range
            mKeyDecryptionVector[i].push_back(rand() % 2);
            mnKeyDecryptionVector[i].push_back(rand() % 2);
        }
        for (int j = 0; j < PNUM_SIZE; j = j + 1)
        {
            mEncryptedKey[i].at(j) = mKey[i].at(j) + mKeyDecryptionVector.at(j);
            mnEncryptedKey[i].at(j) = mnKey[i].at(j) + mnKeyDecryptionVector.at(j);
        }
    }
}

void Wallet::decryptSelectedKeys()
{
    for( int i = 0; i < SECURITY_LOOP; i = i + 1 ) {
        if(randomSelectedKey[i] == DECRYPT_M){
            decryptedSelectedKey[i] = mKeyDecryptionVector[i];
        }
        else if(randomSelectedKey[i] == DECRYPT_MN){
            decryptedSelectedKey[i] = mnKeyDecryptionVector[i];
        }
    }
}

void Wallet::addCoin(int id)
{
    //TODO:broadcast admin to update coin info (id,value)!!
    primeNumberExpo_t key;
    int value;
    randomKeyGenerator(&key, &value);
    coinTable.insert(std::pair<int,int>(id, value));
    secretTable.insert(std::pair<int,primeNumberExpo_t>(id, key));
}

void Wallet::removeCoin(int id)
{
    coinTable.erase(id);
    secretTable.erase(id)
}

std::map<int, int> Wallet::displayCoin()
{
    return coinTable;
}

bool Wallet::verify(int id)
{
    if(coinTable.count(id) == 0){ return false; }

    randomMGenerator();
    computeMN(coinTable.at(id), secretTable.at(id));
    encryptedSecret();
    randomSelection();
    decryptSelectedKeys(a);
    return verifyDecryptedKey()
}

void Wallet::transferCoin(int id, Wallet receiver)
{
    //TODO: report error if we cannot verify
    if (verify(id)){
        removeCoin(id);
        receiver.addCoin(id);
    }
}
