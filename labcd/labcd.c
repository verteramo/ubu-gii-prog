/**
 * @file    labcd.c
 * @brief   Estadísticas de usuarios (16-19 años)
 *          que se conectan a Internet a diario
 * @version 1.0
 * @date    22/05/2024
 * @autor   Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @compile gcc -Wall -o labcd labcd.c
 * @execute ./labcd
 */

/********************************************************
 * Librerías
 *******************************************************/

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************
 * Literales auxiliares
 *******************************************************/

/** Limpiar la consola */
#ifdef _WIN32
#define clear() system("cls")
#else  // POSIX
#define clear() system("clear")
#endif

/** End of line */
#define EOL '\n'

/** End of string */
#define EOS '\0'

/** Salto de línea */
#define NEWLINE "\n"

/** Formato de mensaje de error de archivo */
#define FILE_ERROR "Error al abrir el fichero '%s' (%d: %s).\n"

/********************************************************
 * Literales de operación de firma
 *******************************************************/

/** Firma de código */
#define SIGN_VALUE "pys4344"

/** Correo electrónico */
#define SIGN_EMAIL "mvp1011@alu.ubu.es"

/** Desplazamiento */
#define SIGN_SHIFT 3

/** Formato de NIA */
#define SIGN_NIA_FORMAT "%7s"

/** Longitud de NIA */
#define SIGN_NIA_LEN 7

/** Extremo inferior de número NIA */
#define NUM_MIN '0'

/** Extremo superior de número NIA */
#define NUM_MAX '9'

/** Extremo inferior de letra NIA */
#define LETTER_MIN 'a'

/** Extremo superior de letra NIA */
#define LETTER_MAX 'z'

/** Formato de mensaje de error de firma */
#define SIGN_ERROR "Error de firma: %s -> %s != %s\n"

/********************************************************
 * Literales de operación
 *******************************************************/

/** Nombre del archivo de estadísticas */
#define FILENAME "EuroStat_Inet_using_between_16_and_19.csv"

/** Separador de archivo CSV */
#define FILE_SEPARATOR ";"

/** Número de países */
#define COUNTRY_COUNT 28

/** Longitud de nombre de país */
#define COUNTRY_NAME_LEN 32

/** Número de columnas de estadísticas */
#define COUNTRY_COLS 10

/********************************************************
 * Literales de interfaz
 *******************************************************/

/** Menú principal */
#define MENU                                                             \
  "Estadísticas de usuarios (16-19 años) que se conecta a Internet a " \
  "diario\n\n"                                                           \
  "1. Mostrar estadísticas\n"                                           \
  "2. Año de mayor y menor porcentaje por país\n"                      \
  "3. Ordenación mediante selección directa (año 2023)\n"             \
  "4. Ordenación mediante método de la burbuja (año 2014)\n"          \
  "5. Firma de código\n"                                                \
  "X. Salir\n"                                                           \
  "Opción > "

/** Cabecera de tabla */
#define TABLE_HEADER                                   \
  TABLE_SEPARATOR                                      \
  "| País        "                                    \
  "| 2014    | 2015    | 2016    | 2017    | 2018    " \
  "| 2019    | 2020    | 2021    | 2022    | 2023    | \n" TABLE_SEPARATOR

/** Nombre de país */
#define TABLE_ROW_COUNTRY "| %-11s "

/** Datos de país */
#define TABLE_ROW_DATA "| %6.2f%% "

#define TABLE_ROW_DATA_ZERO "|       - "

/** Fin de fila de tabla */
#define TABLE_ROW_END "|\n"

/** Separador de tabla */
#define TABLE_SEPARATOR                                \
  "+-------------"                                     \
  "+---------+---------+---------+---------+---------" \
  "+---------+---------+---------+---------+---------+\n"

/********************************************************
 * Tipos de datos
 *******************************************************/

/** Buffer de caracteres */
typedef char buffer_t[UCHAR_MAX + 1];

/** NIA */
typedef char nia_t[SIGN_NIA_LEN + 1];

/** Nombre de país */
typedef char country_name_t[COUNTRY_NAME_LEN + 1];

/** Estadísticas de país */
typedef struct country_stats_t {
  country_name_t name;
  float data[COUNTRY_COLS];
} country_stats_t;

/** Métodos de ordenación */
typedef enum order_t { ASC, DESC } order_t;

/********************************************************
 * Prototipos de funciones auxiliares
 *******************************************************/

/**
 * Limpia los caracteres restantes del archivo
 * @param file Puntero al archivo
 */
