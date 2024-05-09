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
public class Crema {
    private String tipo;
        public Crema(){
        tipo="";
    }
    public Crema(String tipoCrema){
        tipo=tipoCrema;
    }
    public Crema(Crema unaCrema){
        this.tipo=unaCrema.tipo;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        System.gc();
    }
    
    public boolean equals(Crema unaCrema){
        if (unaCrema==null){
            return false;
        }
        return tipo==unaCrema.tipo;
    }
    public String to_string(){
        return "la crema es de  : " + tipo + "\n";
    }

    
}
