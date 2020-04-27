/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.main;

import com.ec.admin.Admin;
import com.ec.jna.AdminHandler;
import com.ec.jna.WalletHandler;
import com.ec.utils.Logger;
import com.ec.wallet.Wallet;
import java.io.File;
import java.util.ArrayList;
import javax.swing.JFrame;

/**
 *
 * @author wensh
 */
public class Main {
    
    public static ArrayList<Wallet> WalletInstances = new ArrayList<Wallet>();
    
    public static void RefreshWalletsCoinsSize() {
        for (Wallet wallet : WalletInstances) {
            wallet.updateCoinsSize();
        }
    }
    
    Logger logger;
    
    Admin admin;
    Wallet wallet1;
    Wallet wallet2;
    
    public Main() {
        logger = new Logger();
        admin = new Admin();
        wallet1 = new Wallet(1);
        wallet2 = new Wallet(2);
        
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                logger.setVisible(true);
                admin.setVisible(true);
                wallet1.setVisible(true);
                wallet2.setVisible(true);
                logger.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                admin.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                wallet1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                wallet2.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            }
        });
    }

    public static void main(String[] args) {
        new Main();
    }
}
