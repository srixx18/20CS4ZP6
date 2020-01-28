#include <cstdlib>;
#include <map>;
#include <vector>;
#include "Wallet.h";
#include <iostream>;

void Wallet::randomMgenerator()
{
    Admin a;
    for( int i = 0; i < 10; i = i + 1 ) {
        mValues[i] = rand(/*TODO: randomly big number*/);
        mKey[i] = a.primeFactorization(mValues[i]);
    }
}

void Wallet::computeMN(int n)
{
    for( int i = 0; i < 10; i = i + 1 ) {
        mnValues[i] = mValues[i] * n;
        mnKey[i] = mKey[i] + secretTable.at(n);
    }
}

void Wallet::encryptedSecret()
{
    for( int i = 0; i < 10; i = i + 1 ) {
        mKeyDecryptionVector[i] = rand(/*generated int array*/);
        mEncyrptedKey[i] = mKey[i] + mKeyDecryptionVector[i];
        mnKeyDecryptionVector[i] = rand(/*generated int array*/);
        mnEncryptedKey[i] = mnKey[i] + mnKeyDecryptionVector[i];
    }
}

void Wallet::decryptSelectedKeys()
{
    for( int i = 0; i < 10; i = i + 1 ) {
        Admin admin;
        if(admin.randomeSelectedKey[i] == admin.DECRYPT_M){
            decryptedSelectedKey[i] = mKeyDecryptionVector[i];
        }
        else if(admin.randomeSelectedKey[i] == admin.DECRYPT_MN){
            decryptedSelectedKey[i] = mnKeyDecryptionVector[i];
        }
    }
}

void Wallet::addCoin(int id, int value, primeNumberExpo_t secret)
{
    coinTable.insert( std::pair<int,int>(id, value) );
    secretTable.insert( std::pair<int,primeNumberExpo_t>(id, secret) );
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
    randomMgenerate();
    computeMN(coinTable.at(id));
    encryptSecret();
    Admin a;
    a.randomSelection();
    decryptSelectedKeys(a);
    return a.verifyDecriptedKey(/*this wallet*/)
}

void Wallet::transferCoin(int id, int value, Wallet receiver)
{
    if (!verify(id);){
        cout << id << " is not found.";
    }
    else {
        Admin a;
        a.replaceCoin(id, value);
        removeCoin(id);
        receiver.addCoin(id, value, secret);
    }
}
