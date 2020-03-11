#include "Coin.cpp"
// classes Mint and Walet need for communication some stuff from class Comm,
// and some stuff from Mint and Wallet are needed for implementation of Comm
// so here is the "interface" of Comm, but its implemenation must be after
// the implemenation of Mint and Wallet
#include "comm.hpp"

/* *******************************************************************************
 *                        class Mint
 ********************************************************************************** */
class Mint {
public:
    static long last_id;
    CoinMlist* coins;
    char partner[100];

    Mint() {
        coins = new CoinMlist();
        partner[0] = '\0';
    }

    // Mint gives every wallet number_of_initial_coins when they ask for it
     // the secret is created by the wallets, the coinid is generated by
     // Mint
    long give_initial_coin(long walletid, BigNum* secret, long& coinid) {
        Message m;
        long count = 0;
        for (CoinMnode* p = coins->root; p != 0; p = p->next)
            if (p->walletid == walletid) count++;
        if (count >= number_of_initial_coins) return m.y_coin_not_given;
        last_id++;
        coins->insert(last_id, secret, walletid);
        coinid = last_id;
        return m.y_coin_given;
    }//end give_initial_coin

     // For testing, get wallet a fake coin with a real coinid
    void give_fake_coin(long& coinid, BigNum*& secret, Vector*& v) {
        if (coins->root == 0) {
            // create a real coin first
            long coinid = ++last_id;
            v = new Vector(size_of_factorization);
            v->random();
            secret = new BigNum();
            v->prod(*secret);
            coins->insert(coinid, secret, 0);
            // now create a fake coin with the same coinid
            v->random_delta();
            v->prod(*secret);
        }
        else {
            coinid = coins->root->coin->coinid;
            v = new Vector(size_of_factorization);
            v->random();
            secret = new BigNum;
            while (true) {
                v->prod(*secret);
                if (*secret != *coins->root->coin->secret) return;
            }
        }
        return;
    }//end give_fake_coin

    void show() {
        if (coins == 0)
            printf("empty\n");
        else
            coins->show(true);
    }//end show

    void minishow() {
        if (coins == 0)
            printf("empty\n");
        else
            coins->show(false);
    }//end show

    CoinMnode* find(long coinid) {
        if (coins == 0)  return 0;
        if (coins->root == 0) return 0;
        CoinMnode* p;
        bool found = false;
        for (p = coins->root; p != 0; p = p->next) {
            if (p->coin->coinid == coinid) {
                found = true;
                break;
            }
        }
        if (found)
            return p;
        else
            return 0;
    }//end find

    void put_zk_challenge_in_message(Message& m, ZK_INFO* zk_info, long* zk_challenge) {
        srand((unsigned int)time(0));
        long i;
        for (i = 0; i < number_of_rounds; i++)
            zk_challenge[i] = rand() % 2;
        long** p = (long**)&m.message;
        *p = zk_challenge;
    }//end put_zk_challenge_in_message

    bool check_zk_response(ZK_INFO* zk_info, long* zk_challenge, long* zk_response, long coinid) {
        BigNum M;
        BigNum N;
        CoinMnode* p;

        p = find(coinid);
        if (!p) return false;
        // p->coin is the coin of interest
        long i;
        for (i = 0; i < number_of_rounds; i++) {
            if (zk_challenge[i] == 0) {
                zk_info->left[i].decode(zk_response[i]);
                zk_info->left[i].prod(M);
                if (M != zk_info->m[i]) return false;
            }
            else {
                zk_info->right[i].decode(zk_response[i]);
                BigNum::Mult(*p->coin->secret, zk_info->m[i], N);
                zk_info->right[i].prod(M);
                if (M != N) return false;
            }
        }//end for
        return true;
    }//end check_zk_challenge

    void change_secret(long coinid, BigNum* newsecret) {
        CoinMnode* p = find(coinid);
        if (p == 0) {
            printf("Mint: interanl error\n");
            exit(0);
        }
        *(p->coin->secret) = *newsecret;
    }//end change_secret