void fclean(FILE* file);

/**
 * Pausa la ejecución del programa hasta que se presione enter
 * @param message Mensaje a mostrar
 * @return Carácter introducido
 */
int pause(const char* message);

/**
 * Lee 'size' caracteres de la entrada estándar
 * @param buffer Buffer de caracteres
 * @param size Tamaño del buffer
 * @return Número de caracteres leídos
 */
int read(char* buffer, size_t size);

/********************************************************
 * Prototipos de funciones de operación de firma
 *******************************************************/

/**
 * Cifra un NIA mediante el cifrado César
 * @param buffer Buffer de destino
 * @param email Correo electrónico
 * @param shift Desplazamiento
 * @return true si el cifrado fue exitoso, false en caso contrario
 */
bool firma_de_codigo(nia_t buffer, const char* email, int shift);

/**
 * Comprueba la firma de un NIA contenido en un
 * correo electrónico
 * @param shift Desplazamiento
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return true si la firma es correcta, false en caso contrario
 */
bool check_signature(const int shift, const char* email, const nia_t signature);

/********************************************************
 * Prototipos de funciones de operación
 *******************************************************/

/**
 * Lee los datos de un archivo CSV
 * @param filename Nombre del archivo
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @return true si la lectura fue exitosa, false en caso contrario
 */
bool read_data(const char* filename, country_stats_t* stats, size_t size);

/**
 * Busca un país en un arreglo de estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param name Nombre del país
 * @return Índice del país si se encuentra, EOF en caso contrario
 */
int search(const country_stats_t* stats,
           size_t size,
           const country_name_t name);

/**
 * Ordena un arreglo de estadísticas de países mediante selección directa
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param order Orden de la ordenación
 * @param year Año a ordenar
 * @param elements Contador de elementos
 * @param comparisons Contador de comparaciones
 * @param assignments Contador de asignaciones
 */
void dirsel_sort(country_stats_t* stats,
                 size_t size,
                 order_t order,
                 int year,
                 int* elements,
                 int* comparisons,
                 int* assignments);

/**
 * Ordena un arreglo de estadísticas de países mediante el método de la burbuja
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param order Orden de la ordenación
 * @param year Año a ordenar
 * @param elements Contador de elementos
 * @param comparisons Contador de comparaciones
 * @param assignments Contador de asignaciones
 */
void bubble_sort(country_stats_t* stats,
                 size_t size,
                 order_t order,
                 int year,
                 int* elements,
                 int* comparisons,
                 int* assignments);

/**
 * Imprime los datos de un arreglo de estadísticas de países
 * @param output Puntero al archivo de salida
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 */
void fprint_data(FILE* output, country_stats_t* stats, size_t size);

/********************************************************
 * Prototipos de funciones de interfaz
 *******************************************************/

/**
 * Menú principal
 * @param filename Nombre del archivo de estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Código de salida
 */
int menu(const char* filename,
         country_stats_t* stats,
         size_t size,
         const int shift,
         const char* email,
         const char* signature);

/**
 * Opción 1: Mostrar estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option1(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature);

/**
 * Opción 2: Año de mayor y menor porcentaje por país
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option2(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature);

/**
 * Opción 3: Ordenación mediante selección directa
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option3(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature);

/**
 * Opción 4: Ordenación mediante método de la burbuja
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option4(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature);

/********************************************************
 * Función principal
 *******************************************************/

int main() {
  // Se crea un arreglo de estadísticas de países
  country_stats_t stats[COUNTRY_COUNT];

  // Se muestra el menú principal
  return menu(FILENAME, stats, COUNTRY_COUNT, SIGN_SHIFT, SIGN_EMAIL,
              SIGN_VALUE);
}

/********************************************************
 * Definición de funciones de interfaz
 * Únicos puntos de entrada y salida
 *******************************************************/

/**
 * Menú principal
 * @param filename Nombre del archivo de estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Código de salida
 */
