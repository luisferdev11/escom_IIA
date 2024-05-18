package ingredientes;

public class Cilantro {
    private String tipo;
    private boolean cortado;

    public Cilantro(String tipo) {
        this.tipo = tipo;
        this.cortado = false;
    }

    public void cortar() {
        this.cortado = true;
        System.out.println("Cilantro ha sido cortado.");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Cilantro cilantro = (Cilantro) obj;
        return tipo.equals(cilantro.tipo);
    }

    @Override
    public String toString() {
        return "Cilantro{" +
                "tipo='" + tipo + '\'' +
                (cortado ? " (cortado)" : "") +
                '}';
    }
}
