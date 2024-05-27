/**
 * @brief   Programa de administración del padrón
 * @file    Lab8A.c
 * @version 1.0
 * @date    27/04/2024
 * @autor   Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @compile gcc -o Lab8A Lab8A.c
 */

/********************************************************
 * Librerías
 *******************************************************/

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
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

/** Salto de línea */
#define EOL '\n'

/** Formato de mensaje de error de archivo */
#define FILE_ERROR "Error al abrir el fichero '%s' (%d: %s).\n"

/********************************************************
 * Literales de operación de firma
 *******************************************************/

/** Firma de código */
#define SIGN_VALUE 1

/** Correo electrónico */
#define SIGN_EMAIL "mvp1011@alu.ubu.es"

/** Carácter inicial de la firma */
#define SIGN_MIN 3

/** Carácter final de la firma */
#define SIGN_MAX 6

/** Formato de mensaje de error de firma */
#define SIGN_ERROR "Error de firma: %s -> %d != %d\n"

/********************************************************
 * Literales de operación
 *******************************************************/

/**
 * @link https://www.codigospostales.com/
 */

/** Código municipio mínimo */
#define CODE_MIN 1

/** Código municipio máximo */
#define CODE_MAX 52999

/** Número de campos de registro de texto */
#define REG_LEN 4

/** Formato de registro de texto */
#define REG_FORMAT "%u;%u;%u;%u\n"

/** Formato de registro anómalo */
#define REG_ANOM_FORMAT "%05u;%.2f;%u\n"

/** Tamaño de un registro binario */
#define REG_SIZE (sizeof(int) * REG_LEN)

/** Ruta del fichero de texto */
#define TEXTFILE "poblacion_hombres_mujeres.csv"

/** Ruta del fichero binario */
#define BINFILE "poblacion_hombres_mujeres.dat"

/** Ruta del fichero de anómalos */
#define ANOMFILE "anomalos.txt"

/********************************************************
 * Literales de interfaz
 * *****************************************************/

/** Literal de menú */
#define MENU                      \
  "Administración del padrón\n" \
  "0. Inicialización\n"          \
  "1. Estadísticas\n"            \
  "2. Estadísticas (Grupos)\n"   \
  "3. Búsqueda\n"                \
  "4. Anómalos\n"                \
  "5. Añadir\n"                  \
  "6. Firma\n"                    \
  "X. Salir\n"                    \
  "Opción > "

/** Literal de estadísticas */
#define STATS                                            \
  "%s\n[Municipios: %u]\n"                               \
  "          +-----------+----------+-------------+\n"   \
  "          | Población | Promedio | D. estándar |\n" \
  "+---------+-----------+----------+-------------+\n"   \
  "| Hombres | %9u | %8.2f | %11.2f |\n"                 \
  "| Mujeres | %9u | %8.2f | %11.2f |\n"                 \
  "| Total   | %9u | %8.2f | %11.2f |\n"                 \
  "+---------+-----------+----------+-------------+\n\n"

/** Literal de estadísticas vacías */
#define EMPTY_STATS "%s\n[Sin datos]\n\n"

#define TOWN                  \
  "+---------+-----------+\n" \
  "| %05u   | Población |\n" \
  "+---------+-----------+\n" \
  "| Hombres | %9u |\n"       \
  "| Mujeres | %9u |\n"       \
  "| Total   | %9u |\n"       \
  "+---------+-----------+\n\n"

/********************************************************
 * Tipos de datos
 *******************************************************/

/** Entero sin signo */
typedef unsigned int uint_t;

/********************************************************
 * Prototipos de funciones auxiliares
 *******************************************************/

/**
 * @brief Limpia los caracteres restantes del archivo
 * @param file Puntero al archivo
 */
void fclean(FILE* file);

/**
 * @brief Pausa la ejecución del programa hasta que se presione enter
 * @param message Mensaje a mostrar
 * @return Carácter introducido
 */
int pause(const char* message);

/********************************************************
 * Prototipos de funciones de operación de firma
 *******************************************************/

/**
 * @brief Calcula la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @return Firma de código
 */
int firma_de_codigo(const char* email);

/**
 * @brief Comprueba la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Éxito de la operación
 */
bool check_signature(const char* email, int signature);

/********************************************************
 * Prototipos de funciones de operación
 * Ficheros de texto
 ********************************************************/

