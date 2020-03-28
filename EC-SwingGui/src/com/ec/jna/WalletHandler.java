/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.jna;

import com.ec.utils.Logger;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 *
 * @author wensh
 */
public class WalletHandler {
        public interface JNA extends Library {

        JNA INSTANCE = Native.load(String.format("%s%sdll%sCryptoMoney.dll", System.getProperty("user.dir"), File.separator, File.separator), JNA.class);

        // constructor
        Pointer init_wallet();

        // String
        String show_wallet(Pointer wallet, Boolean mini);
        String verify(Pointer wallet, int id);
        String transfer(Pointer sender, Pointer receiver);
        String transfer_fake(Pointer sender, Pointer receiver);
    }
        
    Pointer wallet;
    String[] tokenId;
    private int instanceId;
    
    public static Pointer RetrieveOrCreateWalletPointer(int instanceId, boolean create) {
        if (AdminHandler.JNAWalletPointers.get(instanceId) == null && create) {
            Pointer walletPointer = JNA.INSTANCE.init_wallet();
            AdminHandler.JNAWalletPointers.put(instanceId, walletPointer);
            return walletPointer;
        } else {
            return AdminHandler.JNAWalletPointers.get(instanceId);
        }
    }
    
    public WalletHandler(int instanceId){
        wallet = WalletHandler.RetrieveOrCreateWalletPointer(instanceId, true);
        Logger.Log("Admin/Wallet created.");
        instanceId = instanceId;
    }
    
    public String showWallet(Boolean mini) {
        return Logger.Log(JNA.INSTANCE.show_wallet(wallet, mini));
    }
    
    public String verify(int id){
        return Logger.Log(JNA.INSTANCE.verify(wallet, id));
    }
    
    public String transfer(Pointer receiver) {
        return Logger.Log(JNA.INSTANCE.transfer(wallet, receiver));
    }
    
    public String transferFakse(Pointer receiver) {
        return Logger.Log(JNA.INSTANCE.transfer_fake(wallet, receiver));
    }
    
    public List<String> sp_getWalletMiniData() {
        String coinsData = this.showWallet(true).split("wallet \\d\n")[1];
        List<String> output = Arrays.asList(coinsData.split("\\s*coin: \\d+\n\\s*"));
        output = output.subList(1, output.size());
        return output;
    }
}
