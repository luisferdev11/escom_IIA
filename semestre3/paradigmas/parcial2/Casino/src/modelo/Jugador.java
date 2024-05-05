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
public class Jugador {
    private int miNumero;
    //private Dado dadoUno;
    //private Dado dadoDos;
    private Dado [] dados;
    public Jugador() {
        dados = new Dado[2];
        System.out.println("Creando " + getClass().getName());
    }
    public void tomarLosDados(Dado dadoUno, Dado dadoDos) {
        //dados = new Dado[2];
        //this.dadoUno = dadoUno;
        //this.dadoDos = dadoDos;
        dados[0] = dadoUno;
        dados[1] = dadoDos;
    }
    public void agitarLosDados() {
        System.out.println("Chaca, chaca");
    }
    public void soplarLosDados() {
        System.out.println("fffffff, ffffff");
    }
    public void pedirSuNumero(int numero) {
        miNumero = numero;
    }
    public int lanzarLosDados() {
        //return dadoUno.caerEnCaraSuperior() + dadoDos.caerEnCaraSuperior();
        return dados[0].caerEnCaraSuperior() + dados[1].caerEnCaraSuperior();
    }
    public int getMiNumero() {
        return miNumero;
    }
    public void destruir() {
        System.out.println("Destruyendo desde " + getClass().getName());
        if(dados!=null) {
            dados = null;
            }
        System.gc();
    }
}
