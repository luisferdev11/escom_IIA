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
public class Lechuga {
    private String tipo;
    private String forma;
        public Lechuga(){
        tipo="";
        forma="entera";
    }
    public Lechuga(String tipoLechuga,String formaLechuga){
        tipo=tipoLechuga;
        forma=formaLechuga;
    }
    public Lechuga(Lechuga unaLechuga){
        this.tipo=unaLechuga.tipo;
        this.forma=unaLechuga.forma;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Lechuga unaLechuga){
        if (unaLechuga==null){
            return false;
        }
        return tipo==unaLechuga.tipo && forma==unaLechuga.forma;
    }
    
    public String to_string(){
        return " La lechuga es  : " + tipo + " y esta  " + forma +  "\n";
    }

    public void cambiarForma(){
        forma="picada";
    }
    
}
