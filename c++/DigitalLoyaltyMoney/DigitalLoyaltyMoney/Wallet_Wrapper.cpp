#include "pch.h"
#include "Wallet.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" DLL_EXPORT Wallet * Wallet_constructor();
Wallet* Wallet_constructor()
{
	return new Wallet();
}

extern "C" DLL_EXPORT int Wallet_primeMultiplication(Wallet * self, std::vector<int> key)
{
	return self->primeMultiplication(key);
}

extern "C" DLL_EXPORT void Wallet_randomMGenerator(Wallet * self)
{
	self->randomMGenerator();
}

extern "C" DLL_EXPORT keyValuePair Wallet_randomKeyGenerator(Wallet * self)
{
	return self->randomKeyGenerator();
}

extern "C" DLL_EXPORT void Wallet_computeMN(Wallet * self, int id)
{
	self->computeMN(id);
}

extern "C" DLL_EXPORT void Wallet_encryptedSecret(Wallet * self)
{
	self->encryptedSecret();
}

extern "C" DLL_EXPORT void Wallet_decryptSelectedKeys(Wallet * self, int * randomSelectedKey)
{
	self->decryptSelectedKeys(randomSelectedKey);
}

extern "C" DLL_EXPORT std::map<int, int> Wallet_displayCoin(Wallet * self)
{
	return self->displayCoin();
}

extern "C" DLL_EXPORT void Wallet_addCoin(Wallet * self, int id)
{
	self->addCoin(id);
}

extern "C" DLL_EXPORT void Wallet_removeCoin(Wallet * self, int id)
{
	self->removeCoin(id);
}