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

public class CarneDeRes {
    private String estado;
    private String forma;
    private String temperatura;
    
    public CarneDeRes(){
        estado="cruda";
        forma="entera";
        temperatura="fria";
    }
    public CarneDeRes(String estadocarne,String formacarne,String temperaturacarne){
        estado=estadocarne;
        forma=formacarne;
        temperatura=temperaturacarne;
    }
    public CarneDeRes(CarneDeRes carne){
        estado=carne.estado;
        forma=carne.forma;
        temperatura=carne.temperatura;
    }
    public void Destruir(){
        if(estado!=null) {
            estado = null;
        }
        if(forma!=null){
            forma=null;
        }
        if (temperatura!=null){
            temperatura=null;
        }
        System.gc();
    }
    
    public boolean equals(CarneDeRes carne){
        if(carne==null){
            return false;
        }
        return estado==carne.estado && forma==carne.forma && temperatura==carne.temperatura;
    }
    public String to_string(){
        return " la carne esta: " + estado + " , " + forma + " de forma con temperatura" + temperatura + "\n";
    }
    
    public void deshebrar(){
        System.out.println("Deshebrando Carne de Res ");
        this.estado="deshebrado";
    }
    public void enfriar(){
        System.out.println("Enfriando Carne de REs");
        this.temperatura="fria";
    }
    
    public void cambiarEstado(){
        if(estado=="cruda"){
            estado="cocida";
        }
    }
}
