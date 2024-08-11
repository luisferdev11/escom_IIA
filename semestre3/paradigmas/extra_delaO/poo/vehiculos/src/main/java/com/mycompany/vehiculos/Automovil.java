/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
class Automovil extends Terrestre {
    public Automovil(String nombre) {
        super(nombre, 4);
    }

    @Override
    public void mover() {
        System.out.println(getNombre() + " se mueve sobre la tierra el auto.");
    }
    
    public void encenderLuces() {
        System.out.println(getNombre() + " enciende las luces.");
    }

    @Override
    public String toString() {
        return super.toString() + ", Tipo: Automovil";
    }
}

