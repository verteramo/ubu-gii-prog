/*
 | Nombre:   lab24_3.c
 | Sinopsis: Cálculo del salario neto tras la aplicación
 |           de las correspondientes deducciones al salario bruto.
 | Autor:    Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 | Fecha:    6-mar-2024
 | Versión:  1.0
 | Compil.:  gcc -Wall lab24_3.c -o lab24_3
 | Ejecuc.:  ./lab24_3
 */

/* Directivas del preprocesador */
#include <stdio.h>

/** Definición de tipos */
typedef unsigned short ushort;

/* Definición del módulo ppal */
int main() {

  // Declaración de variables
  double salario_bruto, salario_neto, deducciones;
  float tipo_irpf, tipo_ss;


  // Solicitud del salariuo bruto
  printf("Cálculo del salario neto\n"
         "Introduzca el salario bruto anual [Ej.: 13000]: ");
  scanf("%lf", &salario_bruto);

  // Solicitud del tipo de IRPF
  printf("\nRangos IRPF\n"
         "Hasta 12.450 euros: 19%%.\n"
         "Desde 12.450 euros hasta 20.000 euros: 24%%.\n"
         "Desde 20.001 euros hasta 35.200 euros: 30%%.\n"
         "Desde 35.201 euros hasta 60.000 euros: 37%%.\n"
         "Desde 60.000 euros: 45%%.\n"
         "Introduzca el tipo de IRPF [Ej.: 19]: ");
  scanf("%f", &tipo_irpf);
  tipo_irpf /= 100;

  // Solicitud del tipo de SS
  printf("\nTipos de contrato\n"
         "Contrato temporal:\t6.4%%\n"
         "Contrato indefinido:\t6.35%%\n"
         "Introduzca el tipo SS [Ej.: 6.4]: ");
  scanf("%f", &tipo_ss);
  tipo_ss /= 100;

  // Cálculos
  deducciones = salario_bruto * (tipo_irpf + tipo_ss);
  salario_neto = salario_bruto - deducciones;

  // Salida por terminal
  printf("\nTotal devengado: %.2f euros.\n"
         "Total deducciones: %.2f euros.\n"
         "Líquido a percibir: %.2f euros.\n"
         "Pagas (12): %.2f euros.\n"
         "Pagas (14): %.2f euros.\n",
         salario_bruto, deducciones,
         salario_neto, salario_neto / 12, salario_neto / 14);

  // Salida del programa
  return 0;
}
