#include <stdio.h>

/**
 * Constantes
 */
#define NIA_LEN 8

/**
 * Tipos de datos
 */
// Está definido en el ejercicio 1,
// se vuelve a definir aquí para evidenciar la dependencia
typedef unsigned int uint;
typedef char nia_t[NIA_LEN];

/** Firma del código */
int firma_de_codigo(char* email) {
  nia_t nia;
  uint suma = 0;

  sscanf(email, "%7s", nia);

  for (int i = 0; i < NIA_LEN - 1; i++) {
    suma += (int)nia[i];
  }

  return suma % 64;
}

int main() {
  printf("Firma: %d\n", firma_de_codigo("mvp1011@alu.ubu.es"));
  return 0;
}

// mvp1011
// 109 + 118 + 112 + 49 + 48 + 49 + 49
// 22