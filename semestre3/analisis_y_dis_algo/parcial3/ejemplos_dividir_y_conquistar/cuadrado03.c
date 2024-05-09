#include <stdio.h>

void cuad(int, int, int);

void main()
{
   int i, j;
   puts("Proporciona ancho y altura: ");
   scanf("%d%d", &i, &j);
   cuad(i, j, j);
}

void cuad(int i, int j, int copia_j)
{
   if(i == 0)
      ;
   else
   if(j == 0)
   {
      putchar('\n');
      cuad(i - 1, copia_j, copia_j);
   }
   else
   {
      putchar('*');
      cuad(i, j - 1, copia_j);
   }
}
