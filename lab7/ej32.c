/******************************************************************************

                            Exprob_2, Ejercicio 3
      Usando los conceptos vistos en los primeros seis temas
      de la asignatura (tipos de datos, funciones, alternativas
      y recursividad), pero sin usar la funcion printf,
      ni conceptos a partir del tema de bucles.
      
      Completa el siguiente programa para que la salida por pantalla sea:
      
      /salida en pantalla
       R
      RRR
     RRRRR
    RRRRRRR
   RRRRRRRRR
  RRRRRRRRRRR
 RRRRRRRRRRRRR
     #
    ###
   #####
           &

*******************************************************************************/

#include <stdio.h>

void escribeCaracter(char caracter, int veces) {
  if (veces == 0)
    return;
  putchar(caracter);
  escribeCaracter(caracter, veces - 1);
}

void escribeTrianguloIsosceles(char caracter, int lineas, int sangria) {
  if (lineas == 0)
    return;
  escribeTrianguloIsosceles(caracter, lineas - 1, sangria + 1);
  escribeCaracter(' ', sangria);
  escribeCaracter(caracter, (lineas * 2) - 1);
  putchar('\n');
}

int main() {
  escribeTrianguloIsosceles('R', 7, 0);
  escribeTrianguloIsosceles('#', 3, 2);
  escribeTrianguloIsosceles('&', 1, 10);
  return 0;
}
