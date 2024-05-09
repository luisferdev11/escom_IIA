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
public class Tortilla {
    private String estado;
    
    public Tortilla(){
        estado="";
    }
    public Tortilla(String estadoTortilla){
        estado=estadoTortilla;
    }
    public Tortilla(Tortilla unaTortilla){
        this.estado=unaTortilla.estado;
    }
    public void destruir(){	
        if(estado!=null){
            estado=null;
        }
        System.gc();
    }
    
    public boolean equals(Tortilla unaTortilla){
        if (unaTortilla==null){
            return false;
        }
        return estado==unaTortilla.estado;
    }
    
    public String to_string(){
        return "la tortilla esta : " + estado + "\n";
    }

    public void cambiarEstado(){
            estado="caliente";
        
    }


    
}
