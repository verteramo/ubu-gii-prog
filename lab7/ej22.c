/******************************************************************************

    Define una funcion, de calculo, en C, que:
        - Reciba valores naturales que representen una cantidad de gradianes
(grados centesimales) minutos centesimales y segundos centesimales,
        - Calcule y devuelva cantidad de radianes que son.
    Si se ejecuta esa funcion con el siguiente programa, la salida por pantalla
    debe ser la de la tabla de abajo.

    /salida
    200grad 0m 0s son 3.14159 radianes
    0grad 20m 0s son 0.00314159 radianes
    0grad 0m 20s son 3.14159e-005 radianes
    200grad 20m 20s son 3,14477 radianes
    0grad 0m 1s son 1.57080e-006 radianes
    63grad 66m 20s son 1 radianes

    Nota: 100s = 1m, 100m = 1grad, 200grad = pi rad.

*******************************************************************************/

#include <math.h>
#include <stdio.h>

double calculaGrados2Radianes(int grad, int min, int seg);

int main() {
  printf("%ugrad %um %us son %g radianes\n", 200, 0, 0,
         calculaGrados2Radianes(200, 0, 0));
  printf("%ugrad %um %us son %g radianes\n", 0, 20, 0,
         calculaGrados2Radianes(0, 20, 0));
  printf("%ugrad %um %us son %g radianes\n", 0, 0, 20,
         calculaGrados2Radianes(0, 0, 20));
  printf("%ugrad %um %us son %g radianes\n", 200, 20, 20,
         calculaGrados2Radianes(200, 20, 20));
  printf("%ugrad %um %us son %g radianes\n", 0, 0, 1,
         calculaGrados2Radianes(0, 0, 1));
  printf("%ugrad %um %us son %g radianes\n", 63, 66, 20,
         calculaGrados2Radianes(63, 66, 20));
  return 0;
}

double calculaGrados2Radianes(int grad, int min, int seg) {
  double radianes = (grad + min / 100.0 + seg / 10000.0) * (acos(-1.0) / 200.0);
  return radianes;
}