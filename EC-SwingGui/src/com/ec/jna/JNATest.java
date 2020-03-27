/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.jna;

/**
 *
 * @author wensh
 */
public class JNATest {
    
    public static void main(String[] args) {
        String output;
        
        WalletHandler wallet1 = new WalletHandler();
        WalletHandler wallet2 = new WalletHandler();
//        output = wallet.showWallet(false);
//        System.out.println(output);

//        output = wallet1.transfer(wallet2.wallet);
//        System.out.println(output);

        output = wallet1.transferFakse(wallet2.wallet);
        System.out.println(output);
        
        AdminHandler admin = new AdminHandler();
//        output = admin.showMint(false);
//        System.out.println(output);
        
        
    }
}
