/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hilos;

import simple.Alumno;
import simple.Persona;
import simple.SerHumano;

/**
 *
 * @author Saul
 */
public class ProbadorDeHilo {
    public static void main(String[] args) {
        Thread principal = Thread.currentThread();
        System.out.println(principal.getName());
        MiHiloSimple hiloUno = new MiHiloSimple("Hilo uno");
        MiHiloSimple hiloDos = new MiHiloSimple("Hilo dos");
        MiHiloSimple hiloTres = new MiHiloSimple("Hilo tres");
        hiloUno.start();
        hiloDos.start();
        hiloTres.start();
        MiHiloMultiple hiloCuatro = new MiHiloMultiple("Hilo cuatro");
        MiHiloMultiple hiloQuinto = new MiHiloMultiple("Hilo quinto");
        MiHiloMultiple hiloSexto = new MiHiloMultiple("Hilo sexto");
        hiloCuatro.start();
        hiloQuinto.start();
        hiloSexto.start();
        SerHumano unHumano = new SerHumano();
        Persona laura = new Persona();
        Alumno juan = new Alumno();
    }
}
