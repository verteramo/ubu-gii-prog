/**
 * Programa:  Lab7.2
 * Sinopsis:  Programa que imprime por pantalla la forma geométrica seleccionada
 * Autor:     Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * Versión:   1.0
 * Fecha:     10/04/2024
 */

/**
 * Librerías
 */
#include <stdio.h>

/**
 * Constantes
 */
#define FILAS 5
#define COLUMNAS 5
#define CARACTER '*'

/**
 * Tipos de datos
 */
typedef unsigned int uint;

/**
 * Prototipos de funciones
 * Los nombres se construyen de la siguiente forma:
 * - r: rectángulo
 * - t: triángulo
 * - h: hipotenusa
 * Acompañados de su característica:
 * lleno, hueco para rectángulo y triángulo
 * creciente, decreciente para hipotenusa
 */

/**
 * Dibuja un rectángulo lleno
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void rlleno(uint filas, uint columnas, char caracter);

/**
 * Dibuja un rectángulo hueco
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void rhueco(uint filas, uint columnas, char caracter);

/**
 * Dibuja un triángulo rectángulo lleno con hipotenusa creciente
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void tlleno_hcreciente(uint filas, uint columnas, char caracter);

/**
 * Dibuja un triángulo rectángulo hueco con hipotenusa creciente
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void thueco_hcreciente(uint filas, uint columnas, char caracter);

/**
 * Dibuja un triángulo rectángulo lleno con hipotenusa decreciente
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void tlleno_hdecreciente(uint filas, uint columnas, char caracter);

/**
 * Dibuja un triángulo rectángulo hueco con hipotenusa decreciente
 * parámetro filas: número de filas (por valor)
 * parámetro columnas: número de columnas (por valor)
 * parámetro caracter: caracter a imprimir (por valor)
 */
void thueco_hdecreciente(uint filas, uint columnas, char caracter);

/**
 *
 * parámetro filas: número de filas (por referencia)
 * parámetro columnas: número de columnas (por referencia)
 * parámetro caracter: caracter a imprimir (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int cambia_opciones(uint* filas, uint* columnas, char* caracter);

/**
 * Firma del código
 * parámetro nia: NIA del alumno (por referencia)
 * return: valor de la firma
 */
int firma_de_codigo(char* email);

/**
 * Menú
 * parámetro filas: número de filas (por referencia)
 * parámetro columnas: número de columnas (por referencia)
 * parámetro caracter: caracter a imprimir (por referencia)
 * return: 0 en caso de éxito, 1 en caso de error
 */
int menu(uint* filas, uint* columnas, char* caracter);

/**
 * Función principal
 */
int main() {
  // Inicialización de las variables
  uint filas = FILAS;
  uint columnas = COLUMNAS;
  char caracter = CARACTER;

  // Inicio del programa
  return menu(&filas, &columnas, &caracter);
}

/**
 * Implementación de las funciones
 */

/** Menú */
int menu(uint* filas, uint* columnas, char* caracter) {
  char opcion;  // Variable para la opción seleccionada
  do {
    printf(
        "Menú\n"
        "1 - dibuja rectángulo lleno\n"
        "2 - dibuja rectángulo hueco\n"
        "3 - dibuja triángulo rectángulo lleno con hipotenusa creciente\n"
        "4 - dibuja triángulo rectángulo hueco con hipotenusa creciente\n"
        "5 - dibuja triángulo rectángulo lleno con hipotenusa decreciente\n"
        "6 - dibuja triángulo rectángulo hueco con hipotenusa decreciente\n"
        "7 - cambia opciones\n"
        "8 - firma del código\n"
        "0 - salir\n");  // Impresión de opciones

    if (scanf("%c", &opcion) == 1) {  // Lectura y validación de la opción
      switch (opcion) {  // Si la opción es válida se selecciona la acción
                         // correspondiente
        case '1':
          rlleno(*filas, *columnas, *caracter);
          break;
        case '2':
          rhueco(*filas, *columnas, *caracter);
          break;
        case '3':
          tlleno_hcreciente(*filas, *columnas, *caracter);
          break;
        case '4':
          thueco_hcreciente(*filas, *columnas, *caracter);
          break;
        case '5':
          tlleno_hdecreciente(*filas, *columnas, *caracter);
          break;
        case '6':
          thueco_hdecreciente(*filas, *columnas, *caracter);
          break;
        case '7':
          if (cambia_opciones(filas, columnas, caracter)) {
            // Se verifica si hubo algún error al cambiar las opciones
            fprintf(stderr, "error al cambiar las opciones\n");
            return 1;
          }
          break;
        case '8':
          // printf("%d\n", firma_de_codigo("mvp1011@alu.ubu.es"));
          break;
      }
    } else {  // Si hubo algún error en la lectura se sale con error
      fprintf(stderr, "error al leer la opción\n");
      return 1;
    }
  } while (opcion != '0');  // Mientras la opción no sea 0 se sigue en el menú

  return 0;  // Si la opción es 0 se sale sin error
}
