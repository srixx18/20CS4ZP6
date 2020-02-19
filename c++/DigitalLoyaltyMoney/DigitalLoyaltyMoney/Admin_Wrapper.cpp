#include "pch.h"
#include "Admin.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" DLL_EXPORT Admin * Admin_constructor();
Admin* Admin_constructor() 
{
	return new Admin();
}

extern "C" DLL_EXPORT void Admin_randomSelection(Admin * self)
{
	self->randomSelection();
}

extern "C" DLL_EXPORT bool Admin_verifyDecryptedKey(Admin * self, int * mValues, primeNumberExpo_t * mEncryptedValue, primeNumberExpo_t * decryptedSelectedKey, int * mnValues, primeNumberExpo_t * mnEncryptedKey)
{
	return self->verifyDecryptedKey(mValues, mEncryptedValue, decryptedSelectedKey, mnValues, mnEncryptedKey);
}

extern "C" DLL_EXPORT int Admin_primeMultiplication(Admin * self, std::vector<int> key, std::vector<int> decryptKey)
{
	return self->primeMultiplication(key, decryptKey);
}

extern "C" DLL_EXPORT std::map<int, int> Admin_displayCoin(Admin * self)
{
	return self->displayCoin();
}

extern "C" DLL_EXPORT void Admin_addCoin(Admin * self, int id, int val)
{
	self->addCoin(id, val);
}

extern "C" DLL_EXPORT void Admin_replaceCoinVal(Admin * self, int replacedID, int replacedValue)
{
	self->replaceCoinVal(replacedID, replacedValue);
}