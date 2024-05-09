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
public class Queso {
    private String tipo;
    private String forma;
        public Queso(){
        tipo="";
        forma="entero";
    }
    public Queso(String tipoQueso,String formaQueso){
        tipo=tipoQueso;
        forma=formaQueso;
    }
    public Queso(Queso unQueso){
        this.tipo=unQueso.tipo;
        this.forma=unQueso.forma;
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
    
    public boolean equals(Queso unQueso){
        if (unQueso==null){
            return false;
        }
        return tipo==unQueso.tipo && forma==unQueso.forma;
    }
    public String to_string(){
        return " El queso es de tipo  : " + tipo + " y esta  " + forma +  "\n";
    }
    
    public void cambiarEstado(){
        forma="picado";
    }


    
}
