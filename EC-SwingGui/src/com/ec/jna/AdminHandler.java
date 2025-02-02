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
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.List;

/**
 *
 * @author wensh
 */
public class AdminHandler {

    public interface JNA extends Library {

        JNA INSTANCE = Native.load(String.format("%s%sdll%sCryptoMoney.dll", System.getProperty("user.dir"), File.separator, File.separator), JNA.class);

        // constructor
        Pointer init_wallet();

        // String
        String show_mint(Pointer wallet, Boolean mini);
    }

    Pointer admin;
    String[] tokenId;
    
    public static Dictionary<Integer, Pointer> JNAWalletPointers = new Hashtable<Integer, Pointer>();
    
    public AdminHandler() {
        admin = JNA.INSTANCE.init_wallet();
        Logger.Log("Admin/Wallet created.");
        JNAWalletPointers.put(1, admin);
    }

    public String showMint(Boolean mini) {
        return Logger.Log(JNA.INSTANCE.show_mint(admin, mini));
    }

    public List<String> sp_getMintMiniData() {
        String coinsData = this.showMint(true);
        List<String> output = Arrays.asList(coinsData.split("\\s*coin :\\s*"));
        output = output.subList(1, output.size());
        return output;
    }
    
}
