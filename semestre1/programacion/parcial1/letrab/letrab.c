#include <stdio.h>

// 11. Diseña un algoritmo que muestre en pantalla la letra B con asteriscos:
// *********
// *       *
// *       *
// *********
// *       *
// *       *
// *********

int main()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9 ; j++)
        {
            if ((i == 0 || i == 3 || i == 6) || (j == 0 || j == 8))
            {
                /* code */
                printf("*");
            }else{
                printf(" ");
            }
            
        }
        printf("\n");
    }
    
    return 0;
}