/**
 * @brief Sumatoria de población de municipios en un rango
 * @param file Archivo de entrada
 * @param min Mínimo de población
 * @param max Máximo de población
 * @param total Suma de población
 * @param men Suma de población de hombres
 * @param women Suma de población de mujeres
 * @return Número de registros
 */
uint_t sum(FILE* file,
           uint_t min,
           uint_t max,
           uint_t* total,
           uint_t* men,
           uint_t* women);

/**
 * @brief Estadísticas de población de municipios en un rango
 * @param textfile Ruta del archivo de texto
 * @param min Mínimo de población
 * @param max Máximo de población
 * @param total Suma de población
 * @param mean Media de población
 * @param sdev Desviación estándar de población
 * @param men Suma de población de hombres
 * @param men_mean Media de población de hombres
 * @param men_sdev Desviación estándar de población de hombres
 * @param women Suma de población de mujeres
 * @param women_mean Media de población de mujeres
 * @param women_sdev Desviación estándar de población de mujeres
 * @return Número de registros
 */
uint_t stats(const char* textfile,
             uint_t min,
             uint_t max,
             uint_t* total,
             float* mean,
             float* sdev,
             uint_t* men,
             float* men_mean,
             float* men_sdev,
             uint_t* women,
             float* women_mean,
             float* women_sdev);
/**
 * @brief Añade un municipio al archivo de texto
 * @param textfile Ruta del archivo de texto
 * @param code Código del municipio
 * @param men Población de hombres
 * @param women Población de mujeres
 * @return Éxito de la operación
 */
bool add(const char* textfile, uint_t code, uint_t men, uint_t women);

/**
 * @brief Crea un archivo con los municipios con población anormalmente baja
 *        Además, imprime los municipios en la salida estándar
 * @param textfile Ruta del archivo de texto
 * @param anomfile Ruta del archivo de anómalos
 * @return Éxito de la operación
 */
bool anomalies(const char* textfile, const char* anomfile);

/********************************************************
 * Prototipos de funciones de operación
 * Ficheros binarios
 *******************************************************/

/**
 * @brief Inicializa el archivo binario
 * @param binfile Ruta del archivo binario
 * @return Éxito de la operación
 */
bool init(const char* binfile);

/**
 * @brief Copia los datos de un archivo de texto a un archivo binario
 * @param textfile Ruta del archivo de texto
 * @param binfile Ruta del archivo binario
 * @return Éxito de la operación
 */
bool copy(const char* textfile, const char* binfile);

/**
 * @brief Busca un municipio en un archivo binario
 * @param binfile Ruta del archivo binario
 * @param code Código del municipio
 * @param total Suma de población
 * @param men Suma de población de hombres
 * @param women Suma de población de mujeres
 * @return Éxito de la operación
 */
bool find(const char* binfile,
          uint_t code,
          uint_t* total,
          uint_t* men,
          uint_t* women);

/********************************************************
 * Prototipos de funciones de interfaz
 *******************************************************/

/**
 * @brief Menú de opciones
 * @param textfile Ruta del archivo de texto
 * @param binfile Ruta del archivo binario
 * @param anomfile Ruta del archivo de anómalos
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Código de salida
 */
int menu(const char* textfile,
         const char* binfile,
         const char* anomfile,
         const char* email,
         int signature);

/**
 * @brief Opción de inicialización
 * @param textfile Ruta del archivo de texto
 * @param binfile Ruta del archivo binario
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option0(const char* textfile,
             const char* binfile,
             const char* email,
             int signature);

/**
 * @brief Opción de estadísticas
 * @param textfile Ruta del archivo de texto
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option1(const char* textfile, const char* email, int signature);

/**
 * @brief Opción de estadísticas por grupos
 * @param textfile Ruta del archivo de texto
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option2(const char* textfile, const char* email, int signature);

/**
 * @brief Opción de búsqueda
 * @param textfile Ruta del archivo de texto
 * @param binfile Ruta del archivo binario
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option3(const char* textfile,
             const char* binfile,
             const char* email,
             int signature);

/**
 * @brief Opción de anómalos
 * @param textfile Ruta del archivo de texto
 * @param anomfile Ruta del archivo de anómalos
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void document(const char* textfile,
              const char* anomfile,
              const char* email,
              int signature);

/**
 * @brief Opción de añadir
 * @param textfile Ruta del archivo de texto
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option5(const char* textfile, const char* email, int signature);

/**
 * @brief Opción de firma
 * @param email Correo electrónico
 */
