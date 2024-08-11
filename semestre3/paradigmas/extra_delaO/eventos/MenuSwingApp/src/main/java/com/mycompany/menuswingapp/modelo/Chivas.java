/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.menuswingapp.modelo;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
import java.util.ArrayList;
import java.util.List;

public class Chivas {
    private List<Jugador> jugadores;

    public Chivas() {
        jugadores = new ArrayList<>();
        // Agregar algunos jugadores de ejemplo
        jugadores.add(new Jugador("Tala", 1, "Portero"));
        jugadores.add(new Jugador("Chiquete", 4, "Defensor"));
        jugadores.add(new Jugador("Chicharito", 14, "Delantero"));
    }

    public List<Jugador> getJugadores() {
        return jugadores;
    }
}

