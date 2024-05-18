package relleno;
import ingredientes.*;

public class Pollo {
    private String tipo;
    private Ajo ajo;
    private Cebolla cebolla;
    private Agua agua;
    private Sal sal;
    private int cantidad;
    private String unidad;

    public Pollo(String tipo, Ajo ajo, Cebolla cebolla, Agua agua, Sal sal, int cantidad, String unidad) {
        this.tipo = tipo;
        this.ajo = ajo;
        this.cebolla = cebolla;
        this.agua = agua;
        this.sal = sal;
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    public void cocinar() {
        System.out.println("Cocinando el pollo de " + tipo + " con " + ajo + ", " + cebolla + ", " + agua + ", y " + sal);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Pollo pollo = (Pollo) obj;
        return cantidad == pollo.cantidad && unidad.equals(pollo.unidad) && tipo.equals(pollo.tipo) &&
                ajo.equals(pollo.ajo) && cebolla.equals(pollo.cebolla) && agua.equals(pollo.agua) && sal.equals(pollo.sal);
    }

    @Override
    public String toString() {
        return "Pollo{" +
                "tipo='" + tipo + '\'' +
                ", ajo=" + ajo +
                ", cebolla=" + cebolla +
                ", agua=" + agua +
                ", sal=" + sal +
                ", cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}