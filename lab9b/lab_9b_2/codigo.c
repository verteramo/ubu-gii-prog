#include <stdio.h>
#include <string.h>

int sumar(int sumnado1, int sumando2);
unsigned char esImPar(int valor);
void escribeHola();

int main() {
  int valor1;
  int valor2;
  int suma;
  int resul;
  unsigned char paridad;

  printf("Teclea los sumandos: ");
  resul = scanf("%d %d", &valor1, &valor2);
  if (resul == 2)
    suma = sumar(valor1, valor2);
  else
    suma = 0;

  if (resul >= 1)
    paridad = esImPar(valor1);
  else
    paridad = -1;

  printf("Suma: %d\n", suma);
  printf("Paridad: %u\n", paridad);
  escribeHola();
  return 0;
}

int sumar(int sumando1, int sumando2) {
  int suma;
  suma = sumando1 + sumando2;
  return suma;
}

unsigned char esImPar(int valor) {
  unsigned char paridad;
  paridad = valor % 2 != 0;
  return paridad;
}

void escribeHola() {
  printf("Hola\n");
  return;
}