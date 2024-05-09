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
public class Cuchillo {
    private String material;
    
        public Cuchillo(){
        material="";
    }
    public Cuchillo(String materialCuchillo){
        material=materialCuchillo;
    }
    public Cuchillo(Cuchillo unCuchillo){
        this.material=unCuchillo.material;
    }
    public void destruir(){	
        if(material!=null){
            material=null;
        }
        System.gc();
    }
    
    public boolean equals(Cuchillo unCuchillo){
        if (unCuchillo==null){
            return false;
        }
        return material==unCuchillo.material;
    }
    public String to_string(){
        return " el cuchillo es de  : " + material + "\n";
    }

    
    public void  picar(Cebolla cebolla){
        System.out.println("Picando cebolla ");
        cebolla.cambiarEstado();
    }
    public void  picar(Aguacate aguacate){
        System.out.println("Picando aguacate ");
        aguacate.cambiarEstado();
    }
    public void  picar(Tomate tomate){
        System.out.println("Picando tomate ");
        tomate.cambiarEstado();
    }
    public void  picar(Papa papa){
        System.out.println("Picando papaa ");
        papa.cambiarForma();
    }
    public void  picar(Cilantro cilantro){
        System.out.println("Picando cilantro ");
        cilantro.cambiarforma();
    }
    public void  picar(Lechuga lechuga){
        System.out.println("Picando lechuga ");
        lechuga.cambiarForma();
    }
    public void  picar(Queso queso){
        System.out.println("Partiendo queso ");
        queso.cambiarEstado();
    }
}
