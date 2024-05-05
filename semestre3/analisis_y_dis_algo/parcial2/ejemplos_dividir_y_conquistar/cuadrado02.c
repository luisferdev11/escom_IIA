#include <stdio.h>

void reng(int, int);
void cols(int);

void main()
{
   int i, j;
   puts("Proporciona ancho y largo: ");
   scanf("%d%d", &i, &j);
   reng(i, j);
}

void reng(int i, int j)
{
   int a = 0;
   for( ; a < i; a++)
   {
      cols(j);
      putchar('\n');
   }
}

void cols(int j)
{
   int b = 0;
   for( ; b < j; b++)
       putchar('*');
}
