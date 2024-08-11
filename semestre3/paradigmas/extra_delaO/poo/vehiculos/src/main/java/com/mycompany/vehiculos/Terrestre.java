/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class Terrestre extends Transporte {
    private int ruedas;

    public Terrestre(String nombre, int ruedas) {
        super(nombre);
        this.ruedas = ruedas;
    }

    public int getRuedas() {
        return ruedas;
    }

    @Override
    public void mover() {
        System.out.println(getNombre() + " se mueve sobre la tierra con " + ruedas + " ruedas.");
    }
    
    public void detener() {
        System.out.println(getNombre() + " se detiene.");
    }

    @Override
    public String toString() {
        return super.toString() + ", Terrestre con " + ruedas + " ruedas";
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) return false;
        Terrestre that = (Terrestre) obj;
        return ruedas == that.ruedas;
    }
}

