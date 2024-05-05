package multiple;

import simple.Alumno;

/**
 *
 * @author Saul
 */
public class Becario extends Alumno implements Trabajador {
    private double sueldo;
    public Becario() {
        super();
        sueldo = SUELDO_BASE_BECARIO;
    }
    public Becario(String genero, double peso, double talla,
            String nombre, int edad,
            String boleta,
            double sueldo) {
        super(genero, peso, talla, nombre, edad, boleta);
        this.sueldo = sueldo;
    } 
    public Becario(Becario becario) {
        super(becario);
        sueldo = becario.sueldo;
    }
    @Override
    public void destruir() {
        super.destruir();
    }
    public void setBecario(String genero, double peso, double talla,
            String nombre, int edad,
            String boleta,
            double sueldo) {
        setAlumno(genero, peso, talla, nombre, edad, boleta);
        this.sueldo = sueldo;
    }
    @Override
    public double cobrar() {
        return sueldo;
    }

    @Override
    public void trabajar() {
        System.out.println("Trabajando");
    }

    @Override
    public void trabajar(int horasExtra) {
        trabajar();
        sueldo += ((HORA_TRABAJADA*1.6)*horasExtra);
    }
    public void respirar(String estado, String donde, int latidos) {
        respirar(estado, donde);
        System.out.println("con " + latidos + " por minutro.");
    }
    public void comer(String comida, String donde) {
        comer(comida);
        System.out.println(donde);
    }
    public void estudiar(String unidadDeAprendizaje) {
        estudiar();
        System.out.println(unidadDeAprendizaje);
    }
    public void dormir() {
        System.out.println("Zzzzzz, Zzzzzzzz, Zzzzzz");
    }
    @Override
    public boolean equals(Object objeto) {
        if(objeto==null) {
            return false;
            }
        if(!(objeto instanceof Becario)) {
            return false;
            }
        Becario unBecario = (Becario)objeto;
        return super.equals(unBecario) && sueldo==unBecario.sueldo;
    }

    @Override
    public int hashCode() {
        int hash = 5;
        hash = 29 * hash + (int) (Double.doubleToLongBits(this.sueldo) ^ 
                (Double.doubleToLongBits(this.sueldo) >>> 32));
        return hash;
    }
    @Override
    public String toString() {
        return super.toString() + "Sueldo: " + sueldo + "\n";
    }
}
