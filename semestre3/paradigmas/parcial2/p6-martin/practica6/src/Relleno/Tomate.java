/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Relleno;

/**
 *
 * @author jhona
 */
public class Tomate {
    public String forma;
    public Tomate(){
        forma="entera";
    }
    public Tomate(String formatomate){
        forma=formatomate;
    }
    public Tomate(Tomate untomate){
        this.forma=untomate.forma;
    }
    public void destruir(){
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Tomate untomate){
        if (untomate==null){
            return false;
        }
        return forma==untomate.forma;
    }
    public String to_string(){
        return " la cebolla esta  : " + forma + "\n";
    }

    
    
    public void cambiarEstado(){
        if(forma=="entera"){
            forma="rodajas";
        }else{
            forma="";
        }
    }
}
