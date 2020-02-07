#include <cstdlib>
#include <map>
#include <vector>
#include "Admin.h"

std::map<int, int> Admin::displayCoin()
{
    return coinTable;
}

void Admin::addCoin(int id, int val)
{
    coinTable.insert(std::pair<int, int>(id, val));
}

void Admin::replaceCoinVal(int replacedID, int replacedValue)
{
    coinTable.at(replacedID) = replacedValue;
}

