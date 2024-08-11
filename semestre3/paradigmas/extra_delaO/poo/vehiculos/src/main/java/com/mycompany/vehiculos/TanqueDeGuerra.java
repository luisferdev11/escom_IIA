/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class TanqueDeGuerra extends Terrestre {
    private String arma;

    public TanqueDeGuerra(String nombre, String arma) {
        super(nombre, 8);
        this.arma = arma;
    }

    public String getArma() {
        return arma;
    }

    @Override
    public void mover() {
        System.out.println(getNombre() + " se mueve sobre la tierra listo para dar de baja a los contrarios.");
    }

    // Método adicional propio de la clase TanqueDeGuerra
    public void disparar() {
        System.out.println(getNombre() + " dispara su " + arma + ".");
    }

    @Override
    public String toString() {
        return super.toString() + ", Tipo: Tanque de Guerra, Arma: " + arma;
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) return false;
        TanqueDeGuerra that = (TanqueDeGuerra) obj;
        return arma.equals(that.arma);
    }
}
