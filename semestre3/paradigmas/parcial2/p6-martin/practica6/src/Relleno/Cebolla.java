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
public class Cebolla {
    private String tipo;
    private String forma;
    
    public Cebolla(){
        tipo="";
        forma="entera";
    }
    public Cebolla(String tipocebolla,String formacebolla){
        tipo=tipocebolla;
        forma=formacebolla;
    }
    public Cebolla(Cebolla unacebolla){
        this.tipo=unacebolla.tipo;
        this.forma=unacebolla.forma;
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
    
    public boolean equals(Cebolla unacebolla){
        if (unacebolla==null){
            return false;
        }
        return tipo==unacebolla.tipo && forma==unacebolla.forma;
    }
    public String to_string(){
        return " la cebolla tipo : " + tipo + " y esta " + forma + "\n";
    }
    
    
    
    public void cambiarEstado(){
        if(forma=="entera"){
            forma="rodajas";
        }else{
            forma="";
        }
    }
    
    
}
