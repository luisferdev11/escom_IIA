/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modelo;

/**
 *
 * @author Saul
 */
public class Dado {
    private final int NUMERO_CARAS;
    private int caraSuperior;
    private Dado() {
        NUMERO_CARAS = 6;
        caraSuperior = 0;
        System.out.println("Creando " + getClass().getName());
    }
    private Dado(int numeroCaras) {
        NUMERO_CARAS = numeroCaras;
        caraSuperior = 0;
        System.out.println("Creando " + getClass().getName());
    }
    public static Dado crearDado() {
        return new Dado();
    }
    public static Dado crearDado(int numeroCaras) {
        return new Dado(numeroCaras);
    }
    private void mostrarCaraSuperior() {
        System.out.println(caraSuperior);
    }
    public int caerEnCaraSuperior() {
        caraSuperior = (int)(Math.random()*NUMERO_CARAS) + 1;
        mostrarCaraSuperior();
        return caraSuperior;
    }
    public void destruir() {
        System.out.println("Nada que destruir desde " + getClass().getName());
    }
}
