package utensilios;

public class Sarten {
    private int diametro;

    public Sarten(int diametro) {
        this.diametro = diametro;
    }

    public void freir() {
        System.out.println("Friendo en el sartén...");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Sarten sarten = (Sarten) obj;
        return diametro == sarten.diametro;
    }

    @Override
    public String toString() {
        return "Sartén{" +
                "diametro=" + diametro +
                '}';
    }
}
