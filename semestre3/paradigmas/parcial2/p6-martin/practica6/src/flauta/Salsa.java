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
public class Salsa {
    private String tipo;
    public Salsa(){
        tipo="";
    }
    public Salsa(String tipoSalsa){
        tipo=tipoSalsa;
    }
    public Salsa(Salsa unaSalsa){
        this.tipo=unaSalsa.tipo;
    }
    public void destruir(){	
        if(tipo!=null){
            tipo=null;
        }
        System.gc();
    }
    
    public boolean equals(Salsa unaSalsa){
        if (unaSalsa==null){
            return false;
        }
        return tipo==unaSalsa.tipo;
    }
    
    public String to_string(){
        return "salsa de : "+ tipo ;
    }

}
