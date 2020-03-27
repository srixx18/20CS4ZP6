#include "pch.h"
#include "main.h"
#include <sstream>
#include <iostream>

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
    fflush(stdout);
    return w1;
}

DLL_EXPORT char* show_mint(Wallet* w, bool mini)
{
    std::stringbuf sbuf(std::ios::out);
    auto oldbuf = std::cout.rdbuf(std::addressof(sbuf));
    if (mini)
    {
        w->mint->minishow();
    }
    else
    {
        w->mint->show();
    }
    std::cout.rdbuf(oldbuf);
    std::string output = sbuf.str();
    char* cstr = new char[output.length() + 1];
    strcpy_s(cstr, output.length() + 1, output.c_str());
    return cstr;
}

DLL_EXPORT char* show_wallet(Wallet* w, bool mini)
{
    std::stringbuf sbuf(std::ios::out);
    auto oldbuf = std::cout.rdbuf(std::addressof(sbuf));
    if (mini)
    {
        w->minishow();
    }
    else
    {
        w->show();
    }
    std::cout.rdbuf(oldbuf);
    std::string output = sbuf.str();
    char* cstr = new char[output.length() + 1];
    strcpy_s(cstr, output.length() + 1, output.c_str());
    return cstr;
}

DLL_EXPORT char* verify(Wallet* w, int id)
{
    std::stringbuf sbuf(std::ios::out);
    auto oldbuf = std::cout.rdbuf(std::addressof(sbuf));

    w->request_verify_ownership(id);
    
    std::cout.rdbuf(oldbuf);
    std::string output = sbuf.str();
    char* cstr = new char[output.length() + 1];
    strcpy_s(cstr, output.length() + 1, output.c_str());
    return cstr;
}

DLL_EXPORT char* transfer(Wallet* sender, Wallet* recv)
{
    std::stringbuf sbuf(std::ios::out);
    auto oldbuf = std::cout.rdbuf(std::addressof(sbuf));

    sender->transfer_coin(recv);
    
    std::cout.rdbuf(oldbuf);
    std::string output = sbuf.str();
    char* cstr = new char[output.length() + 1];
    strcpy_s(cstr, output.length() + 1, output.c_str());
    return cstr;
}

DLL_EXPORT char* transfer_fake(Wallet* sender, Wallet* recv)
{
    std::stringbuf sbuf(std::ios::out);
    auto oldbuf = std::cout.rdbuf(std::addressof(sbuf));

    sender->transfer_fake_coin(recv);
    
    std::cout.rdbuf(oldbuf);
    std::string output = sbuf.str();
    char* cstr = new char[output.length() + 1];
    strcpy_s(cstr, output.length() + 1, output.c_str());
    return cstr;
}
