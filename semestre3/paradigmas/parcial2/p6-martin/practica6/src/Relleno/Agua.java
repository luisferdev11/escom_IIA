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
public class Agua {
    private String estado;
        public Agua(){
        estado="fria";
    }
    public Agua(String estadoAgua){
        estado=estadoAgua;
    }
    public Agua(Agua unAgua){
        this.estado=unAgua.estado;
    }
    public void destruir(){	
        if(estado!=null){
            estado=null;
        }
        System.gc();
    }
    
    public boolean equals(Agua unAgua){
        if (unAgua==null){
            return false;
        }
        return estado==unAgua.estado;
    }
    public void cambiarEstado(){
        if(estado=="fria"){
            estado="hirviendo";
        }else{
            estado="fria";
        }
    }
    public String to_string(){
        return " el agua esta : " + estado +"\n";
    }

}
