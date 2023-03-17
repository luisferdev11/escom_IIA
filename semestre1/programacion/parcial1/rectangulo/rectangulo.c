#include <stdio.h>

// 15. Diseña un algoritmo que muestre en pantalla el siguiente rectángulo:
// * * * * * * * * * * * * * * * * * * * *
// *                                     *
// *                                     *
// *                                     *
// * * * * * * * * * * * * * * * * * * * *
// 16. Modificar el algoritmo anterior, de modo que se lea del teclado una palabra de 5 letras y se
// imprima en el centro del rectángulo.

int main(){
    
    char mipalabra[] = "cacas";

    for (int i = 0; i < 5; i++){

        for (int j = 0; j < 20; j++){

            if(i == 2 && j > 7 && j < 13){
                printf("%c", mipalabra[j - 8]);
            }else if(i == 0 || i == 4 || j == 0 || j == 19){
                printf("*");
            }else{
                printf(" ");
            }
        }

        printf("\n");
    }
    return 0;
}
