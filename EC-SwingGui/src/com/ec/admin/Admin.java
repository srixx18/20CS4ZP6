/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.admin;

import com.ec.jna.AdminHandler;
import java.awt.CardLayout;
import com.ec.admin.CoinDetailCard;
import java.awt.Component;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.List;
import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

/**
 *
 * @author jiajin
 */
public class Admin extends javax.swing.JFrame {
    
    private AdminHandler adminHandler;

    /**
     * Creates new form NewJFrame
     */
    public Admin() {
        adminHandler = new AdminHandler();
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        holder = new javax.swing.JPanel();
        menu = new javax.swing.JPanel();
        menu_label = new javax.swing.JLabel();
        menu_coins_button = new javax.swing.JButton();
        coins = new javax.swing.JPanel();
        coinsScrollPane = new javax.swing.JScrollPane();
        coinsPane = new javax.swing.JPanel();

        jLabel1.setText("jLabel1");

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("EC_Admin");
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        setLocationByPlatform(true);
        setName("ec_admin"); // NOI18N
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        holder.setLayout(new java.awt.CardLayout());

        menu.setBackground(new java.awt.Color(255, 255, 255));

        menu_label.setBackground(new java.awt.Color(0, 0, 0));
        menu_label.setFont(new java.awt.Font("Dialog", 0, 24)); // NOI18N
        menu_label.setText("MENU");

        menu_coins_button.setFont(new java.awt.Font("Dialog", 0, 24)); // NOI18N
        menu_coins_button.setText("COINS");
        menu_coins_button.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                menu_coins_buttonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout menuLayout = new javax.swing.GroupLayout(menu);
        menu.setLayout(menuLayout);
        menuLayout.setHorizontalGroup(
            menuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(menuLayout.createSequentialGroup()
                .addGroup(menuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(menuLayout.createSequentialGroup()
                        .addGap(209, 209, 209)
                        .addComponent(menu_label))
                    .addGroup(menuLayout.createSequentialGroup()
                        .addGap(164, 164, 164)
                        .addComponent(menu_coins_button, javax.swing.GroupLayout.PREFERRED_SIZE, 163, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(173, Short.MAX_VALUE))
        );
        menuLayout.setVerticalGroup(
            menuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(menuLayout.createSequentialGroup()
                .addGap(34, 34, 34)
                .addComponent(menu_label)
                .addGap(67, 67, 67)
                .addComponent(menu_coins_button, javax.swing.GroupLayout.PREFERRED_SIZE, 69, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(400, Short.MAX_VALUE))
        );

        holder.add(menu, "menu");

        coins.setBackground(new java.awt.Color(255, 255, 255));

        coinsScrollPane.setBackground(new java.awt.Color(255, 255, 255));
        coinsScrollPane.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        coinsScrollPane.setPreferredSize(new java.awt.Dimension(500, 605));

        coinsPane.setBackground(new java.awt.Color(255, 255, 255));

        javax.swing.GroupLayout coinsPaneLayout = new javax.swing.GroupLayout(coinsPane);
        coinsPane.setLayout(coinsPaneLayout);
        coinsPaneLayout.setHorizontalGroup(
            coinsPaneLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 497, Short.MAX_VALUE)
        );
        coinsPaneLayout.setVerticalGroup(
            coinsPaneLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 602, Short.MAX_VALUE)
        );

        coinsScrollPane.setViewportView(coinsPane);

        javax.swing.GroupLayout coinsLayout = new javax.swing.GroupLayout(coins);
        coins.setLayout(coinsLayout);
        coinsLayout.setHorizontalGroup(
            coinsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(coinsScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        coinsLayout.setVerticalGroup(
            coinsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(coinsScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        holder.add(coins, "coins");

        getContentPane().add(holder, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 0, -1, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void menu_coins_buttonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_menu_coins_buttonMouseClicked
        List<String> coinsData = adminHandler.sp_getMintMiniData(); // get coins data..

        CardLayout cl = (CardLayout) holder.getLayout(); // show coins page
        cl.show(holder, "coins");

        javax.swing.GroupLayout coinsPanelLayout = new javax.swing.GroupLayout(coinsPane);
        coinsPane.setLayout(coinsPanelLayout);

        GroupLayout.ParallelGroup horizontalPG = coinsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING);

        ArrayList<Component> componentList = new ArrayList();
        for (int i = 0; i < coinsData.size(); i++) {
            CoinDetailCard card = new CoinDetailCard(i + 1, coinsData.get(i));
            componentList.add(card);
            horizontalPG.addComponent(card, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE);
        }

        coinsPanelLayout.setHorizontalGroup(
                coinsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(coinsPanelLayout.createSequentialGroup()
                                .addContainerGap().addGroup(horizontalPG)));

        GroupLayout.SequentialGroup verticalSG = coinsPanelLayout.createSequentialGroup();
        for (int i = coinsData.size() - 1; i >= 0; i--) {
            verticalSG.addComponent(componentList.get(i), javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE);
            if (i != 0) {
                verticalSG.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED);
            }
        }

        coinsPanelLayout.setVerticalGroup(
                coinsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(verticalSG));
        
        coinsScrollPane.setViewportView(coinsPane);
    }//GEN-LAST:event_menu_coins_buttonMouseClicked
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel coins;
    private javax.swing.JPanel coinsPane;
    private javax.swing.JScrollPane coinsScrollPane;
    private javax.swing.JPanel holder;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JPanel menu;
    private javax.swing.JButton menu_coins_button;
    private javax.swing.JLabel menu_label;
    // End of variables declaration//GEN-END:variables
}
