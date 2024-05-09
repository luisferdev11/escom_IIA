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
public class Palillo {
    private String material;
        public Palillo(){
        material="";
    }
    public Palillo(String materialPalillo){
        material=materialPalillo;
    }
    public Palillo(Palillo unPalillo){
        this.material=unPalillo.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Palillo unPalillo){
        if (unPalillo==null){
            return false;
        }
        return material==unPalillo.material;
    }
    
    public String to_string(){
        return  "palillo de: " + material +"\n";    
}

    
}
