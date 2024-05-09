/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utensilios;

import flauta.Tortilla;

/**
 *
 * @author jhona
 */
public class Comal {
    private String material;
    
        public Comal(){
        material="";
    }
    public Comal(String materialComal){
        material=materialComal;
    }
    public Comal(Comal unComal){
        this.material=unComal.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Comal unComal){
        if (unComal==null){
            return false;
        }
        return material==unComal.material;
    }
    public String to_string(){
        return " el comal es de : " + material + "\n";
    }

    
    public void calentar(Tortilla tortilla){
        System.out.println("Calentando Tortilla");
       tortilla.cambiarEstado();
    }
    
}
