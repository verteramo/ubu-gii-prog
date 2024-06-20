#include <stdio.h>
#include <math.h>

void clean() {
  for(int c = getchar(); c != '\n' && c != EOF; c = getchar());
}

int escribeNatural(unsigned n) {
  return printf("%u", n);
}

int pideAncho(int *w) {
  return scanf("%d", w) > 0;
}

float calculaAreaCirculo(unsigned radio) {
  return M_PI * pow(radio, 2);
}

int main() {
  int ancho, leido;

  printf("escribeNatural(100): ");
  escribeNatural(100);

  printf("\n\n");

  printf("pideAncho [10]: ");
  leido = pideAncho(&ancho);
  printf("ancho: %d leído: %d\n", ancho, leido);
  clean();

  printf("pideAncho [20 10]: ");
  leido = pideAncho(&ancho);
  printf("ancho: %d leído: %d\n", ancho, leido);
  clean();

  printf("pideAncho [A 10]: ");
  leido = pideAncho(&ancho);
  printf("ancho: %d leído: %d\n", ancho, leido);
  clean();

  printf("\n\n");

  printf("calculaAreaCirculo(2): %.2f\n", calculaAreaCirculo(2));
  printf("calculaAreaCirculo(5): %.2f\n", calculaAreaCirculo(5));

  return 0;
}
