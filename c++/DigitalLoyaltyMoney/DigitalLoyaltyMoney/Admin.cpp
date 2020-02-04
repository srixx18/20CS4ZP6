#include <cstdlib>;
#include <map>;
#include <vector>;
#include "Admin.h";

std::map<int, int> Admin::displayCoin()
{
    return std::map<int, int>();
}

void Admin::randomSelection()
{
    for( int i = 0; i < 10; i = i + 1 ) {
        randomSelectedKey[i] = rand() % 2;
    }
}

bool Admin::verifyDecryptedKey(Wallet * wallet)
{
    for( int i = 0; i < 10; i = i + 1 ) {
        if(randomSelectKey[i] == DECRYPT_M) {
            if((wallet.mEncryptedKey - wallet.decryptedSelectedKey) != primeFactorization(wallet.mValues[i])) {
                return false;
            }
        }
        else if(randomSelectKey[i] == DECRYPT_MN) {
            if((wallet.mnEncryptedKey - wallet.decryptedSelectedKey) != primeFactorization(wallet.mnValues[i])) {
                return false;
            }
        }
    }
    return true;
}

void Admin::replaceCoin(int replacedID, int replacedValue)
{
    coinTable.at(replacedId) = replacedValue;
}

int * primeFactorization(int number)
{
    std::list<int> factors;

    for( int i = 2; i <= number/i; i++){
        while(number % i == 0){
            number = number/i;
            factors.push_back(i);
        }
    }

    if (number > 1) {
        factors.push_back(number);
    }
    return *factors;
}