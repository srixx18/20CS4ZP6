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
        randomSelectedKey[i] = rand();
    }
    return rand();
}

bool Admin::verifyDecryptedKey(Wallet wallet)
{
    for( int i = 0; i < 10; i = i + 1 ) {
        if(randomSelectKey[i] == DECRYPT_M) {
            if((wallet.mEncryptedKey - wallet.decryptedSelectedKey) != /*prime number factorization of wallet.mValues[i]*/) {
                return false;
            }
        }
        else if(randomSelectKey[i] == DECRYPT_MN) {
            if((wallet.mnEncryptedKey - wallet.decryptedSelectedKey) != /*prime number factorization of wallet.mnValues[i]*/) {
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