/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ec.admin;

/**
 *
 * @author jiajin
 */
public class CoinDetailCard extends javax.swing.JPanel {

    /**
     * Creates new form CoinDetailCard
     */
    public CoinDetailCard() {
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

        pane = new javax.swing.JPanel();
        numbID = new javax.swing.JLabel();
        coin_id_label = new javax.swing.JLabel();
        coin_id = new javax.swing.JLabel();
        secret_label = new javax.swing.JLabel();
        secret = new javax.swing.JLabel();

        numbID.setText("#numb");

        coin_id_label.setText("COIN ID:");

        coin_id.setText("#coinID");
        coin_id.setToolTipText("");

        secret_label.setText("SECRET:");

        secret.setText("#secret");

        javax.swing.GroupLayout paneLayout = new javax.swing.GroupLayout(pane);
        pane.setLayout(paneLayout);
        paneLayout.setHorizontalGroup(
            paneLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(paneLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(numbID)
                .addGap(18, 18, 18)
                .addComponent(coin_id_label)
                .addGap(18, 18, 18)
                .addComponent(coin_id)
                .addGap(55, 55, 55)
                .addComponent(secret_label)
                .addGap(18, 18, 18)
                .addComponent(secret)
                .addContainerGap(132, Short.MAX_VALUE))
        );
        paneLayout.setVerticalGroup(
            paneLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(paneLayout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addGroup(paneLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(numbID)
                    .addComponent(coin_id_label)
                    .addComponent(coin_id)
                    .addComponent(secret_label)
                    .addComponent(secret))
                .addContainerGap(29, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(pane, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(pane, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel coin_id;
    private javax.swing.JLabel coin_id_label;
    private javax.swing.JLabel numbID;
    private javax.swing.JPanel pane;
    private javax.swing.JLabel secret;
    private javax.swing.JLabel secret_label;
    // End of variables declaration//GEN-END:variables
}