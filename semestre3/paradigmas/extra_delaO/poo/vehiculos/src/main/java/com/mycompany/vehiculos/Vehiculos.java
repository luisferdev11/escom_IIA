/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.vehiculos;

/**
 *
 * @author Rodriguez Dominguez Luis Fernando
 */
public class Vehiculos {

    public static void main(String[] args) {
        Automovil automovil = new Automovil("Automovil de Prueba");
        Motocicleta motocicleta = new Motocicleta("Motocicleta de Prueba");
        TanqueDeGuerra tanque = new TanqueDeGuerra("Tanque de Guerra de Prueba", "Cañón");
        Batimovil batimovil = new Batimovil("Batimovil", "Lanzamisiles");

        Transporte[] transportes = {automovil, motocicleta, tanque, batimovil};

        UpCasting upCasting = new UpCasting();
        upCasting.realizarUpCasting(transportes);
        
        
        automovil.encenderLuces();
        motocicleta.hacerCaballito();
        tanque.disparar();
        batimovil.activarModoSigilo();

        System.out.println("El batimovil y el tanque son iguales? " + batimovil.equals(tanque));
    }
}
