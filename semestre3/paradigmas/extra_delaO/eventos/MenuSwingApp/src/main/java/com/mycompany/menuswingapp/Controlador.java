/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.menuswingapp;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.mycompany.menuswingapp.Vista;
import com.mycompany.menuswingapp.modelo.Chivas;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */


public class Controlador {
    private Vista vista;
    private Chivas chivas;

    public Controlador(Vista vista) {
        this.vista = vista;
        this.chivas = new Chivas();
        initController();
    }

    private void initController() {
        vista.getMenuItemPegar().addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                mostrarDialogoPegar();
            }
        });
    }

    private void mostrarDialogoPegar() {
        JOptionPane.showMessageDialog(vista, "Pegando texto de Archivo correctamente", "Pegar", 0);
    }
}

