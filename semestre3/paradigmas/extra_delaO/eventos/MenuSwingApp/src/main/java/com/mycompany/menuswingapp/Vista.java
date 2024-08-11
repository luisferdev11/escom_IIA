/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.menuswingapp;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
import javax.swing.*;
import java.awt.*;
import java.util.List;
import com.mycompany.menuswingapp.modelo.*;

public class Vista extends JFrame {
    private JMenuItem menuItemPegar;
    private JTextArea textAreaJugadores;

    public Vista() {
        // Configuración de la ventana principal
        setTitle("Menu Swing");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 300);
        setLocationRelativeTo(null);

        // Crear barra de menú
        JMenuBar menuBar = new JMenuBar();
        setJMenuBar(menuBar);

        // Crear menús
        JMenu menuArchivo = new JMenu("Archivo");
        menuBar.add(menuArchivo);

        JMenu menuEditar = new JMenu("Editar");
        menuBar.add(menuEditar);

        JMenu menuVentana = new JMenu("Ventana");
        menuBar.add(menuVentana);

        JMenu menuAyuda = new JMenu("Ayuda");
        menuBar.add(menuAyuda);

        // Crear ítem de menú "Pegar"
        menuItemPegar = new JMenuItem("Pegar");
        menuArchivo.add(menuItemPegar);

        // Crear área de texto para mostrar jugadores
        textAreaJugadores = new JTextArea();
        textAreaJugadores.setEditable(false);
        add(new JScrollPane(textAreaJugadores), BorderLayout.CENTER);

        // Mostrar ventana
        setVisible(true);
    }

    public JMenuItem getMenuItemPegar() {
        return menuItemPegar;
    }

    public void mostrarJugadores(List<Jugador> jugadores) {
        StringBuilder sb = new StringBuilder();
        for (Jugador jugador : jugadores) {
            sb.append(jugador.toString()).append("\n");
        }
        textAreaJugadores.setText(sb.toString());
    }
}

