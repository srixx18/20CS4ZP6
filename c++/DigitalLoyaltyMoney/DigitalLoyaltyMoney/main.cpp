// main.cpp : This file is used for testing.
#include <iostream>
#include <cstdlib>
#include <map>
#include <list>
#include <vector>
#include <cmath>
#include "Wallet.h"
#include "Admin.h"

int main()
{
    //Output any message to the console
    std::cout << "---------start-----------\n";
    Wallet w1, w2;
    Admin a;

    //add a new coin into the system
    int coinID = 1;
    w1.addCoin(coinID);
    a.addCoin(coinID, w1.coinTable.at(coinID));

    //transfer coin
    w1.removeCoin(coinID);
    w2.addCoin(coinID);
    a.replaceCoinVal(coinID, w2.coinTable.at(coinID));

    std::cout << "\n---------end-----------\n";
}
