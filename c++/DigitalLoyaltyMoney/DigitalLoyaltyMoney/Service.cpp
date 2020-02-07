#include "Service.h"


bool Service::verify(Admin admin, Wallet wallet, int id)
{
    if (wallet.coinTable.count(id) == 0) {
        return false;
    }
    else
    {
        wallet.randomMGenerator();
        wallet.computeMN(wallet.coinTable.at(id), wallet.secretTable.at(id));
        wallet.encryptedSecret();
        admin.randomSelection();
        wallet.decryptSelectedKeys(admin.randomSelectedKey);
        return admin.verifyDecryptedKey(wallet.mValues, wallet.mEncryptedKey, wallet.decryptedSelectedKey,
                                        wallet.mnValues, wallet.mnEncryptedKey);
    }
}

void Service::addNewCoin(Admin &admin, Wallet &wallet, int id)
{
    wallet.addCoin(id);
    admin.addCoin(id, wallet.coinTable.at(id));
}

void Service::transferCoin(Admin &admin, Wallet &sender, Wallet &receiver, int id)
{
    sender.removeCoin(id);
    receiver.addCoin(id);
    admin.replaceCoinVal(id, receiver.coinTable.at(id));
}