void option6(const char* email);

/********************************************************
 * Función principal
 *******************************************************/

int main() {
  /**
   * Con la parametrización de los siguientes
   * valores se evita un fuerte acoplamiento.
   */
  return menu(TEXTFILE, BINFILE, ANOMFILE, SIGN_EMAIL, SIGN_VALUE);
}

/********************************************************
 * Definición de funciones de interfaz
 * Únicos puntos de entrada y salida
 *******************************************************/

/** Menú de opciones */
int menu(const char* textfile,  // Ruta del archivo de texto
         const char* binfile,   // Ruta del archivo binario
         const char* anomfile,  // Ruta del archivo de anómalos
         const char* email,     // Correo electrónico
         int signature          // Firma de código
) {
  char option;

  do {
    clear();
    printf(MENU);

    if (scanf("%c", &option) == 1) {
      clear();

      switch (option) {
        case '0':
          option0(textfile, binfile, email, signature);
          break;
        case '1':
          option1(textfile, email, signature);
          break;
        case '2':
          option2(textfile, email, signature);
          break;
        case '3':
          option3(textfile, binfile, email, signature);
          break;
        case '4':
          document(textfile, anomfile, email, signature);
          break;
        case '5':
          option5(textfile, email, signature);
          break;
        case '6':
          option6(email);
          break;
        case 'x':
        case 'X':
          return EXIT_SUCCESS;
        default:
          printf("Opción incorrecta\n");
          break;
      }

      pause("Presione enter para continuar...");
    }
  } while (true);
}

/** Opción de inicialización */
void option0(const char* textfile,  // Ruta del archivo de texto
             const char* binfile,   // Ruta del archivo binario
             const char* email,     // Correo electrónico
             int signature          // Firma de código
) {
  /**
   * No es estrictamente necesario inicializar el archivo binario,
   * ya que al solicitar una búsqueda se realiza su inicialización y copia de
   * datos.
   */
  if (check_signature(email, signature)) {
    if (init(binfile) && copy(textfile, binfile)) {
      printf("Archivo binario '%s' inicializado correctamente.\n", binfile);
    }
  }
}

/** Opción de estadísticas */
void option1(const char* textfile,  // Ruta del archivo de texto
             const char* email,     // Correo electrónico
             int signature          // Firma de código
) {
  uint_t count, total, men, women;
  float mean, sdev, men_mean, men_sdev, women_mean, women_sdev;

  if (check_signature(email, signature)) {
    // Si se obtienen registros se imprimen las estadísticas
    count = stats(textfile, 0, INT_MAX, &total, &mean, &sdev, &men, &men_mean,
                  &men_sdev, &women, &women_mean, &women_sdev);
    if (count) {
      printf(STATS, "Estadísticas globales", count, men, men_mean, men_sdev,
             women, women_mean, women_sdev, total, mean, sdev);
    } else {
      printf(EMPTY_STATS, "Estadísticas globales");
    }
  }
}

/** Opción de estadísticas por grupos */
void option2(const char* textfile,  // Ruta del archivo de texto
             const char* email,     // Correo electrónico
             int signature          // Firma de código
) {
  uint_t count, total, men, women;
  float mean, sdev, men_mean, men_sdev, women_mean, women_sdev;

  if (check_signature(email, signature)) {
    // Grupo A: Más de 25000 habitantes
    count = stats(textfile, 25000, INT_MAX, &total, &mean, &sdev, &men,
                  &men_mean, &men_sdev, &women, &women_mean, &women_sdev);
    if (count) {
      printf(STATS, "Estadísticas Grupo A (Desde 25000 habitantes)", count, men,
             men_mean, men_sdev, women, women_mean, women_sdev, total, mean,
             sdev);
    } else {
      printf(EMPTY_STATS, "Estadísticas Grupo A (Desde 25000 habitantes)");
    }

    // Grupo B: 10000 - 24999 habitantes
    count = stats(textfile, 10000, 24999, &total, &mean, &sdev, &men, &men_mean,
                  &men_sdev, &women, &women_mean, &women_sdev);
    if (count) {
      printf(STATS, "Estadísticas Grupo B (10000-24999 habitantes)", count, men,
             men_mean, men_sdev, women, women_mean, women_sdev, total, mean,
             sdev);
    } else {
      printf(EMPTY_STATS, "Estadísticas Grupo B (10000-24999 habitantes)");
    }

    // Grupo C: 0 - 9999 habitantes
    count = stats(textfile, 0, 9999, &total, &mean, &sdev, &men, &men_mean,
                  &men_sdev, &women, &women_mean, &women_sdev);
    if (count) {
      printf(STATS, "Estadísticas Grupo B (0-9999 habitantes)", count, men,
             men_mean, men_sdev, women, women_mean, women_sdev, total, mean,
             sdev);
    } else {
      printf(EMPTY_STATS, "Estadísticas Grupo B (0-9999 habitantes)");
    }
  }
}

