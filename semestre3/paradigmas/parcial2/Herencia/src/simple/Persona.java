/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package simple;

import java.util.Objects;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Saul
 */
public class Persona extends SerHumano {
    private String nombre;
    private int edad;
    public Persona() {
        super();
        nombre = "";
        edad = 0;
    }
    public Persona(String genero, double peso, double talla, String nombre, 
            int edad) {
        super(genero, peso, talla);
        this.nombre = nombre;
        this.edad = edad;
    }
    public Persona(Persona alguien) {
        super(alguien);
        nombre = alguien.nombre;
        edad = alguien.edad;
    }
    @Override
    public void destruir() {
        super.destruir();
        if(nombre!=null) {
            nombre = null;
            }
        System.gc();
    }
    public void setPersona(String genero, double peso, double talla, String nombre, 
            int edad) {
        setSerHumano(genero, peso, talla);
        this.nombre = nombre;
        this.edad = edad;
    }
    public void respirar(String estado) {
        respirar();
        switch(estado) {
            case "agitado":
                System.out.println("agh, agh, agh");
                break;
            case "relajado":
                System.out.println(".....");
                break;
            case "nervioso":
                System.out.println("agh, agh, agh, agh, agh, agh");
                break;
        }
    }
    public void comer() {
        System.out.println("Comiendo nam, nam, nam");
    }
    @Override
    public boolean equals(Object objeto) {
        // comprobar null
        if(objeto==null) {
            return false;
            }
        // ver si es de tipo Persona
        if(!(objeto instanceof Persona)) {
            return false;
            }
        // mutacion
        Persona temporal = (Persona)objeto;
        // comparar y devolver resultado
        return super.equals(temporal) && nombre.equals(temporal.nombre) &&
                edad == temporal.edad;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 59 * hash + Objects.hashCode(this.nombre);
        hash = 59 * hash + this.edad;
        return hash;
    }
    @Override
    public String toString() {
        return super.toString() + 
                "Nombre: " + nombre + "\n" +
                "Edad  : " + edad + "\n";
    }
    @Override
    public void run() {
        int contador = 0;
        while(true) {
            comer();
            try {
                Thread.sleep(5000);
            } catch (InterruptedException ex) {
                Logger.getLogger(SerHumano.class.getName()).log(
                        Level.SEVERE, null, ex);
            }
            contador++;
            if(contador==3) {
                break;
                }
            }
    }
}
