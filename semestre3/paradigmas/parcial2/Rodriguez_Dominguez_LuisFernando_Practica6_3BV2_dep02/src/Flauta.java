import ingredientes.*;
import java.util.Objects;

public class Flauta {
    private Tortilla tortilla;
    private Object relleno; // Puede ser Carne, Pollo o Papa
    private Palillo palillo;
    private Aceite aceite;
    private Queso queso;
    private Crema crema;
    private Lechuga lechuga;
    private Jitomate jitomate;
    private Cebolla cebolla;
    private Aguacate aguacate;
    private Cilantro cilantro;

    // Constructor mínimo
    public Flauta(Tortilla tortilla, Object relleno) {
        this.tortilla = tortilla;
        this.relleno = relleno;
    }

    // Setters para los ingredientes opcionales
    public void setPalillo(Palillo palillo) { this.palillo = palillo;
        System.out.println("Agregando palillo");}
    public void setAceite(Aceite aceite) { this.aceite = aceite;
        System.out.println("Agregando Flauta en aceite");}
    public void setQueso(Queso queso) { this.queso = queso;
    System.out.println("Agregando queso a la flauta");}
    public void setCrema(Crema crema) { this.crema = crema;
    System.out.println("Agregando crema a la flauta");}
    public void setLechuga(Lechuga lechuga) { this.lechuga = lechuga;
    System.out.println("Agregando lechuga a la flauta");}
    public void setJitomate(Jitomate jitomate) { this.jitomate = jitomate;
    System.out.println("Agregando jitomate a la flauta");}
    public void setCebolla(Cebolla cebolla) { this.cebolla = cebolla;
    System.out.println("Agregando cebolla a la flauta");}
    public void setAguacate(Aguacate aguacate) { this.aguacate = aguacate;
    System.out.println("Agregando aguacate a la flauta");}
    public void setCilantro(Cilantro cilantro) { this.cilantro = cilantro;
    System.out.println("Agregando cilantro a la flauta");}

    // Métodos para preparar la flauta
    public void enrollar() {
        System.out.println("Enrollando la tortilla con el relleno...");
    }

    public void freir() {
        System.out.println("Friendo la flauta...");
        System.out.println("Flauta Frita");
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Flauta flauta = (Flauta) obj;
        return tortilla.equals(flauta.tortilla) && relleno.equals(flauta.relleno) &&
                Objects.equals(palillo, flauta.palillo) && Objects.equals(aceite, flauta.aceite) &&
                Objects.equals(queso, flauta.queso) && Objects.equals(crema, flauta.crema) &&
                Objects.equals(lechuga, flauta.lechuga) && Objects.equals(jitomate, flauta.jitomate) &&
                Objects.equals(cebolla, flauta.cebolla) && Objects.equals(aguacate, flauta.aguacate) &&
                Objects.equals(cilantro, flauta.cilantro);
    }

    @Override
    public String toString() {
        return "Flauta{" +
                "tortilla=" + tortilla +
                ", relleno=" + relleno +
                ", palillo=" + palillo +
                ", aceite=" + aceite +
                ", queso=" + queso +
                ", crema=" + crema +
                ", lechuga=" + lechuga +
                ", tomate=" + jitomate +
                ", cebolla=" + cebolla +
                ", aguacate=" + aguacate +
                ", cilantro=" + cilantro +
                '}';
    }
}
