/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.wallet;

import com.ec.constants.EC_Constant;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public class Wallet_Handler {
	
	public interface Wallet_JNA_I extends Library{
		Wallet_JNA_I INSTANCE = (Wallet_JNA_I) Native.load("DigitalLoyaltyMoney", Wallet_JNA_I.class);
		
		// constructor
		Pointer Wallet_constructor();
		// functions
		int Wallet_primeMultiplication(Pointer wallet, Pointer key);
		void Wallet_randomMGenerator(Pointer wallet);
		EC_Constant.KeyValuePair Wallet_randomKeyGenerator(Pointer wallet);
		void Wallet_computeMN(Pointer wallet, int id);
		void Wallet_encryptedSecret(Pointer wallet);
		void Wallet_decryptSelectedKeys(Pointer wallet, Pointer randomSelectedKey);
		// TO-DO Wallet_displayCoin
		void Wallet_addCoin(Pointer wallet, int id);
		void Wallet_removeCoin(Pointer wallet, int id);
	}
	
	private Pointer wallet;
	
	public int primeMultiplication(Pointer key) {
		return Wallet_JNA_I.INSTANCE.Wallet_primeMultiplication(wallet, key);
	}
	
	public void randomMGenerator() {
		Wallet_JNA_I.INSTANCE.Wallet_randomMGenerator(wallet);
	}
	
	public EC_Constant.KeyValuePair randomKeyGenerator(){
		return Wallet_JNA_I.INSTANCE.Wallet_randomKeyGenerator(wallet);
	}
	
	public void computeMN(int id) {
		Wallet_JNA_I.INSTANCE.Wallet_computeMN(wallet, id);
	}
	
	public void encryptedSecret() {
		Wallet_JNA_I.INSTANCE.Wallet_encryptedSecret(wallet);
	}
	
	public void decryptSelectedKeys(Pointer randomSelectedKey) {
		Wallet_JNA_I.INSTANCE.Wallet_decryptSelectedKeys(wallet, randomSelectedKey);
	}
	
	public void addCoin(int id) {
		Wallet_JNA_I.INSTANCE.Wallet_addCoin(wallet, id);
	}
	
	public void removeCoin(int id) {
		Wallet_JNA_I.INSTANCE.Wallet_removeCoin(wallet, id);
	}
}
