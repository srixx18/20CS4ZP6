/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.main;

import com.ec.admin.Admin;
import com.ec.jna.AdminHandler;
import com.ec.jna.WalletHandler;
import com.ec.wallet.Wallet;
import java.io.File;

/**
 *
 * @author wensh
 */
public class Main {
    
    Admin admin;
    Wallet wallet;
    
    public Main() {
        admin = new Admin();
        wallet = new Wallet();
        
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                admin.setVisible(true);
                wallet.setVisible(true);
            }
        });
    }

    public static void main(String[] args) {
        new Main();
    }
}
