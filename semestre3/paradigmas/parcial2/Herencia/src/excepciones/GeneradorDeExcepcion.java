/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package excepciones;

/**
 *
 * @author Saul
 */
public class GeneradorDeExcepcion {
    public static void main(String[] args) {
        Aritmetica aritmetica = new Aritmetica();
        int a = 10, b = 0, c;
        try {
            c = aritmetica.dividir(a, b);
        } catch(ArithmeticException ae) {
            System.out.println(ae);
            //ae.printStackTrace(flujo);
        }
        System.out.println("Terminacion correctamente.");
    }
}
