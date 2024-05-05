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
public class JuegoDeDado {
    private Jugador jugador;
    private Dado dadoUno;
    private Dado dadoDos;
    public JuegoDeDado() {
        jugador = new Jugador();
        //dadoUno = new Dado();
        dadoUno = Dado.crearDado();
        //dadoDos = new Dado();
        dadoDos = Dado.crearDado();
    }
    public JuegoDeDado(int numeroCaras) {
        jugador = new Jugador();
        //dadoUno = new Dado(numeroCaras);
        dadoUno = Dado.crearDado(numeroCaras);
        //dadoDos = new Dado(numeroCaras);
        dadoDos = Dado.crearDado(numeroCaras);
    }
    public void jugarElJuego(int numero) {
        //jugador = new Jugador();
        //dadoUno = new Dado();
        //dadoDos = new Dado();
        jugador.tomarLosDados(dadoUno, dadoDos);
        jugador.agitarLosDados();
        jugador.soplarLosDados();
        jugador.pedirSuNumero(numero);
        int numeroGanador = jugador.lanzarLosDados();
        if(numeroGanador==jugador.getMiNumero()) {
            System.out.println("GANASTE con " + numeroGanador);
            }
        else {
            System.out.println("PERDISTE porque " + numeroGanador + 
                    " es distinto de " + jugador.getMiNumero());
            }
    }
    public void destruir() {
        System.out.println("Destruyendo desde " + getClass().getName());
        jugador.destruir();
        if(jugador!=null) {
            jugador = null;
        }
        dadoUno.destruir();
        if(dadoUno!=null) {
            dadoUno = null;
            }
        dadoDos.destruir();
        if(dadoDos!=null) {
            dadoDos = null;
            }
        System.gc();
    }
}
