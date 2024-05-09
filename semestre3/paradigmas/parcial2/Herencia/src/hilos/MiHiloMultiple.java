/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hilos;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Saul
 */
public class MiHiloMultiple extends Object implements Runnable {
    private int contador;
    private Thread unHilo;
    public MiHiloMultiple(String nombre) {
        this(10, nombre);
    }
    public MiHiloMultiple(int contador, String nombre) {
        //super(nombre);
        this.contador = contador;
        unHilo = new Thread(this, nombre);
        //setName(nombre);
    }
    public void start() {
        unHilo.start();
    }
    @Override
    public void run() {
        for(int n=contador; n>=0; n--) {
            try {
                Thread.sleep(500);
                System.out.println(unHilo.getName() + " : " + n );
            } catch (InterruptedException ex) {
                Logger.getLogger(MiHiloSimple.class.getName()).log(
                        Level.SEVERE, null, ex);
            }
            }
    }
}
