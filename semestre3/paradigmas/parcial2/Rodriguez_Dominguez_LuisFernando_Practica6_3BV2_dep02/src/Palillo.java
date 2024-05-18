public class Palillo {
    private int longitud;

    public Palillo(int longitud) {
        this.longitud = longitud;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Palillo palillo = (Palillo) obj;
        return longitud == palillo.longitud;
    }

    @Override
    public String toString() {
        return "Palillo{" +
                "longitud=" + longitud +
                '}';
    }
}
