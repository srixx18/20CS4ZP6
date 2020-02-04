#include <cstdlib>;
#include <map>;
#include <vector>;
#include "Admin.h";

std::map<int, int> Admin::displayCoin()
{
    return coinTable;
}

void Admin::replaceCoin(int replacedID, int replacedValue)
{
    coinTable.at(replacedID) = replacedValue;
}

