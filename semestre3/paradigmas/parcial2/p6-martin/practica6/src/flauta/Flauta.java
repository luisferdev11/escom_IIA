/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package flauta;

import Relleno.Tomate;

/**
 *
 * @author jhona
 */
public class Flauta {
    private String estado;
    private String relleno;
    private String toppings;
    public Flauta(){
        estado="";
        relleno="";
        toppings="";
    }
    public Flauta (String tiporelleno, String tipoestado){
        relleno=tiporelleno;
        estado=tipoestado;
    }
    public Flauta (Flauta unaflauta){
        relleno=unaflauta.relleno;
        estado=unaflauta.estado;
        toppings=unaflauta.toppings;
    }
    public boolean equals (Flauta unaflauta){
        if(unaflauta==null){
            return false;
        }
        return unaflauta.estado==estado && unaflauta.relleno==relleno && unaflauta.toppings==toppings;
    }
    public String to_string(){
        if(relleno.compareTo("")>0){
            return "la flauta esta rellena de: " + relleno + " y tiene " + toppings +"\n";
        } else {
            return "la flauta no esta rellena";
            
        }
    }

    public void rellenar(Relleno rellenar, Tortilla tortilla ){
        System.out.println("rellenando tortilla con : " + rellenar.to_string());
        estado="rellena";
        relleno=rellenar.tipoderelleno();
    }
    public void enrollar(){
        System.out.println("enrollando tortilla");
        estado="enrollada";
    }
    public void freir(){
        if(estado=="enrollada"){
            estado="frita";
        }
    }    
    public void asegurar(Palillo palillo){
        System.out.println("Asegurando flauta con un : " + palillo.to_string() );
    }
    
    public void drenar(){
        System.out.println("removiendo exceso de aceite en la flauta");
    }
    public void esparcir(Cilantro cilantro, Queso queso, Lechuga lechuga){
        System.out.println("Esparciendo cilantro, queso y lechuga");
        toppings=toppings.concat(" cilantro, queso, lechuga ");
    }
    public void poner(Tomate tomate,Aguacate aguacate){
        System.out.println("poniendo tomate y aguacate  sobre la flauta");
        toppings=toppings.concat(" tomate , aguacate ");
    }
    public void cubrir(Salsa salsa, Crema crema){
        System.out.println("cubriendo flauta con " + salsa.to_string()+ " y crema");
        toppings=toppings.concat("con crema y " + salsa.to_string() + "\n");
    }
    
}