/** Opción de búsqueda */
void option3(const char* textfile,  // Ruta del archivo de texto
             const char* binfile,   // Ruta del archivo binario
             const char* email,     // Correo electrónico
             int signature          // Firma de código
) {
  uint_t code, total, men, women;

  // Se inicializa el archivo binario y se copian los datos
  if (check_signature(email, signature) && init(binfile) &&
      copy(textfile, binfile)) {
    printf("Búsqueda de un municipio\n");
    printf("Código > ");
    scanf("%u", &code);

    // Se busca el municipio en el archivo binario
    if (find(binfile, code, &total, &men, &women)) {
      printf(TOWN, code, men, women, total);
    } else {
      printf("Municipio '%u' no encontrado.\n", code);
    }
  }
}

/** Opción de anómalos */
void document(const char* textfile,  // Ruta del archivo de texto
              const char* anomfile,  // Ruta del archivo de anómalos
              const char* email,     // Correo electrónico
              int signature          // Firma de código
) {
  if (check_signature(email, signature) && anomalies(textfile, anomfile)) {
    printf("Archivo '%s' creado correctamente.\n", anomfile);
  }
}

/** Opción de añadir */
void option5(const char* textfile,  // Ruta del archivo de texto
             const char* email,     // Correo electrónico
             int signature          // Firma de código
) {
  uint_t code, men, women;

  if (check_signature(email, signature)) {
    printf("Agregar un municipio\n");
    printf("Código > ");
    scanf("%u", &code);

    printf("Población de hombres > ");
    scanf("%u", &men);

    printf("Población de mujeres > ");
    scanf("%u", &women);

    // Se añade el municipio al archivo de texto
    if (add(textfile, code, men, women)) {
      printf("Municipio '%05u' añadido correctamente.\n", code);
    }
  }
}

/** Opción de firma */
void option6(const char* email) {
  printf("Correo electrónico: %s\nFirma: %d\n", email, firma_de_codigo(email));
}

/********************************************************
 * Definición de funciones de operación
 * Ficheros de texto
 *******************************************************/

/** Sumatoria de población de municipios en un rango */
uint_t sum(FILE* file,     // Archivo de entrada
           uint_t min,     // Mínimo de población
           uint_t max,     // Máximo de población
           uint_t* total,  // Suma de población
           uint_t* men,    // Suma de población de hombres
           uint_t* women   // Suma de población de mujeres
) {
  uint_t code, row_total, row_men, row_women;
  uint_t count = 0;

  // Se reinicia el puntero del archivo
  rewind(file);

  // Se inicializan los valores de salida
  *total = *men = *women = 0;

  // Se realiza la sumatoria de población
  while (fscanf(file, REG_FORMAT, &code, &row_total, &row_men, &row_women) ==
         REG_LEN) {
    if (row_total >= min && row_total <= max) {
      *total += row_total;
      *men += row_men;
      *women += row_women;
      count++;
    }
  }

  // Se retorna el número de registros
  return count;
}

