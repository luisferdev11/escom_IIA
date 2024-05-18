import ingredientes.*;
import relleno.*;
import utensilios.Cuchillo;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        //mostrarFlujoCompleto();
        interactuarConUsuario();
    }

    public static void interactuarConUsuario() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Preparando una orden de 3 flautas...");

        for (int i = 1; i <= 3; i++) {
            System.out.println("Preparando flauta " + i + " de 3...");
            Flauta flauta = prepararFlauta(scanner);
            System.out.println("Flauta " + i + " preparada: " + flauta);
        }
    }

    private static Flauta prepararFlauta(Scanner scanner) {
        Cuchillo cuchillo = new Cuchillo("afilado");

        System.out.println("Selecciona la tortilla:");
        System.out.println("1. Maíz");
        System.out.println("2. Harina");
        int tipoTortilla = scanner.nextInt();
        Tortilla tortilla = new Tortilla(tipoTortilla == 1 ? "maíz" : "harina", "regular");

        System.out.println("Selecciona el relleno:");
        System.out.println("1. Carne");
        System.out.println("2. Pollo");
        System.out.println("3. Papa");
        int tipoRelleno = scanner.nextInt();
        Object relleno;

        switch (tipoRelleno) {
            case 1:
                Cebolla cebollaCarne = new Cebolla("picada");
                cuchillo.cortar(cebollaCarne);
                relleno = new Carne("res", cebollaCarne, new Ajo(2, "dientes"), new HojaDeLaurel(1, "hoja"), new Agua(1, "litro"), new Sal(1, "cucharadita"), 500, "gramos");
                ((Carne) relleno).cocinar();
                break;
            case 2:
                Ajo ajoPollo = new Ajo(1, "diente");
                Cebolla cebollaPollo = new Cebolla("rebanadas");
                cuchillo.cortar(ajoPollo);
                cuchillo.cortar(cebollaPollo);
                relleno = new Pollo("pechuga", ajoPollo, cebollaPollo, new Agua(1, "litro"), new Sal(1, "cucharadita"), 500, "gramos");
                ((Pollo) relleno).cocinar();
                break;
            case 3:
                Papa papa = new Papa("grande", new Sal(1, "cucharadita"), 500, "gramos");
                cuchillo.pelar(papa);
                relleno = papa;
                ((Papa) relleno).cocinar();
                break;
            default:
                relleno = null;
                break;
        }

        Flauta flauta = new Flauta(tortilla, relleno);


        flauta.setPalillo(new Palillo(5));
        flauta.setAceite(new Aceite("vegetal"));


        flauta.enrollar();
        flauta.freir();

        System.out.println("¿Deseas agregar queso? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            flauta.setQueso(new Queso("Cotija"));
        }

        System.out.println("¿Deseas agregar crema? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            flauta.setCrema(new Crema("Alpura"));
        }

        System.out.println("¿Deseas agregar lechuga? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            Lechuga lechuga = new Lechuga("Romana");
            cuchillo.cortar(lechuga);
            flauta.setLechuga(lechuga);
        }

        System.out.println("¿Deseas agregar jitomate? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            Jitomate jitomate = new Jitomate("Saladet");
            cuchillo.cortar(jitomate);
            flauta.setJitomate(jitomate);
        }

        System.out.println("¿Deseas agregar cebolla? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            Cebolla cebolla = new Cebolla("Blanca");
            cuchillo.cortar(cebolla);
            flauta.setCebolla(cebolla);
        }

        System.out.println("¿Deseas agregar aguacate? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            Aguacate aguacate = new Aguacate("Hass");
            cuchillo.cortar(aguacate);
            flauta.setAguacate(aguacate);
        }

        System.out.println("¿Deseas agregar cilantro? (s/n)");
        if (scanner.next().equalsIgnoreCase("s")) {
            Cilantro cilantro = new Cilantro("Coriandrum");
            cuchillo.cortar(cilantro);
            flauta.setCilantro(cilantro);
        }

        return flauta;
    }

    // Mostrar un flujo completo del programa de manera estática
    public static void mostrarFlujoCompleto() {
        System.out.println("\n--- Flujo completo del programa ---");

        Cuchillo cuchillo = new Cuchillo("afilado");

        Tortilla tortilla1 = new Tortilla("maíz", "regular");
        Cebolla cebollaCarne = new Cebolla("blanca");
        cuchillo.cortar(cebollaCarne);
        Carne carne = new Carne("res", cebollaCarne, new Ajo(2, "dientes"), new HojaDeLaurel(1, "hoja"), new Agua(1, "litro"), new Sal(1, "cucharadita"), 500, "gramos");
        carne.cocinar();
        Flauta flauta1 = new Flauta(tortilla1, carne);
        prepararFlautaCompleta(flauta1);
        prepararIngredientesOpcionales(flauta1, cuchillo);

        Tortilla tortilla2 = new Tortilla("maíz", "regular");
        Ajo ajoPollo = new Ajo(1, "diente");
        Cebolla cebollaPollo = new Cebolla("blanca");
        cuchillo.cortar(ajoPollo);
        cuchillo.cortar(cebollaPollo);
        Pollo pollo = new Pollo("pechuga", ajoPollo, cebollaPollo, new Agua(1, "litro"), new Sal(1, "cucharadita"), 500, "gramos");
        pollo.cocinar();
        Flauta flauta2 = new Flauta(tortilla2, pollo);
        prepararFlautaCompleta(flauta2);
        prepararIngredientesOpcionales(flauta2, cuchillo);

        Tortilla tortilla3 = new Tortilla("maíz", "regular");
        Papa papa = new Papa("grande", new Sal(1, "cucharadita"), 500, "gramos");
        cuchillo.pelar(papa);
        papa.cocinar();
        Flauta flauta3 = new Flauta(tortilla3, papa);
        prepararFlautaCompleta(flauta3);
        prepararIngredientesOpcionales(flauta3, cuchillo);

        System.out.println("Flautas preparadas: ");
        System.out.println(flauta1);
        System.out.println(flauta2);
        System.out.println(flauta3);
    }

    private static void prepararIngredientesOpcionales(Flauta flauta, Cuchillo cuchillo) {
        flauta.setPalillo(new Palillo(5));
        flauta.setAceite(new Aceite("vegetal"));
        flauta.setQueso(new Queso("Cotija"));
        flauta.setCrema(new Crema("Alpura"));

        Lechuga lechuga = new Lechuga("Romana");
        cuchillo.cortar(lechuga);
        flauta.setLechuga(lechuga);

        Jitomate jitomate = new Jitomate("Saladet");
        cuchillo.cortar(jitomate);
        flauta.setJitomate(jitomate);

        Cebolla cebolla = new Cebolla("blanca");
        cuchillo.cortar(cebolla);
        flauta.setCebolla(cebolla);

        Aguacate aguacate = new Aguacate("Hass");
        cuchillo.cortar(aguacate);
        flauta.setAguacate(aguacate);

        Cilantro cilantro = new Cilantro("Coriandrum");
        cuchillo.cortar(cilantro);
        flauta.setCilantro(cilantro);
    }

    private static void prepararFlautaCompleta(Flauta flauta) {
        System.out.println("Enrollando la tortilla con el relleno...");
        flauta.enrollar();
        System.out.println("Friendo la flauta...");
        flauta.freir();
    }
}