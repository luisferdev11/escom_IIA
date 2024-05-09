/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utensilios;

import flauta.Flauta;

/**
 *
 * @author jhona
 */
public class Servilleta {
    private String material;
    public Servilleta(){
        material="";
    }
    public Servilleta(String materialServilleta){
        material=materialServilleta;
    }
    public Servilleta(Servilleta unaServilleta){
        this.material=unaServilleta.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Servilleta unaServilleta){
        if (unaServilleta==null){
            return false;
        }
        return material==unaServilleta.material;
    }
    public String to_string(){
        return " la Servilleta es de  : " + material + "\n";
    }

    
    public void colocar(Flauta flauta){
        System.out.println("colocando faluta en una sevilleta de papel");
        flauta.drenar();
    }
}
