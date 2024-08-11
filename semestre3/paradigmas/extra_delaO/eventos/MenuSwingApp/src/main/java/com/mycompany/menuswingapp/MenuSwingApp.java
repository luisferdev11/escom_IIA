/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.menuswingapp;
import javax.swing.*;
import com.mycompany.menuswingapp.Controlador;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class MenuSwingApp {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Vista vista = new Vista();
            new Controlador(vista);
        });
    }
}
