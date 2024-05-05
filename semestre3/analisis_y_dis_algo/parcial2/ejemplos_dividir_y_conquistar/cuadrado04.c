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
   if(i > 0)
   {
      cols(j);
      putchar('\n');
      reng(i - 1, j);
   }
}

void cols(int j)
{
   if(j > 0)
   {
      putchar('*');
      cols(j - 1);
   }
}
