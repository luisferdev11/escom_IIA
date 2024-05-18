/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package flauta;

import Utensilios.Olla;

/**
 *
 * @author jhona
 */
public class Aguacate extends Olla {
    private String tipo;
    private String forma;
    public Aguacate(){
        tipo="";
        forma="entero";
    }
    public Aguacate(String tipoAguacate,String formaAguacate){
        tipo=tipoAguacate;
        forma=formaAguacate;
    }
    public Aguacate(Aguacate unAguacate){
        this.tipo=unAguacate.tipo;
        this.forma=unAguacate.forma;
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
    
    public boolean equals(Aguacate unAguacate){
        if (unAguacate==null){
            return false;
        }
        return tipo==unAguacate.tipo && forma==unAguacate.forma;
    }
    public String to_string(){
        return " El aguacate es  : " + tipo + " y esta  " + forma +  "\n";
    }
    
    
    
    public void cambiarEstado(){
        forma="rodajas";
    }
    
    

}