int menu(const char* filename,
         country_stats_t* stats,
         size_t size,
         const int shift,
         const char* email,
         const char* signature) {
  char option;
  nia_t signature_buffer;

  // Se lee el archivo de estadísticas
  if (read_data(filename, stats, size)) {
    do {
      // Se muestra el menú principal
      clear();
      printf(MENU);

      // Se lee la opción seleccionada
      if (scanf("%c", &option) == 1) {
        clear();

        // Se ejecuta la opción seleccionada
        switch (option) {
          case '1':
            option1(stats, size, shift, email, signature);
            break;
          case '2':
            option2(stats, size, shift, email, signature);
            break;
          case '3':
            option3(stats, size, shift, email, signature);
            break;
          case '4':
            option4(stats, size, shift, email, signature);
            break;
          case '5':
            firma_de_codigo(signature_buffer, email, shift);
            printf("Correo electrónico: %s\nFirma: %s\n", email,
                   signature_buffer);
            break;
          case 'x':
          case 'X':
            return EXIT_SUCCESS;
            break;
          default:
            printf("Opción no válida.\n");
        }

        pause("Pulse enter para continuar...");
      }
    } while (true);
  } else {
    // Si la lectura del archivo falla se retorna un error
    fprintf(stderr, FILE_ERROR, filename, errno, strerror(errno));
    return EXIT_FAILURE;
  }
}

/**
 * Opción 1: Mostrar estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option1(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature) {
  // Se comprueba la firma de código
  if (check_signature(shift, email, signature)) {
    // Se imprimen las estadísticas
    fprint_data(stdout, stats, size);
  }
}

/**
 * Opción 2: Año de mayor y menor porcentaje por país
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option2(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature) {
  int country;
  country_name_t name;

  // Se comprueba la firma de código
  if (check_signature(shift, email, signature)) {
    printf("Introduzca el nombre del país: ");
    fclean(stdin);
    if (read(name, sizeof(country_name_t))) {
      country = search(stats, size, name);

      if (country != EOF) {
        float max = stats[country].data[0];
        float min = stats[country].data[0];
        int max_year = 0;
        int min_year = 0;

        for (int year = 1; year < COUNTRY_COLS; year++) {
          if (stats[country].data[year] > max) {
            max = stats[country].data[year];
            max_year = year;
          }

          if (stats[country].data[year] >= 0 &&
              stats[country].data[year] < min) {
            min = stats[country].data[year];
            min_year = year;
          }
        }

        printf("País: %s\n", name);
        printf("Año de mayor porcentaje: %d (%.2f%%)\n", 2014 + max_year, max);
        printf("Año de menor porcentaje: %d (%.2f%%)\n", 2014 + min_year, min);
      } else {
        printf("País no encontrado.\n");
      }
    }
  }
}

/**
 * Opción 3: Ordenación mediante selección directa
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option3(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature) {
  int elements, comparisons, assignments;
  // Se comprueba la firma de código
  if (check_signature(shift, email, signature)) {
    // Se ordenan las estadísticas mediante selección directa
    dirsel_sort(stats, size, ASC, 2023, &elements, &comparisons, &assignments);
    // Se imprimen las estadísticas
    fprint_data(stdout, stats, size);
    // Se imprime el número de comparaciones y asignaciones
    printf(
        "\n"
        "Método: Selección directa\n"
        "Campo: 2023\n"
        "Elementos: %d\n"
        "Comparaciones: %d\n"
        "Asignaciones: %d\n",
        elements, comparisons, assignments);
  }
}

/**
 * Opción 4: Ordenación mediante método de la burbuja
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param shift Desplazamiento de cifrado
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option4(country_stats_t* stats,
             size_t size,
             const int shift,
             const char* email,
             const nia_t signature) {
  int elements, comparisons, assignments;
  // Se comprueba la firma de código
  if (check_signature(shift, email, signature)) {
    // Se ordenan las estadísticas mediante el método de la burbuja
    bubble_sort(stats, size, DESC, 2014, &elements, &comparisons, &assignments);
    // Se imprimen las estadísticas
    fprint_data(stdout, stats, size);
    // Se imprime el número de comparaciones y asignaciones
    printf(
        "\n"
        "Método: Burbuja\n"
        "Campo: 2014\n"
        "Elementos: %d\n"
        "Comparaciones: %d\n"
        "Asignaciones: %d\n",
        elements, comparisons, assignments);
  }
}

/********************************************************
 * Definición de funciones de operación
 *******************************************************/

/**
 * Lee los datos de un archivo CSV
 * @param filename Nombre del archivo
 * @param data Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @return true si la lectura fue exitosa, false en caso contrario
 */
