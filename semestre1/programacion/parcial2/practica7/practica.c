#include <stdio.h>

int main() {
    int opcion;
    float falda = 169.9, pantalon = 270, camisa = 150, blusa = 199.9, gorra = 100;
    float total = 0;
    int cantidadF = 0, cantidadP = 0, cantidadC = 0, cantidadB = 0, cantidadG = 0;

    do {
        printf("Elige la prenda que deseas comprar\n");
        printf("1. falda - $169.9\n");
        printf("2. pantalon - $270.0\n");
        printf("3. camisa - $150.0\n");
        printf("4. blusa - $199.9\n");
        printf("5. gorra - $100.0\n");
        printf("6. finalizar compra\n");
        printf("----------------------------------\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Seleccione la cantidad de faldas: \n");
                scanf("%d", &cantidadF);
                total += cantidadF * falda;
                break;
            case 2:
                printf("Seleccione la cantidad de pantalones: \n");
                scanf("%d", &cantidadP);
                total += cantidadP * pantalon;
                break;
            case 3:
                printf("Seleccione la cantidad de camisas: \n");
                scanf("%d", &cantidadC);
                total += cantidadC * camisa;
                break;
            case 4:
                printf("Seleccione la cantidad de blusas: \n");
                scanf("%d", &cantidadB);
                total += cantidadB * blusa;
                break;
            case 5:
                printf("Seleccione la cantidad de gorras: \n");
                scanf("%d", &cantidadG);
                total += cantidadG * gorra;
                break;
            default:
                if (opcion != 6)
                    printf("La opcion no es valida.\n");
                break;
        }
    } while (opcion != 6);

    printf("Usted debe pagar %.2f \n", total);

    return 0;
}

