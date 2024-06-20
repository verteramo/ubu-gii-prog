#include<stdio.h>
                /*prg. ppal.*/
int main(){
  int n1, n2, n3, n4, n5, n6,
      result;
                /* E/ */
  printf("Introduce 5 enteros entre espacios\n");
 scanf("%i %i %i %i %i", &n1, &n2, &n3, &n4, &n5);
                /*  /S*/
  printf("%11d\n", n1);
  printf("%11d\n", n2);
  printf("%11d\n", n3);
  printf("%11d\n", n4);
  printf("%11d\n", n5);
                /* E/ */
  printf("===========\n");
  scanf("%d", &result);
                /* /S */
  printf("%11d respuestas\n%11d solucion\n", result, n1+n2+n3+n4+n5);
  return 0;
}
