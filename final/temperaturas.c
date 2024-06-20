/**
 * @author Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @brief Datos meteorológicos de una estación de medición.
 * @version 1.0
 * @date 28/05/2024
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************
 * Literales
 *
 * Se añade el literal BINFILE
 * para el nombre del fichero binario.
 **************************************/

#define MAX_DIAS 365
#define NMED 4

/**
 * Nombre del fichero binario
 * Definido para llamar a la función crea_fichero
 */
#define BINFILE "medias_quincenales.dat"

/***************************************
 * Definición de tipos de datos
 *
 * Se redefinen los tipos de datos del
 * enunciado y se incluyen nuevos
 * tipos de datos para dar solución
 * al problema.
 **************************************/

/** Momento del día */
enum momento { SEIS_AM, DOCE_PM, SEIS_PM, DOCE_AM };

/** Temperaturas diarias */
struct temperaturas {
  unsigned int current;         // ordinal del día dentro del año
  float mediciones[NMED];       // mediciones obtenidas en los momentos del día
  float temperatura_media_dia;  // temperatura media diaria (por Se calcula)
};

/**
 * Estos alias de tipos de datos
 * no son estríctamente necesarios
 * para la resolución del problema,
 * pero aumentan la legibilidad.
 */

/** Temperaturas */
typedef struct temperaturas temp_t;

/** Entero sin signo */
typedef unsigned int uint_t;

/**
 * Periodo de tiempo
 * Tipo de dato que permite periodificar el tiempo en
 * quincenas, o en los múltiplos que sean necesarios.
 */
typedef enum period { QUINCENA = 15 } period_t;

/** Medias por periodo de tiempo */
typedef struct mean {
  float temp;       // temperatura media para el periodo de tiempo
  period_t period;  // periodo de tiempo
} mean_t;

/** Ordenamiento */
typedef enum order { ASC, DESC } order_t;

/***************************************
 * Variables globales
 *
 * Se define la variable global de la
 * tabla de temperaturas del enunciado.
 **************************************/

struct temperaturas
    tabla_temperaturas[MAX_DIAS];  // tabla anual de temperaturas

/***************************************
 * Prototipos de funciones
 ***************************************/

/**
 * @brief Calcula la temperatura media de una quincena.
 * @param temps Tabla de temperaturas.
 * @param start Día de inicio de la quincena.
 * @param period Periodo de tiempo.
 */
void calcula_temp_media_quincena(temp_t* temps, uint_t start, period_t period);

/**
 * @brief Calcula la temperatura media de los momentos del día.
 * @param means Tabla de medias.
 * @param temps Tabla de temperaturas.
 * @param start Día de inicio del periodo de tiempo.
 * @param period Periodo de tiempo.
 */
void calcula_temp_media_momentos(mean_t* means,
                                 temp_t* temps,
                                 uint_t start,
                                 period_t period);

/**
 * @brief Crea un fichero binario con las medias quincenales y de momentos.
 * @param filename Nombre del fichero.
 * @param temps Tabla de temperaturas.
 * @param means Tabla de medias.
 * @param period Periodo de tiempo.
 * @return true si se ha creado correctamente, false en caso contrario.
 *
 * Se llamaría de la siguiente manera:
 * crea_fichero(BINFILE, tabla_temperaturas, tabla_medias);
 */
bool crea_fichero(const char* filename,
                  temp_t* temps,
                  mean_t* means,
                  period_t period);

void ordena_temperaturas(temp_t* temps,
                         int temps_size,
                         int moment,
                         order_t order,
                         int* comparisons,
                         int* assignments);

/***************************************
 * Función principal
 **************************************/

int main() {}

/***************************************
 * Implementación de funciones
 **************************************/

/**
 * @brief Calcula la temperatura media de una quincena.
 * @param temps Tabla de temperaturas.
 * @param start Día de inicio de la quincena.
 * @param period Periodo de tiempo.
 */
void calcula_temp_media_quincena(temp_t* temps, uint_t start, period_t period) {
  // Se inicializa la suma
  float sum = 0.0;

  // Se recorren los días de la quincena
  for (uint_t current = start; current < start + period; current++) {
    // Se recorren los momentos del día
    for (int moment = 0; moment < NMED; moment++) {
      // Se suma la temperatura del momento
      sum += temps[current].mediciones[moment];
    }

    // Se calcula y almacena la media del día
    temps[current].temperatura_media_dia = sum / NMED;
  }
}

/**
 * @brief Calcula la temperatura media de los momentos del día.
 * @param means Tabla de medias.
 * @param temps Tabla de temperaturas.
 * @param start Día de inicio del periodo de tiempo.
 * @param period Periodo de tiempo.
 */
void calcula_temp_media_momentos(mean_t* means,
                                 temp_t* temps,
                                 uint_t start,
                                 period_t period) {
  // Se inicializa la suma
  float sum = 0.0;

  // Se recorren los momentos del día
  for (int moment = 0; moment < NMED; moment++) {
    // Se recorren los días del periodo de tiempo
    for (uint_t current = start; current < start + period; current++) {
      // Se suma la temperatura del momento actual
      sum += temps[current].mediciones[moment];
    }

    // Se calcula la media del momento
    means[moment].period = period;
    means[moment].temp = sum / period;
  }
}

/**
 * @brief Crea un fichero binario con las medias quincenales y de momentos.
 * @param filename Nombre del fichero.
 * @param temps Tabla de temperaturas.
 * @param means Tabla de medias.
 * @param period Periodo de tiempo.
 * @return true si se ha creado correctamente, false en caso contrario.
 *
 * Se llamaría de la siguiente manera:
 * crea_fichero(BINFILE, tabla_temperaturas, tabla_medias);
 */
bool crea_fichero(const char* filename,
                  temp_t* temps,
                  mean_t* means,
                  period_t period) {
  // Se abre el fichero en modo escritura binaria
  FILE* file = fopen(filename, "wb");

  // Si se ha abierto correctamente
  if (file) {
    // Se escriben las medias quincenales y de momentos
    fwrite(temps, sizeof(mean_t), MAX_DIAS / period, file);
    fwrite(means, sizeof(float), NMED, file);

    // Se cierra el fichero
    fclose(file);
    // Se retorna true
    return true;
  }

  // Se muestra un mensaje de error
  fprintf(stderr, "Error al abrir el fichero %s\n", filename);
  // Se retorna false
  return false;
}
