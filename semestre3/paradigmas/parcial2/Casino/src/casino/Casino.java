/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package casino;

import java.util.Scanner;
import modelo.JuegoDeDado;

/**
 *
 * @author Saul
 */
public class Casino {

    /**
     * @param args the command line arguments
     */
    public static void main(String [] args) {
        Scanner teclado = new Scanner(System.in);
        System.out.print("Introduzca un numero entero entre 2 y 12: ");
        int numero = teclado.nextInt();
        JuegoDeDado juego = new JuegoDeDado();
        juego.jugarElJuego(numero);
        System.out.print("Introduzca un numero entero entre 2 y 24: ");
        numero = teclado.nextInt();
        JuegoDeDado otroJuego = new JuegoDeDado(12);
        otroJuego.jugarElJuego(numero);
        // detruyendo teclado
        if(teclado!=null) {
            teclado = null;
            }
        // Destruyo juego desde adentro
        juego.destruir();
        // Destruyo juego desde afuera
        if(juego!=null) {
            juego = null;
            }
        // Destruyo otroJuego desde adentro
        otroJuego.destruir();
        // Destruyo otroJuego desde afuera
        if(otroJuego!=null) {
            otroJuego = null;
            }
        // recolectando basura
        System.gc();
    }
    
}
