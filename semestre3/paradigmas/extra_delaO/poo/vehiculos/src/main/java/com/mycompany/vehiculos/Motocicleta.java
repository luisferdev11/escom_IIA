/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
class Motocicleta extends Terrestre {
    public Motocicleta(String nombre) {
        super(nombre, 2);
    }

    @Override
    public void mover() {
        System.out.println(getNombre() + " se mueve sobre la tierra en dos ruedas la moto.");
    }
    
    public void hacerCaballito() {
        System.out.println(getNombre() + " hace un caballito.");
    }

    @Override
    public String toString() {
        return super.toString() + ", Tipo: Motocicleta";
    }
}