bool read_data(const char* filename, country_stats_t* data, size_t size) {
  char* token;
  buffer_t buffer;
  FILE* file = fopen(filename, "r");

  // Si el archivo se abre correctamente
  if (file) {
    // Se lee el archivo línea a línea
    for (int line = 0; line < size && fgets(buffer, sizeof(buffer_t), file);
         line++) {
      // Se separan los datos de la línea
      token = strtok(buffer, FILE_SEPARATOR);

      // Si el token es válido
      if (token) {
        // Se copia el nombre del país
        strncpy(data[line].name, token, COUNTRY_NAME_LEN);

        // Se leen los datos de la línea
        for (int i = 0; i < COUNTRY_COLS; i++) {
          // Se obtiene el siguiente token
          token = strtok(NULL, FILE_SEPARATOR);

          // Si el token es válido
          if (token) {
            // Se convierte el token a un número de punto flotante
            data[line].data[i] = strtof(token, NULL);
          }
        }
      }
    }

    // Se cierra el archivo
    fclose(file);
    // Se retorna verdadero
    return true;
  }

  // Si el archivo no se abre correctamente se imprime un mensaje de error
  fprintf(stderr, FILE_ERROR, filename, errno, strerror(errno));
  // Se retorna falso
  return false;
}

/**
 * Busca un país en un arreglo de estadísticas
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param name Nombre del país
 * @return Índice del país si se encuentra, EOF en caso contrario
 */
int search(const country_stats_t* stats,
           size_t size,
           const country_name_t name) {
  // Se busca el país en el arreglo de estadísticas
  for (int country = 0; country < size; country++) {
    // Si el nombre del país es igual al nombre buscado
    if (strcmp(stats[country].name, name) == 0) {
      // Se retorna el índice del país
      return country;
    }
  }

  // Si el país no se encuentra se retorna EOF
  return EOF;
}

/**
 * Ordena un arreglo de estadísticas de países mediante selección directa
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param order Orden de la ordenación
 * @param year Año a ordenar
 * @param elements Contador de elementos
 * @param comparisons Contador de comparaciones
 * @param assignments Contador de asignaciones
 */
void dirsel_sort(country_stats_t* stats,
                 size_t size,
                 order_t order,
                 int year,
                 int* elements,
                 int* comparisons,
                 int* assignments) {
  country_stats_t temp;
  int min, index = year - 2014;

  // Inicializar contadores de elementos, comparaciones y asignaciones
  *elements = 0;
  *comparisons = 0;
  *assignments = 0;

  // Se ordena el arreglo de estadísticas mediante selección directa
  for (int i = 0; i < size - 1; i++) {
    // Se busca el índice del mínimo
    min = i;
    // Se compara el valor del mínimo con el resto de los elementos
    for (int j = i + 1; j < size; j++) {
      if (
          // Si el valor es menor que el mínimo y el orden es ascendente
          (order == ASC && stats[j].data[index] < stats[min].data[index]) ||
          // Si el valor es mayor que el mínimo y el orden es descendente
          (order == DESC && stats[j].data[index] > stats[min].data[index])) {
        // Se actualiza el índice del mínimo
        min = j;
      }
      (*comparisons)++;  // Contar la comparación
    }

    // Si el mínimo no es el elemento actual
    if (min != i) {
      // Se intercambian los elementos
      temp = stats[i];
      stats[i] = stats[min];
      stats[min] = temp;
      *assignments += 3;  // Tres asignaciones por intercambio
    }

    (*elements)++;  // Contar el elemento
  }
}

/**
 * Ordena un arreglo de estadísticas de países mediante selección directa
 * @param stats Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 * @param order Orden de la ordenación
 * @param year Año a ordenar
 * @param elements Contador de elementos
 * @param comparisons Contador de comparaciones
 * @param assignments Contador de asignaciones
 */
void bubble_sort(country_stats_t* stats,
                 size_t size,
                 order_t order,
                 int year,
                 int* elements,
                 int* comparisons,
                 int* assignments) {
  country_stats_t temp;
  int index = year - 2014;

  // Inicializar contadores de elementos, comparaciones y asignaciones
  *elements = 0;
  *comparisons = 0;
  *assignments = 0;

  // Se ordena el arreglo de estadísticas mediante el método de la burbuja
  for (int i = 0; i < size - 1; i++) {
    // Se compara cada elemento con el siguiente
    for (int j = 0; j < size - i - 1; j++) {
      (*comparisons)++;  // Contar la comparación
      if (
          // Si el valor es mayor que el siguiente y el orden es ascendente
          (order == ASC && stats[j].data[index] > stats[j + 1].data[index]) ||
          // Si el valor es menor que el siguiente y el orden es descendente
          (order == DESC && stats[j].data[index] < stats[j + 1].data[index])) {
        // Se intercambian los elementos
        temp = stats[j];
        stats[j] = stats[j + 1];
        stats[j + 1] = temp;
        *assignments += 3;  // Tres asignaciones por intercambio
      }
    }

    (*elements)++;  // Contar el elemento
  }
}

