package ingredientes;

public class Sal {
    private int cantidad;
    private String unidad;

    public Sal(int cantidad, String unidad) {
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Sal sal = (Sal) obj;
        return cantidad == sal.cantidad && unidad.equals(sal.unidad);
    }

    @Override
    public String toString() {
        return "Sal{" +
                "cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}
