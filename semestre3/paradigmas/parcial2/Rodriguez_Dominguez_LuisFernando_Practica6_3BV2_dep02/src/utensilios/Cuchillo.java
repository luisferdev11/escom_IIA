package utensilios;

import ingredientes.*;
import relleno.Papa;

public class Cuchillo {
    private String tipo;

    public Cuchillo(String tipo) {
        this.tipo = tipo;
    }

    public void cortar(Object ingrediente) {
        if (ingrediente instanceof Cebolla) {
            ((Cebolla) ingrediente).cortar();
        } else if (ingrediente instanceof Jitomate) {
            ((Jitomate) ingrediente).cortar();
        } else if (ingrediente instanceof Cilantro) {
            ((Cilantro) ingrediente).cortar();
        } else if (ingrediente instanceof Lechuga) {
            ((Lechuga) ingrediente).cortar();
        } else if (ingrediente instanceof Papa) {
            ((Papa) ingrediente).cortar();
        } else if (ingrediente instanceof Aguacate) {
            ((Aguacate) ingrediente).cortar();
        } else {
            System.out.println("No se puede cortar " + ingrediente.getClass().getSimpleName());
        }
    }

    public void pelar(Object ingrediente) {
        if (ingrediente instanceof Papa) {
            ((Papa) ingrediente).pelar();
        } else {
            System.out.println("No se puede pelar " + ingrediente.getClass().getSimpleName());
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Cuchillo cuchillo = (Cuchillo) obj;
        return tipo.equals(cuchillo.tipo);
    }

    @Override
    public String toString() {
        return "Cuchillo{" +
                "tipo='" + tipo + '\'' +
                '}';
    }
}