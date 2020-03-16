/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.jna;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

/**
 *
 * @author wensh
 */
public class AdminHandler {

    public interface JNA extends Library {

        JNA INSTANCE = Native.load(String.format("%s%sdll%sCryptoMoney.dll", System.getProperty("user.dir"), File.separator, File.separator), JNA.class);

        // constructor
        Pointer init_wallet();

        // void
        void show_mint(Pointer wallet, Boolean mini);
    }

    Pointer admin;
    String[] tokenId;

    public AdminHandler() {
        admin = JNA.INSTANCE.init_wallet();
    }

    public void showMint(Boolean mini) {
        JNA.INSTANCE.show_mint(admin, mini);
    }
}
