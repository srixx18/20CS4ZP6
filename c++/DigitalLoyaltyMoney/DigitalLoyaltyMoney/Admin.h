#ifndef ADMIN_H
#define ADMIN_H

#include <cstdlib>
#include <map>
#include <vector>

class Admin
{

public:
    //variables
    std::map<int, int> coinTable;

    //functions
    std::map<int, int> displayCoin();
    void addCoin(int id, int val);
    void replaceCoinVal(int replacedID, int replacedValue);
};

#endif //!ADMIN_H