#include<stdio.h>
#define M_PI 3.14
int main(){ /*prg. ppal.*/
  int n1, n2, n3, n4, n5, n6,
      result;
    /* E/ */
  printf("Introduce 5 enteros entre espacios\n");
  scanf("%d%d%d%d%d", &n1, &n2, &n3, &n4, &n5);
    /*  /S*/
  printf("%11d\n", n1);
  printf("%11d\n", n2);
  printf("%11d\n", n3);
  printf("%11d\n", n4);
  printf("%11d\n", n5);

  printf("===========\n");
  scanf("%d", &result);
  printf("Salida.\n");
  printf("%11d respuestas\n%11d solucion\n", result, n1+n2+n3+n4+n5);
  return 0;
}
