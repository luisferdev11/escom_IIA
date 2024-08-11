/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.menuswingapp.modelo;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class Jugador {
    private String nombre;
    private int numero;
    private String posicion;

    public Jugador(String nombre, int numero, String posicion) {
        this.nombre = nombre;
        this.numero = numero;
        this.posicion = posicion;
    }

    public String getNombre() {
        return nombre;
    }

    public int getNumero() {
        return numero;
    }

    public String getPosicion() {
        return posicion;
    }

    @Override
    public String toString() {
        return numero + " - " + nombre + " (" + posicion + ")";
    }
}
