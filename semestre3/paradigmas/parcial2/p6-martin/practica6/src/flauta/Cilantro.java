/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package flauta;

/**
 *
 * @author jhona
 */
public class Cilantro {
    private String forma;
        public Cilantro(){
        forma="manojo";
    }
    public Cilantro(String formaCilantro){
        forma=formaCilantro;
    }
    public Cilantro(Cilantro unCilantro){
        this.forma=unCilantro.forma;
    }
    public void destruir(){	
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Cilantro unCilantro){
        if (unCilantro==null){
            return false;
        }
        return forma==unCilantro.forma;
    }
    
    public String to_string(){
        return "el cilantro esta : " + forma + "\n";
    }
    
    public void cambiarforma(){
        if(forma=="manojo"){
            forma="picado";
        }
    }

}
