/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eager;

import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author sauldelaotorres
 */
public class EvaluadorEager {
    /**
     * Por Eager (Estricta)
     * 
     * @param inicio
     * @param fin
     * @return 
     */
    public static List<Integer> eager(int inicio, int fin) {
        List<Integer> lista = new LinkedList<Integer>();
        for(int i=inicio; i<fin; i++) {
            if(esPrimoEspera(i)) {
                lista.add(i);
//                System.out.println(lista);
                }
            }
        return lista;
    }
    private static boolean esPrimoEspera(int numero) {
        boolean esPrimo = true;
        // El 0, 1 y 4 no son primos
        if( numero==0 || numero==1 || numero==4 ) {
            return false;
            }
        for( int x=2; x<numero/2; x++) {
            // Si es divisible por cualquiera de estos números, 
            // NO es primo
            if( numero%x==0 ) {
                return false;
                }
            }
        // Si no se pudo dividir por ninguno de los de arriba, sí es primo
        return esPrimo;
    }
}
