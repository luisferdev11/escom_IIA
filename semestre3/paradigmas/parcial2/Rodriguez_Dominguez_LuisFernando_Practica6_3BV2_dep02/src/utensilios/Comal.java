package utensilios;

public class Comal {
    private int tamaño;

    public Comal(int tamaño) {
        this.tamaño = tamaño;
    }

    public void calentar() {
        System.out.println("Calentando en el comal...");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Comal comal = (Comal) obj;
        return tamaño == comal.tamaño;
    }

    @Override
    public String toString() {
        return "Comal{" +
                "tamaño=" + tamaño +
                '}';
    }
}
