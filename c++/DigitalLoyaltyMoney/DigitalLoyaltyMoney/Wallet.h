#include <cstdlib>;
#include <map>;
#include <vector>;

class Wallet
{
    //default constructor
    Wallet()
    {

    }
    
    //type declaration
    typedef std::vector<int> primeNumberExpo_t;

private:
    //variables
    std::map<int, primeNumberExpo_t> secretTable;
    primeNumberExpo_t mKey[10];
    primeNumberExpo_t mnKey[10];
    primeNumberExpo_t mKeyDecryptionVector[10];
    primeNumberExpo_t mnKeyDecryptionVector[10];

    //functions
    void randomMgenerator();
    void computeMN(int n);
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