/** Estadísticas de población de municipios en un rango */
uint_t stats(const char* textfile,  // Ruta del archivo de texto
             uint_t min,            // Mínimo de población
             uint_t max,            // Máximo de población
             uint_t* total,         // Suma de población
             float* mean,           // Media de población
             float* sdev,           // Desviación estándar de población
             uint_t* men,           // Suma de población de hombres
             float* men_mean,       // Media de población de hombres
             float* men_sdev,  // Desviación estándar de población de hombres
             uint_t* women,    // Suma de población de mujeres
             float* women_mean,  // Media de población de mujeres
             float* women_sdev  // Desviación estándar de población de mujeres
) {
  uint_t code, row_total, row_men, row_women;
  uint_t count = 0;
  FILE* file = fopen(textfile, "r");

  // Se verifica que el archivo se haya abierto
  if (file) {
    // Se inicializan los valores de salida
    *mean = *sdev = *men_mean = *men_sdev = *women_mean = *women_sdev = 0;

    // Se realiza la sumatoria de población
    count = sum(file, min, max, total, men, women);

    // Si se obtienen registros se calculan las estadísticas
    if (count) {
      // Se calcula la media de población
      *mean = (float)*total / count;
      *men_mean = (float)*men / count;
      *women_mean = (float)*women / count;

      // Se reinicia el puntero del archivo
      rewind(file);

      // Se realiza la sumatoria de cuadrados
      while (fscanf(file, REG_FORMAT, &code, &row_total, &row_men,
                    &row_women) == REG_LEN) {
        if (row_total >= min && row_total <= max) {
          *sdev += pow(row_total - *mean, 2);
          *men_sdev += pow(row_men - *men_mean, 2);
          *women_sdev += pow(row_women - *women_mean, 2);
        }
      }

      /**
       * En las muestras se utiliza n−1 en el denominador para corregir el sesgo
       * en la estimación de la desviación estándar. En este caso se trata de
       * una población, por lo que se utiliza n en el denominador.
       */
      //--count;

      // Se calcula la desviación estándar
      *sdev = sqrt(*sdev / count);
      *men_sdev = sqrt(*men_sdev / count);
      *women_sdev = sqrt(*women_sdev / count);
    }

    // Se cierra el archivo
    fclose(file);
  } else {
    // Se imprime el error
    fprintf(stderr, FILE_ERROR, textfile, errno, strerror(errno));
  }

  // Se retorna el número de registros
  return count;
}

/** Añade un municipio al archivo de texto */
bool add(const char* textfile,  // Ruta del archivo de texto
         uint_t code,           // Código del municipio
         uint_t men,            // Población de hombres
         uint_t women           // Población de mujeres
) {
  FILE* file = fopen(textfile, "a");

  if (file) {
    // Se añade el municipio al archivo
    fprintf(file, REG_FORMAT, code, men + women, men, women);
    fclose(file);
    return true;
  }

  fprintf(stderr, FILE_ERROR, textfile, errno, strerror(errno));
  return false;
}

/** Crea un archivo con los municipios con población anormalmente baja */
bool anomalies(const char* textfile,  // Ruta del archivo de texto
               const char* anomfile   // Ruta del archivo de anómalos
) {
  uint_t count, code, total, men, women;
  float mean, limit;
  FILE* input = fopen(textfile, "r");
  FILE* output = fopen(anomfile, "w");

  // Se verifica que ambos archivos se hayan abierto correctamente
  if (input) {
    if (output) {
      // Se calcula el límite de población anormalmente baja
      count = sum(input, 0, INT_MAX, &total, &men, &women);
      mean = (float)total / count;
      limit = mean / 10;

      // Se reinicia el puntero del archivo
      rewind(input);

      // Se imprimen los municipios con población anormalmente baja
      // Tanto en la salida estándar como en el archivo de anómalos
      while (fscanf(input, REG_FORMAT, &code, &total, &men, &women) ==
             REG_LEN) {
        if (total < limit) {
          printf(REG_ANOM_FORMAT, code, limit, total);
          fprintf(output, REG_ANOM_FORMAT, code, limit, total);
        }
      }

      fclose(input);
      fclose(output);
      return true;
    } else {
      fprintf(stderr, FILE_ERROR, anomfile, errno, strerror(errno));
    }

    fclose(input);
  } else {
    fprintf(stderr, FILE_ERROR, textfile, errno, strerror(errno));
  }

  return false;
}

/********************************************************
 * Definición de funciones de operación
 * Ficheros binarios
 *******************************************************/

