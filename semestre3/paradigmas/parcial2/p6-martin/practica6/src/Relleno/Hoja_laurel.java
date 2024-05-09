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
public class Hoja_laurel {
    private String forma;
        public Hoja_laurel(){
        forma="";
    }
    public Hoja_laurel(String formaHoja_laurel){
        forma=formaHoja_laurel;
    }
    public Hoja_laurel(Hoja_laurel unaHoja_laurel){
        this.forma=unaHoja_laurel.forma;
    }
    public void destruir(){
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Hoja_laurel unaHoja_laurel){
        if (unaHoja_laurel==null){
            return false;
        }
        return forma==unaHoja_laurel.forma;
    }
    public String to_string(){
        return " la hoja  esta : " + forma + "\n";
    }

}
