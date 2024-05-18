package relleno;

import ingredientes.*;

public class Papa {
    private String tipo;
    private Sal sal;
    private int cantidad;
    private String unidad;
    private boolean pelado;


    public Papa(String tipo, Sal sal, int cantidad, String unidad) {
        this.tipo = tipo;
        this.sal = sal;
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    public void pelar() {
        this.pelado = true;
        System.out.println("Papa ha sido pelada.");
    }

    public void cortar() {
        System.out.println("Papa ha sido cortada.");
    }

    public void cocinar() {
        System.out.println("Cocinando la papa de " + tipo + " con " + sal);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Papa papa = (Papa) obj;
        return cantidad == papa.cantidad && unidad.equals(papa.unidad) && tipo.equals(papa.tipo) && sal.equals(papa.sal);
    }

    @Override
    public String toString() {
        return "Papa{" +
                "tipo='" + tipo + '\'' +
                ", sal=" + sal +
                ", cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}