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
public class Papa {
    private String tipo;
    private String forma;
    private String estado;
    public Papa(){
        tipo="";
        forma="entera";
        estado="cruda";
    }
    public Papa(String tipoPapa,String formaPapa,String estadoPapa){
        tipo=tipoPapa;
        forma=formaPapa;
        estado=estadoPapa;
    }
    public Papa(Papa unaPapa){
        this.tipo=unaPapa.tipo;
        this.forma=unaPapa.forma;
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
    
    public boolean equals(Papa unaPapa){
        if (unaPapa==null){
            return false;
        }
        return tipo==unaPapa.tipo && forma==unaPapa.forma;
    }    
    public String to_string(){
        return " la papa es tipo : " + tipo + " esta " + forma + " y " + estado + "\n";
    }
    
    public void macerar(){
        System.out.println("macerando papa");
        this.forma="machacada";
    }
    public void escurrir(){
        System.out.println("escurriendo papa");
    }
    
    public void cambiarForma(){
        if(forma=="pelada"){
            forma="rodajas";
        }else if(forma=="entera"){
            forma="pelada";
        }
    }
    public void cambiarEstado(){
        if(estado=="cruda"){
            estado="cocida";
        }
    }
    
}
