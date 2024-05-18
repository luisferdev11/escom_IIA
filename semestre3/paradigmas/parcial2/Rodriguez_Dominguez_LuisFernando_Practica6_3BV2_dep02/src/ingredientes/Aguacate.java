package ingredientes;

public class Aguacate {
    private String tipo;
    private boolean cortado;

    public Aguacate(String tipo) {
        this.tipo = tipo;
    }

    public void cortar() {
        this.cortado = true;
        System.out.println("El aguacate ha sido cortada.");
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Aguacate aguacate = (Aguacate) obj;
        return tipo.equals(aguacate.tipo);
    }

    @Override
    public String toString() {
        return "Aguacate{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}