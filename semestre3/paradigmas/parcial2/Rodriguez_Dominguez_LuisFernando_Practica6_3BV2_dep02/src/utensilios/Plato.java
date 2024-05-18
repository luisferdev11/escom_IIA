package utensilios;

public class Plato {
    private String material;

    public Plato(String material) {
        this.material = material;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Plato plato = (Plato) obj;
        return material.equals(plato.material);
    }

    @Override
    public String toString() {
        return "Plato{" +
                "material='" + material + '\'' +
                '}';
    }
}

