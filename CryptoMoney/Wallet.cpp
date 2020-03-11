#include "Mint.cpp"
/* *******************************************************************************
 *                        class Wallet
 ********************************************************************************** */
class Wallet {
public:
    CoinWlist* coins;
    long walletid;
    static Mint* mint;
    static long last_id;
    char wpartner[100];
    char mpartner[100];
    Comm* mC, * wC;
    Message::Ycode mdialogue_type;
    CoinWnode* mdialogue_coin;
    BigNum* mdialogue_secret;
    Message::Xcode mylast_x_code;
    Message::Ycode mylast_y_code;
    Message::Ycode mdialogue_res;
    long wdialogue_coinid;
    BigNum* wdialogue_secret;
    Vector* wdialogue_vector;
    Message::Xcode wylast_x_code;
    Message::Ycode wylast_y_code;
    Message::Ycode wdialogue_type;
    Message::Ycode wdialogue_res;
    long zk_challenge[number_of_rounds];
    long zk_response[number_of_rounds];
    long left_keys[number_of_rounds];
    long right_keys[number_of_rounds];
    ZK_INFO* zk_info;

    void init() {
        if (wC) delete wC;
        if (mC) delete mC;
        wC = mC = 0;
        mpartner[0] = '\0';
        wpartner[0] = '\0';
        mdialogue_type = Message::y_none;
        wdialogue_type = Message::y_none;
        mdialogue_coin = 0;
        mdialogue_secret = 0;
        mylast_x_code = Message::x_none;
        mylast_y_code = Message::y_none;
        mdialogue_res = Message::y_none;
        wdialogue_coinid = 0;
        wdialogue_secret = 0;
        wylast_x_code = Message::x_none;
        wylast_y_code = Message::y_none;
        wdialogue_res = Message::y_none;
        for (long i = 0; i < number_of_rounds; i++) {
            zk_challenge[i] = -1;
            zk_response[i] = 0;
            left_keys[i] = 0;
            right_keys[i] = 0;
        }
        zk_info = 0;
    }//end init


    Wallet() {
        walletid = ++last_id;
        wC = mC = 0;
        init();
        coins = new CoinWlist();
        get_initial_coins();
    }//end Wallet

    ~Wallet() { if (coins) delete coins; }

    void show() {
        printf("wallet %u:\n", walletid);
        if (coins == 0)
            printf("empty\n");
        else
            coins->show(true);
    }//end show

    void minishow() {
        printf("wallet %u\n", walletid);
        if (coins == 0)
            printf("empty\n");
        else
            coins->show(false);
    }//end minishow

    BigNum* getSecret(long coinid) {
        if (coins == 0) return 0;
        CoinWnode* p;
        for (p = coins->root; p != 0; p = p->next)
            if (p->coinid == coinid) return p->secret;
        return 0;
    }//end getSecret


    CoinWnode* find_coin(long coinid) {
        if (coins == 0) return 0;
        if (coins->root == 0) return 0;
        for (CoinWnode* p = coins->root; p != 0; p = p->next) {
            if (p->coinid == coinid)
                return p;
        }
        return 0;
    }//end find_coin


    // just for the initial setup, to get 10 coins from Mint
    // can be applied only once, otherwise Mint will object
    // Only 10 coins can be had, if you ask for more, Mint will
    // object by responding with the y code y_coin_not_given
    void get_initial_coin() {
        Util util;
        Vector* vector = new Vector(size_of_factorization);
        vector->random();
        BigNum* secret = new BigNum();
        vector->prod(*secret, starting_prime);
        long coinid;
        long x;
        x = mint->give_initial_coin(walletid, secret, coinid);
        if (x == Message::y_coin_not_given) {
            printf("did not get required coin from Mint");
            util.GETCHAR();
            exit(0);
        }
        else {
            coins->insert(coinid, secret, vector);
        }
    }//end get_initial_coin

