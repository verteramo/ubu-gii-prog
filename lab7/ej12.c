#include <stdio.h>

typedef enum {
  ENE,
  FEB,
  MAR,
  ABR,
  MAY,
  JUN,
  JUL,
  AGO,
  SEP,
  OCT,
  NOV,
  DIC
} mes_t;

int calculaDiaAno(int, mes_t, int);

int main() {
  printf("El día 22 de abril de 2017 es el día %d del año\n",
         calculaDiaAno(4, ABR, 2017));
  return 0;
}

int calculaDiaAno(int dia, mes_t mes, int ano) {
  int dias = 0;
  switch (mes) {
    case ENE:
      dias = dia;
      break;
    case FEB:
      dias = 31 + dia;
      break;
    case MAR:
      dias = 59 + dia;
      break;
    case ABR:
      dias = 90 + dia;
      break;
    case MAY:
      dias = 120 + dia;
      break;
    case JUN:
      dias = 151 + dia;
      break;
    case JUL:
      dias = 181 + dia;
      break;
    case AGO:
      dias = 212 + dia;
      break;
    case SEP:
      dias = 243 + dia;
      break;
    case OCT:
      dias = 273 + dia;
      break;
    case NOV:
      dias = 304 + dia;
      break;
    case DIC:
      dias = 334 + dia;
      break;
  }

  if (ano % 4 == 0 && mes > FEB) {
    dias++;
  }

  return dias;
}