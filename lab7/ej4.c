/**
 * Tipos de datos
 */

// Está definido en el ejercicio 1,
// se vuelve a definir aquí para evidenciar la dependencia
typedef unsigned int uint;

/** Dibuja un rectángulo hueco */
void rhueco(uint filas, uint columnas, char caracter) {
  // Se recorre cada fila
  for (uint fila = 0; fila < filas; fila++) {
    // Se recorre cada columna
    for (uint columna = 0; columna < columnas; columna++) {
      if (fila == 0 || fila == filas - 1 || columna == 0 ||
          columna == columnas - 1) {
        // Si es una fila o columna de los bordes se imprime el caracter
        printf("%c", caracter);
      } else {
        // Si no se imprime un espacio
        printf(" ");
      }
    }
    // Se imprime un salto de línea al final de cada fila
    printf("\n");
  }
}
