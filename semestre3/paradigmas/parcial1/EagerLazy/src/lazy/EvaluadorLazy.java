/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lazy;

import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author sauldelaotorres
 */
public class EvaluadorLazy {
    /**
     * Por Lazy (Perezosa)
     * 
     * @param inicio
     * @param fin
     * @return 
     */
    public static List<Integer> lazy(int inicio, int fin) {
        List<Integer> lista = new LinkedList<Integer>();
        int i = inicio;
        for( ; i<fin; i++) {
            int valor = i;
            i = lazy(valor);
            lista.add(i);
//            System.out.println(lista);
            }
        return lista;
    }
    private static Integer lazy(int numero) {
        int n = numero;
        while( true ) {
            if( esPrimoEspera(n) ) {
                try {
                    Thread.sleep(100); // espera un centesimo de segundo
                } catch(InterruptedException ie) {
                    System.out.println("Excepcion: " + ie);
                }
                break;
                }
            n++;
            }
        return n;
    }
    private static boolean esPrimoEspera(int numero) {
        boolean esPrimo = true;
        // El 0, 1 y 4 no son primos
        if( numero==0 || numero==1 || numero==4 ) {
            esPrimo = false;
            return esPrimo;
            }
        for( int x=2; x<numero/2; x++) {
            // Si es divisible por cualquiera de estos números, 
            // NO es primo
            if( numero%x==0 ) {
                esPrimo = false;
                return esPrimo;
                }
        }
        // Si no se pudo dividir por ninguno de los de arriba, sí es primo
        esPrimo = true;
        return esPrimo;
    }
}
