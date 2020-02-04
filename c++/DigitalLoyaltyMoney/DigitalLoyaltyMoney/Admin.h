#ifndef ADMIN_H
#define ADMIN_H

#include <cstdlib>;
#include <map>;
#include <vector>;

class Admin
{
    //default constructor
    Admin()
    {
    }

public:
    //variables
    std::map<int, int> coinTable;

    //functions
    std::map<int, int> displayCoin();
    void replaceCoin(int replacedID, int replacedValue);
};

#endif //!ADMIN_H