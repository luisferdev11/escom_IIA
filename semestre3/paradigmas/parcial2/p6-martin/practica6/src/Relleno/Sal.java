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
public class Sal {
    public String tipo;
        public Sal(){
        tipo="";
    }
    public Sal(String tipoSal){
        tipo=tipoSal;
    }
    public Sal(Sal algunaSal){
        this.tipo=algunaSal.tipo;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        System.gc();
    }
    
    public boolean equals(Sal algunaSal){
        if (algunaSal==null){
            return false;
        }
        return tipo==algunaSal.tipo;
    }
    public String to_string(){
        return "la sal es  : " + tipo + "\n";
    }

}
