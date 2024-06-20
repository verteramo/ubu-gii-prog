/**
 * @author  Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @brief   Implementación de las funciones FDR_iter y FDR_rec.
 * @version 1.0
 * @date    28/05/2024
 *
 * Enunciado:
 * Se define como factorial decreciente reducido (FDR) de un número num de orden
 * "k" como el cálculo del factorial del número en orden decreciente de valores
 * teniendo en cuenta sólo "k" factores. Por ejemplo, el factorial ordinario de
 * 5 sería 5!=5*4*3*2*1=120, mientras que el FDR de 5 en orden 2 sería  FDR(5,2)
 * = 5*4 = 20.
 *
 * Se solicita implementar y documentar dos funciones FDR_iter y FDR_rec que
 * implemente el cálculo del FDR para en general cualquier valor.  Debe
 * observarse que el valor de "orden" debe ser a lo sumo num (en este caso es el
 * cálculo del factorial ordinario).
 */

#include <stdio.h>
#include <stdlib.h>

/***************************************
 * Definición de tipos de datos
 *
 * No son estrictamente necesarios
 * para la resolución del problema,
 * pero aumentan la legibilidad.
 **************************************/

typedef unsigned int uint_t;
typedef unsigned long long ull_t;

/***************************************
 * Prototipos de funciones
 **************************************/

/**
 * @brief Calcula el FDR de un número num de orden k de manera iterativa.
 * @param num Número al que se le calculará el FDR.
 * @param k Orden del FDR.
 * @return FDR de num de orden k.
 */
ull_t FDR_iter(uint_t num, uint_t k);

/**
 * @brief Calcula el FDR de un número num de orden k de manera recursiva.
 * @param num Número al que se le calculará el FDR.
 * @param k Orden del FDR.
 * @return FDR de num de orden k.
 */
ull_t FDR_rec(uint_t num, uint_t k);

/***************************************
 * Función principal
 **************************************/

int main() {
  int num, k;

  // Ejemplo de uso de la función iterativa
  num = 5;
  k = 2;
  printf("FDR_iter(%d, %d) = %llu\n", num, k, FDR_iter(num, k));
  printf("FDR_rec(%d, %d) = %llu\n", num, k, FDR_rec(num, k));

  num = 6;
  k = 3;
  printf("FDR_iter(%d, %d) = %llu\n", num, k, FDR_iter(num, k));
  printf("FDR_rec(%d, %d) = %llu\n", num, k, FDR_rec(num, k));

  // Ejemplo de uso con error
  num = 5;
  k = 6;
  printf("FDR_iter(%d, %d) = %llu\n", num, k, FDR_iter(num, k));
  printf("FDR_rec(%d, %d) = %llu\n", num, k, FDR_rec(num, k));

  return 0;
}

/***************************************
 * Implementación de funciones
 **************************************/

/**
 * @brief Calcula el FDR de un número num de orden k de manera iterativa.
 * @param num Número al que se le calculará el FDR.
 * @param k Orden del FDR.
 * @return FDR de num de orden k.
 */
ull_t FDR_iter(uint_t num, uint_t k) {
  ull_t result = 1;

  // Si k es menor o igual que num
  if (k <= num) {
    // Se recorren los k primeros números
    for (int i = 0; i < k; i++) {
      // Se multiplica el resultado por el número actual
      result *= (num - i);
    }

    // Se retorna el resultado
    return result;
  }

  // Error si k es mayor que num
  fprintf(stderr, "k (%u) debe ser menor o igual que num (%u)\n", k, num);
  return 0;
}

/**
 * @brief Calcula el FDR de un número num de orden k de manera recursiva.
 * @param num Número al que se le calculará el FDR.
 * @param k Orden del FDR.
 * @return FDR de num de orden k.
 */
ull_t FDR_rec(uint_t num, uint_t k) {
  // Si k es menor o igual que num
  if (k <= num) {
    // Caso base
    if (k == 0) {
      return 1;
    }

    // Llamada recursiva
    // Se decrementan num y k en 1
    return num * FDR_rec(num - 1, k - 1);
  }

  // Error si k es mayor que num
  fprintf(stderr, "k (%u) debe ser menor o igual que num (%u)\n", k, num);
  return 0;
}
