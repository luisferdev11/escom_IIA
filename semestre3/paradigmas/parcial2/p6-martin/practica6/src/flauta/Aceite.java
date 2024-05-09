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
public class Aceite {
    private  String tipo ;
    private String temperatura;
    public Aceite(){
        tipo="";
        temperatura="frio";
    }
    public Aceite(String tipoAceite,String tempeAceite){
        tipo=tipoAceite;
        temperatura=tempeAceite;
    }
    public Aceite(Aceite unAceite){
        this.tipo=unAceite.tipo;
        this.temperatura=unAceite.temperatura;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        if(temperatura!=null){
            temperatura=null;
        }
        System.gc();
    }
    
    public boolean equals(Aceite unAceite){
        if (unAceite==null){
            return false;
        }
        return tipo==unAceite.tipo && temperatura==unAceite.temperatura;
    }
 
    public String to_string(){
        return " El aceite es  : " + tipo + " y esta  " + temperatura +  "\n";
    }
    
    public void cambiartemperatura(){
        if(temperatura=="frio"){
            temperatura="caliente";
        }
    }

}
