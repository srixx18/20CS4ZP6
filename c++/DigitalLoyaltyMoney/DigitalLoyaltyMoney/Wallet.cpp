#include "Wallet.h"

Wallet::Wallet()
{
}

//TODO: output should be mpz_class
int Wallet::primeMultiplication(std::vector<int> key)
{
    //TODO: given n is the size of the key, generate a list n of prime numbers
    int tempPrimeNumList[PNUM_SIZE] = { 1,2,3,5,7,9,11 };
    //TODO: type of val should be mpz_class
    int val = 1;
    for (int i = 0; i < PNUM_SIZE; i++)
    {
        //TODO: use GMP lib to add value into val
        val = val * pow(tempPrimeNumList[i], key[i]);
    }
    return val;
}

void Wallet::randomMGenerator()
{
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        keyValuePair temp = randomKeyGenerator();
        mKey[i] = temp.key;
        mValues[i] = temp.value;
    }
}

keyValuePair Wallet::randomKeyGenerator()
{
    keyValuePair result;
    for (int i = 0; i < PNUM_SIZE; i++) {
        //TODO:generated random value could be set to wider range
        result.key.push_back(rand() % 2);
    }
    result.value = primeMultiplication(result.key);
    return result;
}

//TODO: input should be mpz_class n
void Wallet::computeMN(int id)
{
    int n = coinTable.at(id);
    primeNumberExpo_t nKey = secretTable.at(id);
    for (int i = 0; i < SECURITY_LOOP; i = i + 1) {
        //TODO: use GMP lib to perform multiplication
        mnValues[i] = mValues[i] * n;
        for (int j = 0; j < PNUM_SIZE; j = j + 1)
        {
            mnKey[i].push_back(mKey[i].at(j) + nKey.at(j));
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
            mEncryptedKey[i].push_back(mKey[i].at(j) + mKeyDecryptionVector[i].at(j));
            mnEncryptedKey[i].push_back(mnKey[i].at(j) + mnKeyDecryptionVector[i].at(j));
        }
    }
}

void Wallet::decryptSelectedKeys(int randomSelectedKey[SECURITY_LOOP])
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
    primeNumberExpo_t key;
    int value;
    keyValuePair res = randomKeyGenerator();
    coinTable.insert(std::pair<int,int>(id, res.value));
    secretTable.insert(std::pair<int,primeNumberExpo_t>(id, res.key));
}

void Wallet::removeCoin(int id)
{
    coinTable.erase(id);
    secretTable.erase(id);
}

std::map<int, int> Wallet::displayCoin()
{
    return coinTable;
}
