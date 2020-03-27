// here comes the implementation of Comm
// unblock _com_debug to see the message traffic as passed on by comm
//#define _com_debug
#include "wallet.cpp"
#include "comm_impl.hpp"
#include "pch.h"

#pragma once
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C" DLL_EXPORT Wallet* init_wallet();
extern "C" DLL_EXPORT char* show_mint(Wallet *w, bool mini);
extern "C" DLL_EXPORT char* show_wallet(Wallet *w, bool mini);
extern "C" DLL_EXPORT char* verify(Wallet *w, int id);
extern "C" DLL_EXPORT char* transfer(Wallet *sender, Wallet *recv);
extern "C" DLL_EXPORT char* transfer_fake(Wallet * sender, Wallet * recv);