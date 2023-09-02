import java.util.ArrayList;
import java.util.Scanner;

class Pelota {
    int alto;
    int ancho;
    String color;

    public Pelota(int alto, int ancho, String color) {
        this.alto = alto;
        this.ancho = ancho;
        this.color = color;
    }
}

public class Main {
    public static void main(String[] args) {
        ArrayList<Pelota> pelotas = new ArrayList<>();
        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("1. Crear pelota");
            System.out.println("2. Destruir pelota");
            System.out.println("3. Leer pelotas");
            System.out.println("4. Salir");
            System.out.print("Opción: ");

            int opcion = sc.nextInt();

            switch (opcion) {
                case 1:
                    crearPelota(pelotas, sc);
                    break;
                case 2:
                    destruirPelota(pelotas, sc);
                    break;
                case 3:
                    leerPelotas(pelotas);
                    break;
                case 4:
                    System.out.println("Saliendo...");
                    sc.close();
                    return;
                default:
                    System.out.println("Opción inválida.");
            }
        }
    }

    public static void crearPelota(ArrayList<Pelota> pelotas, Scanner sc) {
        System.out.print("Alto: ");
        int alto = sc.nextInt();

        System.out.print("Ancho: ");
        int ancho = sc.nextInt();

        System.out.print("Color: ");
        String color = sc.next();

        pelotas.add(new Pelota(alto, ancho, color));
    }

    public static void destruirPelota(ArrayList<Pelota> pelotas, Scanner sc) {
        System.out.print("Índice de la pelota a destruir: ");
        int indice = sc.nextInt() - 1;

        if (indice >= 0 && indice < pelotas.size()) {
            pelotas.remove(indice);
        } else {
            System.out.println("Índice no válido.");
        }
    }

    public static void leerPelotas(ArrayList<Pelota> pelotas) {
        for (int i = 0; i < pelotas.size(); i++) {
            Pelota pelota = pelotas.get(i);
            System.out.println("Pelota " + (i + 1) + ":");
            System.out.println("Alto: " + pelota.alto);
            System.out.println("Ancho: " + pelota.ancho);
            System.out.println("Color: " + pelota.color);
        }
    }
}
