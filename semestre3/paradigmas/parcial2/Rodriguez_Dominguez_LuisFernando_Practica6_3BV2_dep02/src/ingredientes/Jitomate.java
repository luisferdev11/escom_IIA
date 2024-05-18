package ingredientes;

public class Jitomate {
    private String tipo;
    private boolean cortado;

    public Jitomate(String tipo) {
        this.tipo = tipo;
    }

    public void cortar() {
        this.cortado = true;
        System.out.println("Jitomate ha sido cortada.");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Jitomate jitomate = (Jitomate) obj;
        return tipo.equals(jitomate.tipo);
    }

    @Override
    public String toString() {
        return "Jitomate{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}
