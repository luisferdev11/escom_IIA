package utensilios;

public class ToallaDePapel {
    private String marca;

    public ToallaDePapel(String marca) {
        this.marca = marca;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        ToallaDePapel toallaDePapel = (ToallaDePapel) obj;
        return marca.equals(toallaDePapel.marca);
    }

    @Override
    public String toString() {
        return "ToallaDePapel{" +
                "marca='" + marca + '\'' +
                '}';
    }
}