    void get_initial_coins() {
        Util util;
        for (long i = 0; i < number_of_initial_coins; i++)
            get_initial_coin();
        printf("wallet %d: recieved %d initial coins from mint", walletid, number_of_initial_coins);
        util.GETCHAR();
    }//end get_initial_coins


#define wHUP() { wylast_x_code = m.Message::x_code = Message::x_hup; \
                    wylast_y_code = m.Message::y_code = Message::y_none; \
                    wdialogue_type = Message::y_none; \
                    printf("wallet %d: protocol fault, hanging up",walletid); \
                    return m; }


    void transfer_coin(Wallet* w) {
        Util util;
        init();
        w->init();
        wC = new Comm(this, w);  // communication object
        sprintf_s(wpartner, "wallet %d", w->walletid);
        Message m;
        m.x_code = Message::x_start;
        sprintf_s(m.message, "wallet %d", walletid);  // so the wallet w knows who it is talking to
        wdialogue_coinid = coins->root->coinid;
        if (wdialogue_secret) delete wdialogue_secret;
        wdialogue_secret = coins->root->secret;
        printf("wallet %d: sent x_start to %s to start coin transfer", walletid, wpartner);
        util.GETCHAR();
        wylast_x_code = Message::x_start;
        wylast_y_code = Message::y_none;
        wdialogue_type = Message::y_coin_transfer;
        wC->wcomm(m);
        delete wC;
        wC = 0;
    }//end transfer_coin

     //just for testing  
    void transfer_fake_coin(Wallet* w) {
        long coinid;
        BigNum* secret;
        Vector* v;
        mint->give_fake_coin(coinid, secret, v);
        // add the fake coin as the first one in the coins
        coins->insert(coinid, secret, v);
        transfer_coin(w);
        //remove the fake coin
        CoinWnode* p = coins->root;
        if (coins->root->next == 0) {
            coins->root = 0;
            p->prev = p->next;
            delete p;
        }
        else {
            coins->root = coins->root->next;
            coins->root->prev = 0;
            p->next = p->prev = 0;
            delete p;
        }
    }//end transfer_fake_coin

    void get_newsecret_from_message(Message& m) {
        BigNum** q = (BigNum**)&m.message;
        wdialogue_secret = *q;
    }//end get_newsecret_from_message

    void generate_newsecret_to_message(Message& m) {
        wdialogue_vector = new Vector(size_of_factorization);
        wdialogue_vector->random();
        wdialogue_secret = new BigNum();
        wdialogue_vector->prod(*wdialogue_secret, starting_prime);
        BigNum** p = (BigNum**)&m.message;
        *p = wdialogue_secret;
    }//end generate_newsecret_to_message


    void remove_transferred_coin(Message& m) {
        if (coins == 0) {
            printf("remove_transferred_coin internal error 1\n");
            exit(0);
        }
        if (coins->root == 0) {
            printf("remove_transefered_coin internal error 2\n");
            exit(0);
        }
        bool found = false;
        CoinWnode* p;
        for (p = coins->root; p != 0; p = p->next) {
            if (p->coinid == wdialogue_coinid) {
                found = true;
                break;
            }
        }
        if (!found) {
            printf("remove_transefered_coin internal error 2\n");
            exit(0);
        }
        // remove p
        CoinWnode* q;
        if (p == coins->root) {  // first node
            q = coins->root;
            coins->root = p->next;
            coins->root->prev = 0;
            q->next = 0;
            delete q;
        }
        else if (p->next == 0) { // last node
            p->prev->next = 0;
            p->prev = 0;
            delete p;
        }
        else {                   // in-between node
            q = p->prev;
            q->next = p->next;
            p->prev = p->next = 0;
            delete p;
        }
        long* t = (long*)&m.message;
        *t = wdialogue_coinid;
        printf("wallet %d: transferred coin %d to %s", walletid, wdialogue_coinid, wpartner);
        Util util;
        util.GETCHAR();
    }//end remove_transferred coin


    void add_transferred_coin(Message& m) {
        Util util;
        long* p = (long*)&m.message;
        wdialogue_coinid = *p;
        printf("wallet %d: received coin %d from %s", walletid, wdialogue_coinid, wpartner);
        util.GETCHAR();
        coins->insert(wdialogue_coinid, wdialogue_secret, wdialogue_vector);
    }//end dd_transferred_coin


    Message& wdialogue(Message& m) {
        Util util;
        if (m.x_code == Message::x_start) {
            if (wdialogue_type == Message::y_coin_transfer) wHUP()
                if (wylast_x_code != 0 || wylast_y_code != 0) wHUP()
                    strcpy_s(wpartner, m.message);
            wdialogue_type = Message::y_receive_coin;
            printf("wallet %d: received x_start for coin transfer from %s, sending x_ok to %s", walletid, wpartner, wpartner);
            util.GETCHAR();
            wylast_x_code = m.x_code = Message::x_ok;
            wylast_y_code = m.y_code = Message::y_none;
            return m;
        }

        if (m.x_code == Message::x_ok) {
            if (wdialogue_type == 0 || wdialogue_type == Message::y_receive_coin) wHUP()
                if (wylast_x_code != Message::x_start || wylast_y_code != 0) wHUP()
                    printf("wallet %d: received x_ok from %s, sending request for y_new_secret to %s", walletid, wpartner, wpartner);
            util.GETCHAR();
            wylast_x_code = m.x_code = Message::x_message;
            wylast_y_code = m.y_code = Message::y_new_secret;
            return m;
        }

        if (m.x_code == Message::x_hup) {
            if (m.y_code == Message::y_transfer_completed || m.y_code == Message::y_transfer_rejected) {
                if (m.y_code == Message::y_transfer_completed) add_transferred_coin(m);
                printf("wallet %d: received %s from %s, hanging up", walletid, m.sy(), wpartner);
                wdialogue_res = m.y_code;
                wylast_x_code = m.x_code = Message::x_hup;
                wylast_y_code = m.y_code = Message::y_none;
                util.GETCHAR();
                return m;
            }
            wHUP()
        }

        if (m.x_code == Message::x_message) {
            if (wdialogue_type == Message::y_receive_coin) { // must send new secret to wallet1
                if (wylast_x_code != Message::x_ok && wylast_x_code != Message::x_message) wHUP()
                    if (wylast_y_code != Message::y_none) wHUP()
                        if (m.y_code != Message::y_new_secret) wHUP()
                            generate_newsecret_to_message(m);
                m.x_code = wylast_x_code = Message::x_message;
                m.y_code = wylast_y_code = Message::y_new_secret;
                printf("wallet %d: received request for %s from %s, sendin %s to %s", walletid, m.sy(), wpartner, m.sy(), wpartner);
                util.GETCHAR();
                return m;
            }
            else if (wdialogue_type == Message::y_coin_transfer) { // must perform change_secret
                if (wylast_x_code != Message::x_message || wylast_y_code != Message::y_new_secret) wHUP()
                    get_newsecret_from_message(m);
                request_change_secret(wdialogue_secret);
                if (mdialogue_res == Message::y_secret_changed) {
                    remove_transferred_coin(m);
                    m.x_code = Message::x_hup;
                    m.y_code = Message::y_transfer_completed;
                    wylast_x_code = Message::x_none;
                    wylast_y_code = Message::y_none;
                    return m;
                }
                else {
                    m.x_code = Message::x_hup;
                    m.y_code = Message::y_transfer_rejected;
                    wylast_x_code = Message::x_none;
                    wylast_y_code = Message::y_none;
                    wdialogue_type = Message::y_none;
                    return m;
                }
            }
            else {
                printf("wdialogue_type error\n");
                exit(0);
            }
        }
        wHUP()
    }//end wdialogue


    void request_change_secret(BigNum* newsecret) {
        Util util;
        if (mC) delete mC;
        mC = new Comm(this, mint);  // communication object
        sprintf_s(mpartner, "mint");
        Message m;
        m.x_code = Message::x_start;
        sprintf_s(m.message, "wallet %d", walletid);  // so the Mint knows who it is talking to
        mdialogue_type = Message::y_change_secret;
        mdialogue_coin = coins->root;
        mdialogue_secret = newsecret;
        printf("wallet %d: sent x_start to mint", walletid);
        util.GETCHAR();
        mylast_x_code = Message::x_start;
        mylast_y_code = Message::y_none;
        mC->mcomm(m);
        delete mC;
        mC = 0;
    }//end request_change_secret


    void request_verify_ownership(long coinid) {
        Util util;
        init();
        if (mC) delete mC;
        mC = new Comm(this, mint);  // communication object
        sprintf_s(mpartner, "mint");
        Message m;
        m.x_code = Message::x_start;
        sprintf_s(m.message, "wallet %d", walletid);  // so the Mint knows who it is talking to
        mdialogue_type = Message::y_verify_ownership;
        mdialogue_coin = find_coin(coinid);
        if (mdialogue_coin == NULL) {
            printf("wallet %d: coin %d do not exist", walletid, coinid);
            util.GETCHAR();
            mylast_x_code = Message::x_none;
            mylast_y_code = Message::y_none;
            m.x_code = Message::x_hup;
        }
        else {
            if (mdialogue_secret) delete mdialogue_secret;
            mdialogue_secret = 0;
            printf("wallet %d: sent x_start to mint", walletid);
            util.GETCHAR();
            mylast_x_code = Message::x_start;
            mylast_y_code = Message::y_none;
            mC->mcomm(m);
            delete mC;
            mC = 0;
        }
    }//end request_verify_ownership


    void put_coinid_newsecret_in_message(Message& m, CoinWnode*& mdialogue_coin, BigNum* mdialogue_secret) {
        //we want mint to change secret for the coin with coinid
        long* y = (long*)&m.message;
        *y = mdialogue_coin->coinid;
        BigNum** z = (BigNum**)&m.message[sizeof(long)];
        *z = mdialogue_secret;
    }//end put_coin_newsecret_in_message


    void put_coinid_in_message(Message& m, long coinid) {
        long* y = (long*)&m.message;
        *y = coinid;
    }//end put_coinid_in_message


    // creates zk_info, stores it, and puts an address of it to message
    // it also creates left_keys[] and right_keys[]
    void put_zk_info_in_message(Message& m, CoinWnode* coin) {
        srand((unsigned int)time(0));
        for (long i = 0; i < number_of_rounds; i++) {
            left_keys[i] = rand();
            right_keys[i] = rand();
        }
        zk_info = new ZK_INFO(*coin->secret, *coin->vector, left_keys, right_keys);
        ZK_INFO** p = (ZK_INFO**)&m.message;
        *p = zk_info;
    }//end put_zk_info_in_message


    void get_zk_challenge_from_message(Message& m) {
        long* p = *((long**)&m.message);
        for (long i = 0; i < number_of_rounds; i++)
            zk_challenge[i] = p[i];
    }

    void put_zk_response_in_message(Message& m) {
        long i;
        for (i = 0; i < number_of_rounds; i++) {
            if (zk_challenge[i] == 0)  // open left vector
                zk_response[i] = left_keys[i];
            else                     // open right vector
                zk_response[i] = right_keys[i];
        }
        long** q = (long**)m.message;
        *q = zk_response;
    }//end put_zk_challenge_in_message

