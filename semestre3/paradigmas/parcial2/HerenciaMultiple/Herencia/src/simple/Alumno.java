/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package simple;

import java.util.Objects;

/**
 *
 * @author Saul
 */
public class Alumno extends Persona {
    private String boleta;
    public Alumno() {
        super();
        boleta = "";
    }
    public Alumno(String genero, double peso, double talla, 
            String nombre, int edad, String boleta) {
        super(genero, peso, talla, nombre, edad);
        this.boleta = boleta;
    }
    public Alumno(Alumno alguien) {
        super(alguien);
        boleta = alguien.boleta;
    }
    @Override
    public void destruir() {
        super.destruir();
        if(boleta!=null) {
            boleta = null;
        }
        System.gc();
    }
    public void setAlumno(String genero, double peso, double talla, 
            String nombre, int edad, String boleta) {
        setPersona(genero, peso, talla, nombre, edad);
        this.boleta = boleta;
    }
    public void respirar(String estado, String donde) {
        respirar(estado);
        System.out.println(donde);
    }
    public void comer(String comida) {
        comer();
        System.out.println(comida);
    }
    public void estudiar() {
        System.out.println("Estudiando");
    }
    @Override
    public boolean equals(Object objeto) {
        if(objeto==null) {
            return false;
            }
        if(!(objeto instanceof Persona)) {
            return false;
            }
        Alumno unAlumno = (Alumno)objeto;
        return super.equals(unAlumno) && boleta.equals(unAlumno.boleta);
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 13 * hash + Objects.hashCode(this.boleta);
        return hash;
    }
    public String toString() {
        return super.toString() + "Boleta: " + boleta + "\n";
    }
}
