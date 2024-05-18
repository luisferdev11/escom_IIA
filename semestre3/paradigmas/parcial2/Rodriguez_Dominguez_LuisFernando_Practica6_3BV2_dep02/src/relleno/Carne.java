package relleno;


import ingredientes.Ajo;
import ingredientes.Cebolla;
import ingredientes.HojaDeLaurel;
import ingredientes.Sal;
import ingredientes.Agua;

public class Carne {
    private String tipo;
    private Cebolla cebolla;
    private Ajo ajo;
    private HojaDeLaurel hojaDeLaurel;
    private Agua agua;
    private Sal sal;
    private int cantidad;
    private String unidad;

    public Carne(String tipo, Cebolla cebolla, Ajo ajo, HojaDeLaurel hojaDeLaurel, Agua agua, Sal sal, int cantidad, String unidad) {
        this.tipo = tipo;
        this.cebolla = cebolla;
        this.ajo = ajo;
        this.hojaDeLaurel = hojaDeLaurel;
        this.agua = agua;
        this.sal = sal;
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    public void cocinar() {
        System.out.println("Cocinando la carne de " + tipo + " con " + cebolla + ", " + ajo + ", " + hojaDeLaurel + ", " + agua + ", y " + sal);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Carne carne = (Carne) obj;
        return cantidad == carne.cantidad && unidad.equals(carne.unidad) && tipo.equals(carne.tipo) &&
                cebolla.equals(carne.cebolla) && ajo.equals(carne.ajo) && hojaDeLaurel.equals(carne.hojaDeLaurel) &&
                agua.equals(carne.agua) && sal.equals(carne.sal);
    }

    @Override
    public String toString() {
        return "Carne{" +
                "tipo='" + tipo + '\'' +
                ", cebolla=" + cebolla +
                ", ajo=" + ajo +
                ", hojaDeLaurel=" + hojaDeLaurel +
                ", agua=" + agua +
                ", sal=" + sal +
                ", cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}