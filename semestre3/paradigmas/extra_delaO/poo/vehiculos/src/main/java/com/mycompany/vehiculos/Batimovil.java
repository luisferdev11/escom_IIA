/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class Batimovil extends TanqueDeGuerra {
    public Batimovil(String nombre, String arma) {
        super(nombre, arma);
    }

    @Override
    public void mover() {
        System.out.println(getNombre() + " al rescate para acabar con el joker!!!.");
    }
    
    public void activarModoSigilo() {
        System.out.println(getNombre() + " activa el modo sigilo.");
    }

    @Override
    public String toString() {
        return super.toString() + ", Tipo: Batimovil";
    }
}

