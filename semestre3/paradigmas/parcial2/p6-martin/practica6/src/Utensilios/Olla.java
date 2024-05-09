/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utensilios;
import flauta.*;
import Relleno.*;
/**
 *
 * @author jhona
 */
public class Olla {
    private String material;
    
    public Olla(){
        material="";
    }
    public Olla(String materialOlla){
        material=materialOlla;
    }
    public Olla(Olla unaOlla){
        this.material=unaOlla.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Olla unaOlla){
        if (unaOlla==null){
            return false;
        }
        return material==unaOlla.material;
    }
    public String to_string(){
        return " la olla es de  : " + material + "\n";
    }

    

    
    public void cocinar(Papa papa, Agua agua, Sal sal){
        System.out.println("Cocinando relleno de papa");
        papa.cambiarEstado();
        agua.cambiarEstado();
     
    }
    
    
    public void cocinar(Pollo pollo, Agua agua, Sal sal,
            Ajo ajo, Hoja_laurel hojalaurel){
        System.out.println("Cocinando relleno de pollo");
        agua.cambiarEstado();
        pollo.cambiarEstado();
    }
    public void cocinar(CarneDeRes res, Agua agua, Sal sal,
            Ajo ajo, Hoja_laurel hojalaurel, Cebolla cebolla){
        System.out.println("Cocinando relleno de carne de res");
        res.cambiarEstado();
        agua.cambiarEstado();
    }    
}
