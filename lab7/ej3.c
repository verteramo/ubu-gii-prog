/**
 * Tipos de datos
 */

// Está definido en el ejercicio 1,
// se vuelve a definir aquí para evidenciar la dependencia
typedef unsigned int uint;

/**
 * Cambia el número de columnas
 * parámetro columnas: número de columnas (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int cambia_columnas(uint* columnas) {
  printf("nuevo número de columnas: ");
  return scanf("%u", columnas);
}
