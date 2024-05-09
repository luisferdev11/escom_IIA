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
public class Plato {
    private String material;
    private String forma;
    
        public Plato(){
        material="";
        forma="";
    }
    public Plato(String materialPlato,String formaPlato){
        material=materialPlato;
        forma=formaPlato;
    }
    public Plato(Plato unPlato){
        this.material=unPlato.material;
        this.forma=unPlato.forma;
    }
    public void destruir(){
        if(material!=null){
            material=null;
        }
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Plato unPlato){
        if (unPlato==null){
            return false;
        }
        return material==unPlato.material && forma==unPlato.forma;
    }
    
    public String to_string(){
        return " el plato es de  : " + material + " y " + forma + " \n";
    }
     
    public void servir(Flauta flauta){
        System.out.println("sirviendo flauta");
    }
    
}
