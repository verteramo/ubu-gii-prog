/*
 | Nombre:   lab24_1.c
 | Sinopsis: Conversión de días, horas, minutos y segundos en segundos.
 | Autor:    Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 | Fecha:    6-mar-2024
 | Versión:  1.0
 | Compil.:  gcc -Wall lab24_1.c -o lab24_1
 | Ejecuc.:  ./lab24_1
*/

/* Directivas del preprocesador */
#include <stdio.h>

/* Definición de constantes */
#define MINUTO 60
#define HORA   MINUTO * MINUTO
#define DIA    HORA * 24

/* Definición de tipos */
typedef unsigned int uint;

/* Definición del módulo ppal */
int main() {

  // Declaración de variables
  uint dias, horas, minutos, segundos, valores;

  // Inicialización de variables
  dias = 0;
  horas = 0;
  minutos = 0;
  segundos = 0;

  // Entrada por terminal
  printf("Conversión de días, horas, minutos y segundos en segundos\n"
         "Introduzca los valores [DD,HH,MM,SS]: ");

  valores = scanf("%u,%u,%u,%u", &dias, &horas, &minutos, &segundos);

  // Salida por terminal
  printf("Se han introducido %u valores: %ud, %uh, %um, %us\n"
         "Equivalen a %u segundos\n"
         "Gracias\n",
         valores,
         dias, horas, minutos, segundos,
         dias * DIA + horas * HORA + minutos * MINUTO + segundos);

  // Salida del programa
  return 0;
}
