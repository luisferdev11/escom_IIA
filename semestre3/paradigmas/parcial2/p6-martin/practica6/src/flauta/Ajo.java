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
public class Ajo {
    private String forma;
        public Ajo(){
        forma="";
    }
    public Ajo(String formaAjo){
        forma=formaAjo;
    }
    public Ajo(Ajo unAjo){
        this.forma=unAjo.forma;
    }
    public void destruir(){	
        if(forma!=null){
            forma=null;
        }
        System.gc();
    }
    
    public boolean equals(Ajo unAjo){
        if (unAjo==null){
            return false;
        }
        return forma==unAjo.forma;
    }
    public String to_string(){
        return "el ajo esta : " + forma + "\n";
    }

    
}