/** Inicializa el archivo binario */
bool init(const char* binfile  // Ruta del archivo binario
) {
  FILE* file = fopen(binfile, "wb");

  if (file) {
    // Se inicializa el archivo con valores -1
    // Puesto que cero es un valor válido para la población
    for (int data = -1, i = CODE_MIN; i <= CODE_MAX; i++) {
      fwrite(&data, sizeof(int), 1, file);
      fwrite(&data, sizeof(int), 1, file);
      fwrite(&data, sizeof(int), 1, file);
      fwrite(&data, sizeof(int), 1, file);
    }

    fclose(file);
    return true;
  }

  fprintf(stderr, FILE_ERROR, binfile, errno, strerror(errno));
  return false;
}

/** Copia los datos de un archivo de texto a un archivo binario */
bool copy(const char* textfile,  // Ruta del archivo de texto
          const char* binfile    // Ruta del archivo binario
) {
  uint_t code, total, men, women;
  FILE* input = fopen(textfile, "r");
  FILE* output = fopen(binfile, "rb+");

  // Se verifica que ambos archivos se hayan abierto correctamente
  if (input) {
    if (output) {
      // Se copian los datos del archivo de texto al archivo binario
      while (fscanf(input, REG_FORMAT, &code, &total, &men, &women) ==
             REG_LEN) {
        // Se accede a la posición correspondiente
        fseek(output, code * REG_SIZE, SEEK_SET);

        // Se escriben los datos
        fwrite(&code, sizeof(int), 1, output);
        fwrite(&total, sizeof(int), 1, output);
        fwrite(&men, sizeof(int), 1, output);
        fwrite(&women, sizeof(int), 1, output);
      }

      fclose(input);
      fclose(output);
      return true;
    } else {
      fprintf(stderr, FILE_ERROR, binfile, errno, strerror(errno));
    }

    fclose(input);
  } else {
    fprintf(stderr, FILE_ERROR, textfile, errno, strerror(errno));
  }

  return false;
}

/** Busca un municipio en un archivo binario */
bool find(const char* binfile,  // Ruta del archivo binario
          uint_t code,          // Código del municipio
          uint_t* total,        // Suma de población
          uint_t* men,          // Suma de población de hombres
          uint_t* women         // Suma de población de mujeres
) {
  int read_code;
  FILE* file = fopen(binfile, "rb");

  if (file) {
    // Se accede a la posición correspondiente
    fseek(file, code * REG_SIZE, SEEK_SET);

    // Se lee el código del municipio
    fread(&read_code, sizeof(int), 1, file);

    // Se verifica que el código leído sea igual al buscado
    // Si es -1 no coincidirá con ningún código y se considerará no encontrado
    if (read_code == code) {
      // Se leen los datos del municipio
      fread(total, sizeof(int), 1, file);
      fread(men, sizeof(int), 1, file);
      fread(women, sizeof(int), 1, file);

      fclose(file);
      return true;
    }

    fclose(file);
    return false;
  }

  fprintf(stderr, FILE_ERROR, binfile, errno, strerror(errno));
  return false;
}

/********************************************************
 * Definición de funciones de operación de firma
 *******************************************************/

/** Calcula la firma de un NIA contenido en un correo electrónico */
int firma_de_codigo(const char* email  // Correo electrónico
) {
  int result = 0;

  // Se realiza la operación XOR de los caracteres de la firma
  for (int i = SIGN_MIN; i <= SIGN_MAX; i++) {
    result ^= email[i];
  }

  return result;
}

/** Comprueba la firma de un NIA contenido en un correo electrónico */
bool check_signature(const char* email,  // Correo electrónico
                     int signature       // Firma de código
) {
  // Se obtiene la firma
  int calculated_signature = firma_de_codigo(email);

  // Se verifica que la firma sea correcta
  if (calculated_signature == signature) {
    return true;
  }

  // Si la firma no es correcta se imprime un mensaje de error y se retorna
  // falso
  fprintf(stderr, SIGN_ERROR, email, calculated_signature, signature);
  return false;
}

/********************************************************
 * Definición de funciones auxiliares
 *******************************************************/

/** Limpia los caracteres restantes del archivo */
void fclean(FILE* file  // Puntero al archivo
) {
  int value = getc(file);

  // Se limpian los caracteres restantes del archivo hasta encontrar un salto de
  // línea o el final del archivo
  while (value != EOL && value != EOF) {
    value = getc(file);
  }
}

/** Pausa la ejecución del programa hasta que se presione enter */
int pause(const char* message  // Mensaje a mostrar
) {
  printf("%s", message);
  fclean(stdin);
  return getchar();
}
