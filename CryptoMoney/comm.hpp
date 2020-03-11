#ifndef _comm_hpp
#define _comm_hpp

class Message {
public:
    ////////////////////////////////////////////////////////////////////////////////
// x codes
////////////////////////////////////////////////////////////////////////////////
    typedef enum xcode { x_none = 0, x_start = 11, x_hup, x_message, x_ok } Xcode;
    //#define x_none     0
    //#define x_start    11
    //#define x_hup      12
    //#define x_message  13
    //#define x_ok       14

    ////////////////////////////////////////////////////////////////////////////////
// y codes
////////////////////////////////////////////////////////////////////////////////
    typedef enum ycode {
        y_none = 0, y_coin_given = 11, y_coin_not_given, y_change_secret,
        y_secret_change_denied, y_secret_changed, y_verify_ownership,
        y_ownership_wrong, y_ownership_ok, y_zk_info, y_zk_challenge,
        y_coin_transfer, y_receive_coin, y_new_secret, y_transfer_completed,
        y_transfer_rejected
    } Ycode;

    //#define y_none                     0
    //#define y_coin_given               11
    //#define y_coin_not_given           12
    //#define y_change_secret            13
    //#define y_secret_change_denied     14
    //#define y_secret_changed           15
    //#define y_verify_ownership         16
    //#define y_ownership_wrong          17
    //#define y_ownership_ok             18
    //#define y_zk_info                  19
    //#define y_zk_challenge             20
    //#define y_coin_transfer            21
    //#define y_receive_coin             22
    //#define y_new_secret               23
    //#define y_transfer_completed       24
    //#define y_transfer_rejected        25


    Xcode x_code;
   Ycode y_code;
   static char message[100];
   Message() { x_code=Message::x_none; y_code= Message::y_none; }
   char* ssx(Xcode x_code) {
       static char buf[100];
       if (x_code == Message::x_none)
           sprintf_s(buf, "%s", Message::x_none);
       else if (x_code == x_start)
           sprintf_s(buf, "%s", "x_start");
       else if (x_code == x_hup)
           sprintf_s(buf, "%s", "x_hup");
       else if (x_code == x_message)
           sprintf_s(buf, "%s", "x_message");
       else if (x_code == x_ok)
           sprintf_s(buf, "%s", "x_ok");
       else
           strcpy_s(buf, "????");
       return buf;
   }//end ssx
   char* ssy(Ycode y_code) {
       static char buf[100];
       if (y_code == y_none)
           sprintf_s(buf, "%s", "y_none");
       else if (y_code == y_coin_given)
           sprintf_s(buf, "%s", "y_coin_given");
       else if (y_code == y_coin_given)
           sprintf_s(buf, "%s", "y_coin_given");
       else if (y_code == y_change_secret)
           sprintf_s(buf, "%s", "y_change_secret");
       else if (y_code == y_secret_change_denied)
           sprintf_s(buf, "%s", "y_secret_change_denied");
       else if (y_code == y_secret_changed)
           sprintf_s(buf, "%s", "y_secret_changed");
       else if (y_code == y_verify_ownership)
           sprintf_s(buf, "%s", "y_verify_ownership");
       else if (y_code == y_ownership_wrong)
           sprintf_s(buf, "%s", "y_ownership_wrong");
       else if (y_code == y_ownership_ok)
           sprintf_s(buf, "%s", "y_ownership_ok");
       else if (y_code == y_zk_info)
           sprintf_s(buf, "%s", "y_zk_info");
       else if (y_code == y_zk_challenge)
           sprintf_s(buf, "%s", "y_zk_challeneg");
       else if (y_code == y_coin_transfer)
           sprintf_s(buf, "%s", "y_coin_transfer");
       else if (y_code == y_receive_coin)
           sprintf_s(buf, "%s", "y_receive_coin");
       else if (y_code == y_new_secret)
           sprintf_s(buf, "%s", "y_new_secret");
       else if (y_code == y_transfer_completed)
           sprintf_s(buf, "%s", "y_transfer_completed");
       else if (y_code == y_transfer_rejected)
           sprintf_s(buf, "%s", "y_transfer_rejected");
       else
           strcpy_s(buf, "????");
       return buf;
   }//end ssy
   char* sx() { return ssx(x_code); }
   char* sy() { return ssy(y_code); }
};//end class Message

class Wallet;
class Mint;


class Comm {
public:
   char __message[100];
   Wallet *w1;
   Wallet *w2;
   Mint *mint;
   char name1[100];
   char name2[100];
 
   Comm(Wallet *w1,Wallet *w2);   //initialization for wdialog (wallet-to-wallet)
   Comm(Wallet* w1,Mint* mint);   //initialization for mdialog (wallet-to-mint)
   void wcomm(Message& m);
   void mcomm(Message& m);
};//end class Comm

#endif
