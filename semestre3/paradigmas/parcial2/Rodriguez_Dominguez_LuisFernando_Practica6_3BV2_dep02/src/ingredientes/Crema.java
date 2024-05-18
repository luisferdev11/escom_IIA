package ingredientes;

public class Crema {
    private String tipo;

    public Crema(String tipo) {
        this.tipo = tipo;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Crema crema = (Crema) obj;
        return tipo.equals(crema.tipo);
    }

    @Override
    public String toString() {
        return "Crema{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}

