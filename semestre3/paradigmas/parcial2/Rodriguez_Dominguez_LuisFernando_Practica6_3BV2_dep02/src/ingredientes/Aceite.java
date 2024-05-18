package ingredientes;

public class Aceite {
    private String tipo;

    public Aceite(String tipo) {
        this.tipo = tipo;
    }

    public void calentar() {
        System.out.println("Calentando el aceite...");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Aceite aceite = (Aceite) obj;
        return tipo.equals(aceite.tipo);
    }

    @Override
    public String toString() {
        return "Aceite{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}