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

public class Pollo {
    private String estado;
    private String forma;
    private String temperatura;
    
    public Pollo(){
        estado="crudo";
        forma="entero";
        temperatura="fria";
    }
    public Pollo(String estadopiezapollo,String formapiezapollo,String temperaturapiezapollo){
        estado=estadopiezapollo;
        forma=formapiezapollo;
        temperatura=temperaturapiezapollo;
    }
    public Pollo(Pollo piezapollo){
        estado=piezapollo.estado;
        forma=piezapollo.forma;
        temperatura=piezapollo.temperatura;
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
    
    public boolean equals(Pollo piezapollo){
        if(piezapollo==null){
            return false;
        }
        return estado==piezapollo.estado && forma==piezapollo.forma && temperatura==piezapollo.temperatura;
    }
    public String tostring(){
        return " la piezapollo esta: " + estado + " , " + forma + "de forma con temperatura " + temperatura  +"\n";
    }
    
    public void deshebrar(){
        System.out.println("Deshebrando Pollo ");
        this.forma="deshebrado";
    }
    public void enfriar(){
        System.out.println("Enfriando    Pollo");
        this.temperatura="frio";
    }
    
    

    public void cambiarEstado(){
        if(estado=="crudo"){
            estado="cocido";
        }
    }
}