/**
 * Imprime los datos de un arreglo de estadísticas de países
 * @param output Puntero al archivo de salida
 * @param data Dirección de memoria del arreglo
 * @param size Tamaño del arreglo
 */
void fprint_data(FILE* output, country_stats_t* stats, size_t size) {
  // Se imprime la cabecera de la tabla
  printf(TABLE_HEADER);

  // Se imprimen los datos de cada país
  for (int country = 0; country < size; country++) {
    // Se imprime el nombre del país
    fprintf(output, TABLE_ROW_COUNTRY, stats[country].name);
    // Se imprimen los datos de cada año
    for (int year = 0; year < COUNTRY_COLS; year++) {
      // Se imprime el dato del año
      if (stats[country].data[year] == -1) {
        fprintf(output, TABLE_ROW_DATA_ZERO);
      } else {
        fprintf(output, TABLE_ROW_DATA, stats[country].data[year]);
      }
    }
    // Se imprime el fin de la fila
    fputs(TABLE_ROW_END, output);
  }

  // Se imprime el separador de la tabla
  printf(TABLE_SEPARATOR);
}

/********************************************************
 * Definición de funciones de operación de firma
 *******************************************************/

/**
 * Cifra un NIA mediante el cifrado César
 * @param buffer Buffer de destino
 * @param email Correo electrónico
 * @param shift Desplazamiento
 * @return true si el cifrado fue exitoso, false en caso contrario
 */
bool firma_de_codigo(nia_t buffer, const char* email, int shift) {
  // Si el NIA se copia correctamente al buffer
  if (strncpy(buffer, email, SIGN_NIA_LEN)) {
    // Para cada carácter del NIA
    for (int pos = 0; buffer[pos] != EOS; pos++) {
      if (buffer[pos] >= NUM_MIN && buffer[pos] <= NUM_MAX) {
        // Si el carácter es un número permitido
        // Se corrige el desplazamiento para que no se salga de rango
        buffer[pos] = (buffer[pos] - NUM_MIN + shift) % 10 + NUM_MIN;

      } else if (buffer[pos] >= LETTER_MIN && buffer[pos] <= LETTER_MAX) {
        // Si el carácter es una letra permitida
        // Se corrige el desplazamiento para que no se salga de rango
        buffer[pos] = (buffer[pos] - LETTER_MIN + shift) % 26 + LETTER_MIN;

      } else {
        // Se retorna falso si el carácter no es válido
        return false;
      }
    }

    // Se retorna verdadero si el cifrado fue exitoso
    return true;
  }

  // Se retorna falso si el formato de NIA no es válido
  return false;
}

/**
 * Comprueba la firma de un NIA contenido en un
 * correo electrónico
 * @param shift Desplazamiento
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return true si la firma es correcta, false en caso contrario
 */
bool check_signature(const int shift,
                     const char* email,
                     const nia_t signature) {
  nia_t buffer;

  // Se verifica que la firma sea correcta
  if (firma_de_codigo(buffer, email, shift) && strcmp(buffer, signature) == 0) {
    return true;
  }

  // Si la firma no es correcta se imprime un mensaje de error y se retorna
  // falso
  fprintf(stderr, SIGN_ERROR, email, buffer, signature);
  return false;
}

/********************************************************
 * Definición de funciones auxiliares
 *******************************************************/

/**
 * Limpia los caracteres restantes del archivo
 * @param file Puntero al archivo
 */
void fclean(FILE* file) {
  int value = getc(file);

  // Se limpian los caracteres restantes del archivo hasta encontrar un salto
  // de línea o el final del archivo
  while (value != EOL && value != EOF) {
    value = getc(file);
  }
}

/**
 * Pausa la ejecución del programa hasta que se presione enter
 * @param message Mensaje a mostrar
 * @return Carácter introducido
 */
int pause(const char* message) {
  printf("%s", message);
  fclean(stdin);
  return getchar();
}

/**
 * Lee 'size' caracteres de la entrada estándar
 * @param buffer Buffer de caracteres
 * @param size Tamaño del buffer
 * @return Número de caracteres leídos
 */
int read(char* buffer, size_t size) {
  if (fgets(buffer, size, stdin)) {
    // Se busca el salto de línea y se reemplaza por el fin de cadena
    buffer[strcspn(buffer, NEWLINE)] = EOS;
    // Se retorna la longitud de la cadena
    return strlen(buffer);
  }

  // Si no se lee ningún carácter se retorna 0
  return 0;
}
