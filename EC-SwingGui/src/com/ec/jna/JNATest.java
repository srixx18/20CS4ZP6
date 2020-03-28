/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.jna;

import java.util.List;

/**
 *
 * @author wensh
 */
public class JNATest {

    public void strTst() {
        String output;

        WalletHandler wallet1 = new WalletHandler();
        WalletHandler wallet2 = new WalletHandler();
        output = wallet1.showWallet(false);
        System.out.println(output);

        output = wallet1.transfer(wallet2.wallet);
        System.out.println(output);

        output = wallet1.transferFakse(wallet2.wallet);
        System.out.println(output);

        AdminHandler admin = new AdminHandler();
        output = admin.showMint(false);
        System.out.println(output);
    }

    public static void main(String[] args) {
        WalletHandler walletHandler = new WalletHandler();
        
        List<String> output = walletHandler.sp_getWalletMiniData();
        
        System.out.println(output.size());
    }
}
