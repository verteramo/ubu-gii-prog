/*
 | Nombre:   lab24_2.c
 | Sinopsis: Programa que solicita al usuario una cantidad en euros y ofrece
 |           su valor en dólares, yenes, libras esterlinas y francos suizos.
 | Autor:    Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 | Fecha:    6-mar-2024
 | Versión:  1.0
 | Compil.:  gcc -Wall lab24_2.c -o lab24_2
 | Ejecuc.:  ./lab24_2
 */

/* Directivas del preprocesador */
#include <stdio.h>

/* Definición de constantes */
/* Tasas de cambio con respecto al euro*/
#define USD 1.1239
#define JPY 130.09
#define CHF 1.0425
#define GBP 0.8397
/* Subdivisiones */
#define SUB 100

/* Definición de tipos */
typedef unsigned long ulong;

/* Definición del módulo ppal */
int main() {

  // Declaración de variables
  double eur_entrada;
  ulong eur, usd, jpy, chf, gbp;
  ulong sub_eur, sub_usd, sub_jpy, sub_chf, sub_gbp;

  // Entrada por terminal
  printf("Conversión de divisas\n"
         "Introduzca importe en euros: ");
  scanf("%lf", &eur_entrada);

  // Conversiones
  eur = (ulong)(eur_entrada * SUB);
  usd = (ulong)(eur_entrada * USD * SUB);
  jpy = (ulong)(eur_entrada * JPY * SUB);
  chf = (ulong)(eur_entrada * CHF * SUB);
  gbp = (ulong)(eur_entrada * GBP * SUB);

  // Salida por terminal
  printf("\nConversión directa\n"
      "EUR: %.2f\n"
      "USD: %.2f\n"
      "JPY: %.2f\n"
      "CHF: %.2f\n"
      "GBP: %.2f\n",
      (double)eur / SUB,
      (double)usd / SUB,
      (double)jpy / SUB,
      (double)chf / SUB,
      (double)gbp / SUB);

  // Cálculo de subdivisiones
  sub_eur = eur % SUB;
  sub_usd = usd % SUB;
  sub_jpy = jpy % SUB;
  sub_chf = chf % SUB;
  sub_gbp = gbp % SUB;

  /*
   | Salida por terminal
   | Se calculan las partes enteras de forma directa
   | para evitar la reserva de más memoria,
   | salvo en el caso de cálculos complejos.
  */
  printf("\nConversión con cálculo de subdivisiones\n"
         "EUR: %lu euros y %lu céntimos\n"
         "USD: %lu dólares y %lu centavos\n"
         "JPY: %lu yenes y %lu sen\n"
         "CHF: %lu francos y %lu rappen\n"
         "GBP: %lu libras y %lu peniques\n",
         (eur - sub_eur) / SUB, sub_eur,
         (usd - sub_usd) / SUB, sub_usd,
         (jpy - sub_jpy) / SUB, sub_jpy,
         (chf - sub_chf) / SUB, sub_chf,
         (gbp - sub_gbp) / SUB, sub_gbp);

  // Salida del programa
  return 0;
}
