#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//#define M_PI 3.14


int main() {
  float radio, radio_2,
        periCircunf, areaCircul,
        areaCuadrIns, periCuadrIns,
        periCuadrCir, areaCuadrCir;

  printf("Radio: ");
  scanf("%f", &radio);

  radio_2 = radio * radio;

  periCircunf = 2.0*M_PI*radio;
  areaCircul = M_PI*radio_2;
  periCuadrCir=8.0*radio;
  areaCuadrCir=4.0*radio_2;
  periCuadrIns=4.0*radio*sqrt(2);
  areaCuadrIns=2.0*radio_2;

  printf("La circunferencia de radio %g\n"
      " mide %10g de perímetro y %10g de área del círculo\n",
      radio, periCircunf, areaCircul);

  printf("El cuadrado circunscrito\n"
      " mide %10g de perímetro y %10g de área\n",
      periCuadrCir, areaCuadrCir);

  printf("El cuadrado inscrito\n"
      " mide %10g de perímetro y %10g de área\n",
      periCuadrIns, areaCuadrIns);

  return 0;
}
