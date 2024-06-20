#include <stdio.h>

int main() {
  int x1=2, n1=3, x2=2, n2=3;

  x1*=--n1;
  x2*=n2--;

  printf("(3+8/2)*3: %i\n", (3+8/2)*3);
  printf("5!=5: %i\n", (int)(5!=5));
  printf("6+20/2: %i\n", 6+20/2);
  printf("(3+5)*3: %i\n", (3+5)*3);
  printf("x*=--n: %i\n", x1);
  printf("x*=n--: %i\n", x2);
  printf("1==5: %i\n", 1==5);
  printf("6+5/2: %i\n", 6+5/2);
  printf("5+10*3: %i\n", 5+10*3);

  return 0;
}