#define mHUP() { printf("wallet %d: wallet-mint protocol fault, hanging up",walletid); \
                    Util util; \
                    util.GETCHAR(); \
                    m.x_code = Message::x_hup; \
                    m.y_code = Message::y_none; \
                    mylast_x_code = Message::x_none; \
                    mylast_y_code = Message::y_none; \
                    return m; }

    Message& mdialogue(Message& m) {
        Util util;

        if (m.x_code == Message::x_ok) {
            if (mylast_x_code != Message::x_start) mHUP()
                if (mdialogue_type == Message::y_change_secret) { // change_secret
                    mylast_x_code = m.x_code = Message::x_message;
                    mylast_y_code = m.y_code = Message::y_change_secret;
                    put_coinid_newsecret_in_message(m, mdialogue_coin, mdialogue_secret);
                    printf("wallet %d: received x_ok from mint, sending y_change_secret to mint for coin %d", walletid, mdialogue_coin->coinid);
                    util.GETCHAR();
                    return m;
                }
                else {
                    mylast_x_code = m.x_code = Message::x_message;
                    mylast_y_code = m.y_code = Message::y_verify_ownership;
                    put_coinid_in_message(m, mdialogue_coin->coinid);
                    printf("wallet %d: received x_ok from mint, sending y_verify_ownership to mint for coin %d", walletid, mdialogue_coin->coinid);
                    util.GETCHAR();
                    return m;
                }
        }

        if (m.x_code == Message::x_message) {
            if (m.y_code == Message::y_zk_info) {
                if (coins == 0) {
                    printf("wallet %d: error -- I do not have any coins to give\n", walletid);
                    mHUP()
                }
                if (coins->root == 0) {
                    printf("wallet %d: error -- I do not have any coins to give\n", walletid);
                    mHUP()
                }
                mdialogue_coin = coins->root;
                put_zk_info_in_message(m, mdialogue_coin);
                mylast_x_code = m.x_code = Message::x_message;
                mylast_y_code = m.y_code = Message::y_zk_info;
                printf("wallet %d: received request for zk_info for coin %d from mint, sending zk_info to mint", walletid, mdialogue_coin->coinid);
                util.GETCHAR();
                return m;
            }
            else if (m.y_code == Message::y_zk_challenge) {
                get_zk_challenge_from_message(m);
                put_zk_response_in_message(m);
                mylast_x_code = m.x_code = Message::x_message;
                mylast_y_code = m.y_code = Message::y_zk_challenge;
                printf("wallet %d: received zk_challenge for coin %d from mint, sending zk_response to mint", walletid, mdialogue_coin->coinid);
                util.GETCHAR();
                return m;
            }
            else mHUP()
        }

        if (m.x_code == Message::x_hup) {
            if (m.y_code == Message::y_secret_changed || m.y_code == Message::y_secret_change_denied || m.y_code == Message::y_ownership_ok ||
                m.y_code == Message::y_ownership_wrong) {
                printf("wallet %d: received %s for coind %d from mint, terminating communication with mint", walletid, m.sy(), mdialogue_coin->coinid);
                util.GETCHAR();
                mdialogue_res = m.y_code;
                mylast_x_code = Message::x_none;
                mylast_y_code = Message::y_none;
                m.x_code = Message::x_none;
                m.y_code = Message::y_none;
                return m;
            }
            else mHUP()
        }
        mHUP()
    }//end mdialogue
};//end class Wallet
