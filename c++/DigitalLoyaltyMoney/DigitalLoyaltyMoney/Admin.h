#include <cstdlib>;
#include <map>;
#include <vector>;
#include "Wallet.h";

class Admin
{
    //default constructor
    Admin()
    {
        randomSelection();
    }

    //constant declaration
    const int DECRYPT_M = 0;
    const int DECRYPT_MN = 1;

public:
    //variables
    std::map<int, int> coinTable;
    int randomSelectedKey[10];

    //functions
    std::map<int, int> displayCoin();
    void randomSelection();
    bool verifyDecryptedKey(Wallet wallet);
    void replaceCoin(int replacedID, int replacedValue);
};