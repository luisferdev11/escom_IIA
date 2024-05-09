#include <stdio.h>

void cuad(int, int);

void main()
{
   int i, j;
   puts("Proporciona ancho y largo: ");
   scanf("%d%d", &i, &j);
   cuad(i, j );
}

void cuad(int i, int j)
{
   int a = 0, b = 0;
   for( ; a < i; a++)
   {
      for(b = 0 ; b < j; b++)
          putchar('*');
      putchar('\n');
   }
}
