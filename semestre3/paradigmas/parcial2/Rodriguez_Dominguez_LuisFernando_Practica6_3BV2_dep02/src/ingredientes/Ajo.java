package ingredientes;

public class Ajo {
    private int cantidad;
    private String unidad;

    public Ajo(int cantidad, String unidad) {
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Ajo ajo = (Ajo) obj;
        return cantidad == ajo.cantidad && unidad.equals(ajo.unidad);
    }

    @Override
    public String toString() {
        return "Ajo{" +
                "cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}
