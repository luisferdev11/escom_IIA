package ingredientes;

public class Agua {
    private int cantidad;
    private String unidad;

    public Agua(int cantidad, String unidad) {
        this.cantidad = cantidad;
        this.unidad = unidad;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Agua agua = (Agua) obj;
        return cantidad == agua.cantidad && unidad.equals(agua.unidad);
    }

    @Override
    public String toString() {
        return "Agua{" +
                "cantidad=" + cantidad +
                ", unidad='" + unidad + '\'' +
                '}';
    }
}