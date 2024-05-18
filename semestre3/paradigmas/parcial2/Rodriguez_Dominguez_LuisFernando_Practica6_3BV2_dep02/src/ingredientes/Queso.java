package ingredientes;

public class Queso {
    private String tipo;

    public Queso(String tipo) {
        this.tipo = tipo;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Queso queso = (Queso) obj;
        return tipo.equals(queso.tipo);
    }

    @Override
    public String toString() {
        return "Queso{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}