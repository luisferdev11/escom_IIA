package utensilios;

public class Olla {
    private int capacidad;

    public Olla(int capacidad) {
        this.capacidad = capacidad;
    }

    public void cocinar() {
        System.out.println("Cocinando en la olla...");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Olla olla = (Olla) obj;
        return capacidad == olla.capacidad;
    }

    @Override
    public String toString() {
        return "Olla{" +
                "capacidad=" + capacidad +
                '}';
    }
}