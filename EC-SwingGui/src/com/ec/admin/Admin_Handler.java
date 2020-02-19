/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.admin;

import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Library;

public class Admin_Handler {
	
	public interface Admin_JNA_I extends Library{
		Admin_JNA_I INSTANCE = (Admin_JNA_I) Native.load("DigitalLoyaltyMoney", Admin_JNA_I.class);
		
		// constructor
		Pointer Admin_constructor();
		// functions
		void Admin_randomSelection(Pointer admin);
		// TO-DO the boolean for Admin_verifyDecrypted might cause problem
		boolean Admin_verifyDecrypted(Pointer admin, Pointer mValues, Pointer mEncryptedValue, Pointer decryptedSelectedKey, Pointer mnValues, Pointer mnEncryptedKey);
		int Admin_primeMultiplication(Pointer admin, Pointer key, Pointer decryptKey);
		// TO-DO Admin_displayCoin
		void Admin_addCoin(Pointer admin, int id, int val);
		void Admin_replaceCoinVal(Pointer admin, int replacedID, int replacedValue);
	}
	
	private Pointer admin;
	
	public Admin_Handler() {
		admin = Admin_JNA_I.INSTANCE.Admin_constructor();
	}
	
	public void randomSelection() {
		Admin_JNA_I.INSTANCE.Admin_randomSelection(admin);
	}
	
	/*
	 * 
	 * @param int mValues[SECURITY_LOOP]
	 * @param primeNumberExpo_t mEncryptedKey[SECURITY_LOOP]
	 * @param primeNumberExpo_t decryptedSelectedKey[SECURITY_LOOP]
	 * @param int mnValues[SECURITY_LOOP]
	 * @param primeNumberExpo_t mnEncryptedKey[SECURITY_LOOP]
	 */
	public boolean verifyDecrypted(Pointer mValues,  Pointer mEncryptedValue, Pointer decryptedSelectedKey, Pointer mnValues, Pointer mnEncryptedKey) {
		return Admin_JNA_I.INSTANCE.Admin_verifyDecrypted(mnEncryptedKey, mValues, mEncryptedValue, decryptedSelectedKey, mnValues, mnEncryptedKey);
	}
	
	/*
	 * 
	 * @param std::vector<int> key
	 * @param std::vector<int> decryptKey
	 */
	public int primeMultiplication(Pointer key, Pointer decryptKey) {
		return Admin_JNA_I.INSTANCE.Admin_primeMultiplication(admin, key, decryptKey);
	}
	
	public void addCoin(int id, int val) {
		Admin_JNA_I.INSTANCE.Admin_addCoin(admin, id, val);
	}
	
	public void replaceCoinVal(int replacedID, int replacedValue) {
		Admin_JNA_I.INSTANCE.Admin_replaceCoinVal(admin, replacedID, replacedValue);
	}
}
