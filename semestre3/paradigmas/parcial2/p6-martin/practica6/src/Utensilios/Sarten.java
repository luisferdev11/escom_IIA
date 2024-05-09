/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utensilios;

import flauta.*;

/**
 *
 * @author jhona
 */
public class Sarten {
    private String material;
        public Sarten(){
        material="";
    }
    public Sarten(String materialSarten){
        material=materialSarten;
    }
    public Sarten(Sarten unSarten){
        this.material=unSarten.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Sarten unSarten){
        if (unSarten==null){
            return false;
        }
        return material==unSarten.material;
    }
    
    public String to_string(){
        return " el sarten es de  : " + material + "\n";
    }

    public void calentar(Aceite aceite){
        System.out.println("Calentando el " + aceite.to_string());
        aceite.cambiartemperatura();
    }
    public void freir(Flauta flauta){
        System.out.println("Friendo flauta");
        flauta.freir();
       
    }
    
}