    Message& mdialogue(Message& m) {
        Util util;
        static Message::Ycode mylast_y_code = Message::y_none;
        static Message::Xcode mylast_x_code = Message::x_none;
        static long coinid = 0;
        static BigNum* newsecret = 0;
        static Message::Ycode protocol_type = Message::y_none;
        static ZK_INFO* zk_info = 0;
        static long* zk_challenge = 0;
        static long* zk_response = 0;
        bool res;

        if (m.x_code == Message::x_start) {
            strcpy_s(partner, m.message); // who I am talking too
            printf("mint: %s initialized mdialogue, sending x_ok to %s", partner, partner);
            util.GETCHAR();
            res = false;
            mylast_y_code = Message::y_none;
            mylast_x_code = m.x_code = Message::x_ok;
            coinid = -1;
            newsecret = 0;
            protocol_type = Message::y_none;
            zk_info = 0;
            if (zk_challenge == 0)
                zk_challenge = new long[number_of_rounds];
            for (long i = 0; i < number_of_rounds; i++)
                zk_challenge[i] = -1;
            zk_response = 0;
            return m;
        }//end of x_start

        if (m.x_code == Message::x_hup) {
            printf("mint: received x_hup, hanging up");
            util.GETCHAR();
            mylast_x_code = Message::x_none;
            mylast_y_code = Message::y_none;
            return m;
        }//end of x_hup

        if (m.x_code == Message::x_message) {
            if (m.y_code == Message::y_change_secret) {
                if (mylast_x_code != Message::x_ok || protocol_type != 0) {
                    // protocol fault
                    printf("mint: protocol fault, hanging up");
                    util.GETCHAR();
                    mylast_x_code = Message::x_none;
                    mylast_y_code = protocol_type = Message::y_none;
                    m.x_code = Message::x_hup;
                    return m;
                }
                protocol_type = Message::y_change_secret;
                ////////////////////////////////////////////////////////////////
                //             extract coinid+newsecret from message
                coinid = *(long*)m.message;
                newsecret = *(BigNum**)&m.message[sizeof(long)];
                ////////////////////////////////////////////////////////////////
                m.y_code = Message::y_zk_info;
                mylast_x_code = Message::x_message;
                mylast_y_code = Message::y_zk_info;
                printf("mint: received request for change_secret for coin %d from %s, sending request for zk_info to %s",
                    coinid, partner, partner);
                util.GETCHAR();
                return m;
            }//end of y_change_secret

            if (m.y_code == Message::y_verify_ownership) {
                if (mylast_x_code != Message::x_ok || protocol_type != 0) {
                    // protocol fault
                    printf("mint: protocol fault, hanging up");
                    util.GETCHAR();
                    mylast_x_code = Message::x_none;
                    mylast_y_code = protocol_type = Message::y_none;
                    m.x_code = Message::x_hup;
                    return m;
                }
                protocol_type = Message::y_verify_ownership;
                ////////////////////////////////////////////////////////////////
                // extract coinid from message
                coinid = *(long*)m.message;
                ///////////////////////////////////////////////////////////////
                m.y_code = Message::y_zk_info;
                mylast_x_code = Message::x_message;
                mylast_y_code = Message::y_zk_info;
                printf("mint: received request to verify_ownership of coin %d from %s, sending request for zk_info to %s",
                    coinid, partner, partner);
                util.GETCHAR();
                return m;
            }//end verify_ownership

            if (m.y_code == Message::y_zk_info) {
                if (mylast_y_code == Message::y_zk_info) {
                    ////////////////////////////////////////////////////////////////
                    // extract zk_info from m.message
                    zk_info = *(ZK_INFO**)&m.message;
                    ///////////////////////////////////////////////////////////////
                    put_zk_challenge_in_message(m, zk_info, zk_challenge);
                    m.x_code = mylast_x_code = Message::x_message;
                    m.y_code = mylast_y_code = Message::y_zk_challenge;
                    printf("mint: received zk_info foc coind %d from %s, sending zk_challenge to %s", coinid, partner, partner);
                    util.GETCHAR();
                    return m;
                }
                else {
                    // protocol fault
                    printf("mint: protocol fault, hanging up");
                    util.GETCHAR();
                    mylast_x_code = Message::x_none;
                    mylast_y_code = protocol_type = Message::y_none;
                    m.x_code = Message::x_hup;
                    return m;
                }
            }//end y_zk_info


            if (m.y_code == Message::y_zk_challenge) {
                if (mylast_y_code == Message::y_zk_challenge) {
                    ////////////////////////////////////////////////////////////////
                    // extract zk_response
                    zk_response = *(long**)m.message;
                    ///////////////////////////////////////////////////////////////
                    res = check_zk_response(zk_info, zk_challenge, zk_response, coinid);
                    m.x_code = Message::x_hup;
                    if (res) {
                        if (protocol_type == Message::y_change_secret) {
                            change_secret(coinid, newsecret);
                            m.y_code = Message::y_secret_changed;
                            mylast_x_code = Message::x_none;
                            mylast_y_code = protocol_type = Message::y_none;
                            printf("mint: received y_zk_challenge for coin %d from %s, sending y_secret_changed to %s, hanging up",
                                coinid, partner, partner);
                            util.GETCHAR();
                            return m;
                        }
                        else {
                            m.y_code = Message::y_ownership_ok;
                            mylast_x_code = Message::x_none;
                            mylast_y_code = protocol_type = Message::y_none;
                            printf("mint: received y_zk_challenge for coind %d from %s, sending y_ownership_ok to %s, hanging up",
                                coinid, partner, partner);
                            util.GETCHAR();
                            return m;
                        }
                    }
                    else {
                        if (protocol_type == Message::y_change_secret) {
                            m.y_code = Message::y_secret_change_denied;
                            mylast_x_code = Message::x_none;
                            mylast_y_code = protocol_type = Message::y_none;
                            printf("mint: received y_zk_challenge for coin %d from %s, sending y_secret_change_denied to %s, hanging up",
                                coinid, partner, partner);
                            util.GETCHAR();
                            return m;
                        }
                        else {
                            m.y_code = Message::y_ownership_wrong;
                            mylast_x_code = Message::x_none;
                            mylast_y_code = protocol_type = Message::y_none;
                            printf("mint: received y_zk_challenge for coin %d from %s, sending y_ownership_wrong to %s, hanging up", coinid, partner, partner);
                            util.GETCHAR();
                            return m;
                        }
                    }
                }
                else {
                    // protocol fault
                    printf("mint: protocol fault, hanging up");
                    util.GETCHAR();
                    mylast_x_code = Message::x_none;
                    mylast_y_code = Message::y_none;
                    m.x_code = Message::x_hup;
                    return m;
                }
            }
            else {
                // protocol fault
                printf("mint: protocol fault, hanging up");
                util.GETCHAR();
                mylast_x_code = Message::x_none;
                mylast_y_code = Message::y_none;
                m.x_code = Message::x_hup;
                return m;
            }
        }//end of x_message

        printf("mint: protocol faultn");
        util.GETCHAR();
        m.x_code = Message::x_hup;
        mylast_x_code = Message::x_none;
        mylast_y_code = Message::y_none;
        return m;
    }//end mdialogue
};//end class Mint
