/**
 * Tipos de datos
 */

// Está definido en el ejercicio 1,
// se vuelve a definir aquí para evidenciar la dependencia
typedef unsigned int uint;

/**
 * Cambia el número de filas
 * parámetro filas: número de filas (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int cambia_filas(uint* filas);

/**
 * Cambia el número de columnas
 * parámetro columnas: número de columnas (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int cambia_columnas(uint* columnas);

/**
 * Cambia el caracter a imprimir
 * parámetro caracter: caracter a imprimir (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int cambia_caracter(char* caracter);

/** Cambia las opciones */
int cambia_opciones(uint* filas, uint* columnas, char* caracter) {
  char opcion;  // Variable para la opción seleccionada
  do {
    printf(
        "Menú\n"
        "a - cambia número de líneas\n"
        "b - cambia número de columnas\n"
        "c - cambia carácter a escribir\n"
        "0 - volver al menú\n");  // Impresión de opciones

    if (scanf("%c", &opcion) == 1) {  // Lectura y validación de la opción
      switch (opcion) {  // Si la opción es válida se selecciona la acción
                         // correspondiente
        case 'a':
          cambia_filas(filas);
          break;
        case 'b':
          cambia_columnas(columnas);
          break;
        case 'c':
          cambia_caracter(caracter);
          break;
      }
    } else {  // Si hubo algún error en la lectura se sale con error
      return 1;
    }
  } while (opcion != '0');  // Mientras la opción no sea 0 se sigue en el menú

  return 0;  // Si la opción es 0 se sale sin error
}
