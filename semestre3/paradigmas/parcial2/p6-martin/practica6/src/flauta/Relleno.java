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
import flauta.*;
import Relleno.*;
public class Relleno {
    private String tipo;
        public Relleno(){
        tipo="";
    }
    public Relleno(String tipoTipoderelleno){
        tipo=tipoTipoderelleno;
    }
    public Relleno(Papa unapapa){
        tipo="papa";
    }
    public Relleno(CarneDeRes unares){
        tipo="res";
    }
    public Relleno(Pollo unpollo){
        tipo="pollo";
    }
    
    public Relleno(Relleno unTipoderelleno){
        this.tipo=unTipoderelleno.tipo;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        System.gc();
    }
    
    public boolean equals(Relleno unTipoderelleno){
        if (unTipoderelleno==null){
            return false;
        }
        return tipo==unTipoderelleno.tipo;
    }
    
    public String to_string(){
        return " relleno de : " + tipo + "\n"; 
    }
    public String tipoderelleno(){
        return tipo;
    }
}

    
    

