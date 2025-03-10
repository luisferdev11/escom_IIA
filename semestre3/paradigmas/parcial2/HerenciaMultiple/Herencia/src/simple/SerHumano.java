package simple;

import java.util.Objects;

/**
 *
 * @author Saul
 */
public class SerHumano extends Object {
    private String genero;
    private double peso;
    private double talla;
    public SerHumano() {
//        genero = "Masculino";
//        peso = 0.0;
//        talla = 0.0;
        this("Masculino", 0.0, 0.0);
    }
    public SerHumano(String genero, double peso, double talla) {
        super();
        this.genero = genero;
        this.peso = peso;
        this.talla = talla;
    }
    public SerHumano(SerHumano humano) {
//        genero = humano.genero;
//        peso = humano.peso;
//        talla = humano.talla;
        this(humano.genero, humano.peso, humano.talla);
    }
    public void destruir() {
        if(genero!=null) {
            genero = null;
            }
        System.gc();
    }
    public void setSerHumano(String genero, double peso, double talla) {
        this.genero = genero;
        this.peso = peso;
        this.talla = talla;
    }
    public void respirar() {
        System.out.println("Respirando ....");
    }
    @Override
    public boolean equals(Object objeto) {
        // 1. preguntar si es null
        if(objeto==null) {
            return false;
            }
        // 2. preguntar tipo
        if(!(objeto instanceof SerHumano)) {
            return false;
            }
        // 3. mutar
        SerHumano temporal = (SerHumano)objeto;
        // 4. comparar y devolver la comparaccion
        return genero.equals(temporal.genero) && peso == temporal.peso &&
                talla == temporal.talla;
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 71 * hash + Objects.hashCode(this.genero);
        hash = 71 * hash + (int) (Double.doubleToLongBits(this.peso) ^ (Double.doubleToLongBits(this.peso) >>> 32));
        hash = 71 * hash + (int) (Double.doubleToLongBits(this.talla) ^ (Double.doubleToLongBits(this.talla) >>> 32));
        return hash;
    }
    @Override
    public String toString() {
        return super.toString() + "\n" +
                "Genero: " + genero + "\n" + 
                "Peso  : " + peso + "\n" +
                "Talla : " + talla + "\n";
    }
}
