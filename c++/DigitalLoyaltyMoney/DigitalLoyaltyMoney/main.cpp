// main.cpp : This file is used for testing.
#pragma once
#include <iostream>
#include <cstdlib>;
#include <map>;
#include <list>;
#include <vector>;
#include <cmath>;
#include "Wallet.h"

int main()
{
    //Output any message to the console
    std::cout << "---------start-----------";

    for (int i = 0; i < 10; i = i + 1) {
        std::cout << rand() % 5;
    }

    std::cout << "---------end-----------";
}
