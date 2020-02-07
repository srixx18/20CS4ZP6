#ifndef SERVICE_H
#define SERVICE_H

#include "Wallet.h"
#include "Admin.h"

class Service
{
public:
    //functions
    bool verify(Admin admin, Wallet wallet, int id);
    void addNewCoin(Admin &admin, Wallet &wallet, int id);
    void transferCoin(Admin &admin, Wallet &sender, Wallet &receiver, int id);
};

#endif //!SERVICE_H
