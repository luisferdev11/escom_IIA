package ingredientes;

public class HojaDeLaurel {
    private int cantidad;
    private String unidad;

    public HojaDeLaurel(int cantidad, String unidad) {
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        HojaDeLaurel hojaDeLaurel = (HojaDeLaurel) obj;
        return cantidad == hojaDeLaurel.cantidad && unidad.equals(hojaDeLaurel.unidad);
    }

    @Override
    public String toString() {
        return "HojaDeLaurel{" +
                "cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}
