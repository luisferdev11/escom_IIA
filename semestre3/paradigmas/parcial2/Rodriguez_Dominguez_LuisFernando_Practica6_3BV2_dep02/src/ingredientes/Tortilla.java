package ingredientes;

public class Tortilla {
    private String tipo;
    private String tamaño;

    public Tortilla(String tipo, String tamaño) {
        this.tipo = tipo;
        this.tamaño = tamaño;
    }

    public void calentar() {
        System.out.println("Calentando la tortilla...");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Tortilla tortilla = (Tortilla) obj;
        return tipo.equals(tortilla.tipo) && tamaño.equals(tortilla.tamaño);
    }

    @Override
    public String toString() {
        return "Tortilla{" +
                "tipo='" + tipo + '\'' +
                ", tamaño='" + tamaño + '\'' +
                '}';
    }
}