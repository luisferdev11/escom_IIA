package ingredientes;

public class Lechuga {
    private String tipo;
    private boolean cortado;

    public Lechuga(String tipo) {
        this.tipo = tipo;
        this.cortado = false;
    }

    public void cortar() {
        this.cortado = true;
        System.out.println("Lechuga ha sido cortada.");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Lechuga lechuga = (Lechuga) obj;
        return tipo.equals(lechuga.tipo);
    }

    @Override
    public String toString() {
        return "Lechuga{" +
                "tipo='" + tipo + '\'' +
                (cortado ? " (cortado)" : "") +
                '}';
    }
}