package ingredientes;

public class Cebolla {
    private String tipo;
    private boolean cortado;
    private boolean pelado;

    public Cebolla(String tipo) {
        this.tipo = tipo;
        this.cortado = false;
        this.pelado = false;
    }

    public void cortar() {
        this.cortado = true;
        System.out.println("Cebolla ha sido cortada.");
    }

    public void pelar() {
        this.pelado = true;
        System.out.println("Cebolla ha sido pelada.");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Cebolla cebolla = (Cebolla) obj;
        return tipo.equals(cebolla.tipo);
    }

    @Override
    public String toString() {
        return "Cebolla{" +
                "tipo='" + tipo + '\'' +
                (cortado ? " (cortado)" : "") +
                (pelado ? " (pelado)" : "") +
                '}';
    }
}