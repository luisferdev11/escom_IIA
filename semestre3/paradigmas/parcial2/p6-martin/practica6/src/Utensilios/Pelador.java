/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utensilios;

import Relleno.Papa;

/**
 *
 * @author jhona
 */
public class Pelador {
    private String material;
    
        public Pelador(){
        material="";
    }
    public Pelador(String materialPelador){
        material=materialPelador;
    }
    public Pelador(Pelador unPelador){
        this.material=unPelador.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Pelador unPelador){
        if (unPelador==null){
            return false;
        }
        return material==unPelador.material;
    }
    
    public String to_string(){
        return " el pelador es de  : " + material + "\n";
    }
    
    public void pelar(Papa papa){
            System.out.println("pelando papa");
            papa.cambiarEstado();
    }
    
}
