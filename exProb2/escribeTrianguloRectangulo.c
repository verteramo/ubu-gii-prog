#include <stdio.h>

int escribeTrianguloRectangulo(char, int, int);

int main() {
  escribeTrianguloRectangulo('R', 7, 0);
  escribeTrianguloRectangulo('#', 3, 2);
  escribeTrianguloRectangulo('#', 1, 6);
  return 0;
}

int escribeTrianguloRectangulo(char caracter, int espacios, int caracteres) {
  printf("%*s\n", espacios - 1, &caracter);
  //printf("%.*c", caracteres + 1, caracter);
  //printf("\n");

  if (espacios > 0) {
    return escribeTrianguloRectangulo(caracter, --espacios, ++caracteres);
  }

  return 0;
}
