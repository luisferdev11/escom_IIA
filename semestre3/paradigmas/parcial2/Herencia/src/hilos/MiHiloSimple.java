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
public class MiHiloSimple extends Thread {
    private int contador;
    public MiHiloSimple(String nombre) {
        this(10, nombre);
    }
    public MiHiloSimple(int contador, String nombre) {
        super(nombre);
        this.contador = contador;
        //setName(nombre);
    }
    @Override
    public void run() {
        for(int n=contador; n>=0; n--) {
            try {
                Thread.sleep(500);
                System.out.println(getName() + " : " + n );
            } catch (InterruptedException ex) {
                Logger.getLogger(MiHiloSimple.class.getName()).log(
                        Level.SEVERE, null, ex);
            }
            }
    }
}
