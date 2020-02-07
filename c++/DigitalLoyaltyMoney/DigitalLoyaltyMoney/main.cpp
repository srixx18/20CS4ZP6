// main.cpp : This file is used for testing.
#include "Service.h"

int main()
{
    //Output any message to the console
    std::cout << "---------start-----------\n";

    Service sev;
    Admin admin;
    Wallet w1;
    Wallet w2;

    sev.addNewCoin(admin, w1, 7);
    std::cout << sev.verify(admin, w1, 7);
    sev.transferCoin(admin, w1, w2, 7);

    std::cout << "\n---------end-----------\n";
}
