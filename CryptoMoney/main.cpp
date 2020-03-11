#include "main.h"

Mint* Wallet::mint = new Mint();
long Mint::last_id = 0;
long Wallet::last_id = 0;
char Message::message[100];

int main() {
    Wallet* w1 = new Wallet();
    Wallet* w2 = new Wallet();

    w1->minishow();
    //getchar();
    w2->minishow();
    //getchar();
    w1->mint->minishow();
    //getchar();

    w1->transfer_fake_coin(w2);
    printf("\n\n********************\n\n");
    w1->transfer_coin(w2);
    printf("\n\n********************\n\n");
    w2->request_verify_ownership(w2->coins->root->coinid);

    w1->minishow();
    //getchar();
    w2->minishow();
    //getchar();
    w2->mint->minishow();
    //getchar();
    w2->request_verify_ownership(0);
    printf("\n\ndone -- press <enter> to terminate");
    //getchar();
    return 0;
}//end main


DLL_EXPORT Wallet* init_wallet()
{
    Wallet* w1 = new Wallet();
    return w1;
}

DLL_EXPORT void show_mint(Wallet* w, bool mini)
{
    if (mini)
    {
        w->mint->minishow();
    }
    else
    {
        w->mint->show();
    }
}

DLL_EXPORT void show_wallet(Wallet* w, bool mini)
{
    if (mini)
    {
        w->minishow();
    }
    else
    {
        w->show();
    }
}

DLL_EXPORT void verify(Wallet* w, int id)
{
    w->request_verify_ownership(id);
}

DLL_EXPORT void transfer(Wallet* sender, Wallet* recv)
{
    sender->transfer_coin(recv);
}

DLL_EXPORT void transfer_fake(Wallet* sender, Wallet* recv)
{
    sender->transfer_fake_coin(recv);
}
