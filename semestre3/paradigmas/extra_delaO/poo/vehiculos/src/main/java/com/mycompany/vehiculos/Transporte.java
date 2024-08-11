/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public abstract class Transporte {
    private String nombre;

    public Transporte(String nombre) {
        this.nombre = nombre;
    }

    public String getNombre() {
        return nombre;
    }

    // metodo a redefinir
    public abstract void mover();

    @Override
    public String toString() {
        return "Transporte: " + nombre;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Transporte that = (Transporte) obj;
        return nombre.equals(that.nombre);
    }
}

