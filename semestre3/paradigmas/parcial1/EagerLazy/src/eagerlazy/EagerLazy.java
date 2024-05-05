/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package eagerlazy;

import eager.EvaluadorEager;
import lazy.EvaluadorLazy;

/**
 * 
 * @author sauldelaotorres
 */
public class EagerLazy {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println(EvaluadorEager.eager(0, 30));
        System.out.println(EvaluadorLazy.lazy(0, 30));
    }
    
}
