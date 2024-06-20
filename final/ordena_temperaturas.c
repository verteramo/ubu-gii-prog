/**
 * @author Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @brief Ordenación de temperaturas de una estación de medición.
 * @version 1.0
 * @date 28/05/2024
 */

/***************************************
 * Literales
 **************************************/

#define MAX_DIAS 365
#define NMED 4

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
  uint_t current;               // ordinal del día dentro del año
  float mediciones[NMED];       // mediciones obtenidas en los momentos del día
  float temperatura_media_dia;  // temperatura media diaria (por Se calcula)
};

/** Ordenamiento */
typedef enum order { ASC, DESC } order_t;

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
 * @brief Ordena las temperaturas de la tabla.
 * @param temps Tabla de temperaturas.
 * @param temps_size Tamaño de la tabla.
 * @param moment Momento del día.
 * @param order Orden de ordenamiento.
 * @param comparisons Comparaciones realizadas.
 * @param assignments Asignaciones realizadas.
 *
 * Se llamaría de la siguiente manera:
 *
 * ordena_temperaturas(
 *    tabla_temperaturas,
 *    MAX_DIAS,
 *    SEIS_AM,
 *    ASC,
 *    &comparisons,
 *    &assignments
 * );
 */
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
 * @brief Ordena las temperaturas de la tabla.
 * @param temps Tabla de temperaturas.
 * @param temps_size Tamaño de la tabla.
 * @param moment Momento del día.
 * @param order Orden de ordenamiento.
 * @param comparisons Comparaciones realizadas.
 * @param assignments Asignaciones realizadas.
 *
 * Se llamaría de la siguiente manera:
 *
 * ordena_temperaturas(
 *    tabla_temperaturas,
 *    MAX_DIAS,
 *    SEIS_AM,
 *    ASC,
 *    &comparisons,
 *    &assignments
 * );
 */
void ordena_temperaturas(temp_t* temps,
                         int temps_size,
                         int moment,
                         order_t order,
                         int* comparisons,
                         int* assignments) {
  temp_t temp;

  // Inicialización de contadores
  *comparisons = 0;
  *assignments = 0;

  // Ordenamiento de burbuja
  for (uint_t i = 0; i < temps_size - 1; i++) {
    for (uint_t j = 0; j < temps_size - i - 1; j++) {
      // Una comparación por iteración
      (*comparisons)++;

      if (
          // Si el orden es ascendente y la temperatura actual es mayor que la
          // siguiente
          (order == ASC &&
           temps[j].mediciones[moment] > temps[j + 1].mediciones[moment]) ||
          // Si el orden es descendente y la temperatura actual es menor que la
          // siguiente
          (order == DESC &&
           temps[j].mediciones[moment] < temps[j + 1].mediciones[moment])) {
        // Intercambio de temperaturas
        temp = temps[j];
        temps[j] = temps[j + 1];
        temps[j + 1] = temp;
        // Tres asignaciones por intercambio
        *assignments += 3;
      }
    }
  }
}
