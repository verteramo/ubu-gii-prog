/**
 * @file
 * @brief   Programa que simula un fondo de inversión
 * @version 1.0
 * @date    04/05/2024
 * @autor   Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @compile gcc -Wall -o lab_9b_1 lab_9b_1.c -lm
 * @execute ./lab_9b_1
 */

/********************************************************
 * Librerías
 *******************************************************/

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
#define SIGN_VALUE 4617

/** Correo electrónico */
#define SIGN_EMAIL "mvp1011@alu.ubu.es"

/** Módulo de firma */
#define SIGN_MOD 65

/** Máscara para caracteres pares */
#define SIGN_MASK_EVEN 10

/** Máscara para caracteres impares */
#define SIGN_MASK_ODD 11

/** Formato de NIA */
#define SIGN_NIA_FORMAT "%7s"

/** Longitud de NIA */
#define SIGN_NIA_LEN 7

/** Formato de mensaje de error de firma */
#define SIGN_ERROR "Error de firma: %s -> %d != %d\n"

/********************************************************
 * Literales de operación
 *******************************************************/

/** Cantidad mínima de inversión */
#define CAPITAL_MIN 8000

/** Cantidad máxima de inversión */
#define CAPITAL_MAX 50000

/** Tasa de interés mínima */
#define RATE_MIN 0.0

/** Tasa de interés máxima */
#define RATE_MAX 100.0

/** Tamaño del arreglo de tasas de interés probables */
#define RATES_LEN 12

/** Fichero de simulación */
#define SIMFILE1 "simulación.txt"

/** Fichero de simulación probable */
#define SIMFILE2 "simulación_probable.txt"

/** Capital por defecto */
#define DEFAULT_CAPITAL CAPITAL_MIN

/** Tasa de interés por defecto */
#define DEFAULT_RATE 0.21

/** Periodos de capitalización por defecto */
#define DEFAULT_PERIODS 36

/********************************************************
 * Literales de interfaz
 *******************************************************/

#define STATUS_CAPITAL "[Capital: %.2f EUR]\n"

#define STATUS_RATE "[Interés: %.2f %%]\n"

/** Literal de menú */
#define MENU                                           \
  "Fondos de inversión\n\n" STATUS_CAPITAL STATUS_RATE \
  "\n"                                                 \
  "1. Ingresar capital e intereses trimestrales\n"     \
  "2. Cuadro de simulación\n"                         \
  "3. Cuadro de simulación probable\n"                \
  "4. Valor del fondo a mes determinado\n"             \
  "5. Firma de código\n"                              \
  "X. Salir\n"                                         \
  "Opción > "

/** Literal de submenú de simulación */
#define MENUTAB                                         \
  "Cuadro de simulación\n\n" STATUS_CAPITAL STATUS_RATE \
  "\n"                                                  \
  "1. Ver en pantalla\n"                                \
  "2. Guardar en fichero\n"                             \
  "X. Regresar\n"                                       \
  "Opción > "

/** Literal de submenú de simulación probable */
#define MENUSIM                                      \
  "Cuadro de simulación probable\n\n" STATUS_CAPITAL \
  "\n"                                               \
  "1. Ver en pantalla\n"                             \
  "2. Guardar en fichero\n"                          \
  "X. Regresar\n"                                    \
  "Opción > "

/** Literal de cabecera cuadro de simulación */
#define TAB_HEADER                   \
  "Cuadro de simulación\n\n"        \
  "[Capital inicial: %.2f EUR]\n"    \
  "[Interés trimestral: %.2f %%]\n" \
  "[Periodos de capitalización: %d]\n\n"

/** Literal de cabecera de cuadro de simulación probable */
#define SIM_HEADER            \
  "Cuadro de simulación\n\n" \
  "[Capital inicial: %.2f EUR]\n\n"

/** Literal de cabecera de tabla */
#define ROW_HEADER                                                  \
  "+-----+-----------------+-----------------+-----------------+\n" \
  "| Mes | Capital inicial | Tasa aplicada   | Capital final   |\n" \
  "+-----+-----------------+-----------------+-----------------+\n"

/** Literal de fila de tabla */
#define ROW "| %-3d | %11.2f EUR | %+13.4f %% | %11.2f EUR |\n"

/** Literal de pie de tabla */
#define ROW_FOOTER \
  "+-----+-----------------+-----------------+-----------------+\n"

/********************************************************
 * Tipos de datos
 *******************************************************/

/** Buffer de caracteres */
typedef char buffer_t[UCHAR_MAX + 1];

/** NIA */
typedef char nia_t[SIGN_NIA_LEN + 1];

/** Entero sin signo */
typedef unsigned int uint_t;

/** Periodos de capitalización */
typedef enum period_t {
  ANNUAL = 1,
  SEMIANNUAL = 2,
  QUARTERLY = 4,
  MONTHLY = 12
} period_t;

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
 * Lee una cadena de caracteres hasta encontrar un salto de línea
 * @param buffer Buffer de caracteres
 * @return Número de caracteres leídos
 */
int read(buffer_t buffer);

/********************************************************
 * Prototipos de funciones de operación de firma
 *******************************************************/

/**
 * Calcula la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @return Firma de código
 */
int firma_de_codigo(const char* email);

/**
 * Comprueba la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Éxito de la operación
 */
bool check_signature(const char* email, int signature);

/********************************************************
 * Prototipos de funciones de operación
 *******************************************************/

/**
 * Convierte una tasa de interés de un periodo a otro
 * @param rate Tasa de interés
 * @param orig Periodo de origen
 * @param dest Periodo de destino
 * @return Tasa de interés convertida
 */
double convert_rate(double rate, period_t orig, period_t dest);

/**
 * Capitaliza una renta a un periodo determinado
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param period Periodo
 * @return Capital final
 */
double capitalize(double capital, double rate, int period);

/**
 * Imprime un cuadro de simulación en un archivo
 * @param output Puntero al archivo de salida
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 */
void fprinttab(FILE* output, double capital, double rate, uint_t periods);

/**
 * Imprime un cuadro de simulación de tasas probables en un archivo
 * @param output Puntero al archivo de salida
 * @param capital Capital inicial
 * @param rates Tasas de interés
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 */
void fprintsim(FILE* output,
               double capital,
               const double* rates,
               const int rates_len,
               period_t period);



/**
 * Muestra el menú principal
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 * @param simfile1 Fichero de simulación
 * @param simfile2 Fichero de simulación probable
 * @param rates Tasas de interés probables
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Éxito de la operación
 */
int menu(double* capital,
         double* rate,
         uint_t periods,
         const char* simfile1,
         const char* simfile2,
         const double* rates,
         const int rates_len,
         period_t period,
         const char* email,
         int signature);

/**
 * Establece el capital inicial
 * @param capital Capital inicial
 */
void set_capital(double* capital);

/**
 * Establece la tasa de interés
 * @param rate Tasa de interés
 */
void set_rate(double* rate);

/**
 * Opción 1 del menú principal
 * Establece el capital inicial y la tasa de interés
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option1(double* capital, double* rate, const char* email, int signature);

/**
 * Opción 2 del menú principal
 * Muestra el submenú de simulación
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 * @param simfile Fichero de simulación
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void menutab(double capital,
             double rate,
             uint_t periods,
             const char* simfile,
             const char* email,
             int signature);

/**
 * Opción 3 del menú principal
 * Muestra el submenú de simulación probable
 * @param capital Capital inicial
 * @param rates Tasas de interés probables
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 * @param simfile Fichero de simulación probable
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void menusim(double capital,
             const double* rates,
             const int rates_len,
             period_t period,
             const char* simfile,
             const char* email,
             int signature);

/**
 * Opción 4 del menú principal
 * Muestra el valor del fondo a un mes determinado
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option4(double capital, double rate, const char* email, int signature);

/********************************************************
 * Función principal
 *******************************************************/

int main() {
  // Tasas de interés probables
  const double RATES[] = {0.21, 0.15,  0.33, -0.45, -1.00, 0.12,
                          0.24, -0.66, 0.22, 0.36,  -0.12, 1.25};

  // Parametrización por defecto
  double capital = DEFAULT_CAPITAL;
  double rate = DEFAULT_RATE;
  uint_t periods = DEFAULT_PERIODS;

  // Se muestra el menú principal
  return menu(&capital, &rate, periods, SIMFILE1, SIMFILE2, RATES, RATES_LEN,
              QUARTERLY, SIGN_EMAIL, SIGN_VALUE);
}

/********************************************************
 * Definición de funciones de interfaz
 * Únicos puntos de entrada y salida
 *******************************************************/

/**
 * Muestra el menú principal
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 * @param simfile1 Fichero de simulación
 * @param simfile2 Fichero de simulación probable
 * @param rates Tasas de interés probables
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Éxito de la operación
 */
int menu(double* capital,
         double* rate,
         uint_t periods,
         const char* simfile1,
         const char* simfile2,
         const double* rates,
         const int rates_len,
         period_t period,
         const char* email,
         int signature) {
  char option;

  do {
    // Se muestra el menú principal
    clear();
    printf(MENU, *capital, *rate);

    // Se lee la opción seleccionada
    if (scanf("%c", &option) == 1) {
      clear();

      // Se ejecuta la opción seleccionada
      switch (option) {
        case '1':
          option1(capital, rate, email, signature);
          break;
        case '2':
          menutab(*capital, *rate, periods, simfile1, email, signature);
          continue;
        case '3':
          menusim(*capital, rates, rates_len, period, simfile2, email,
                  signature);
          continue;
        case '4':
          option4(*capital, *rate, email, signature);
          break;
        case '5':
          printf("Correo electrónico: %s\nFirma: %d\n", email,
                 firma_de_codigo(email));
          break;
        case 'x':
        case 'X':
          // Se sale del programa
          return EXIT_SUCCESS;
        default:
          printf("Opción incorrecta\n");
          break;
      }

      pause("Presione enter para continuar...");
    }
  } while (true);
}

/**
 * Establece el capital inicial
 * @param capital Capital inicial
 */
void set_capital(double* capital) {
  double value;
  buffer_t line;

  // Se solicita el capital inicial mientras no se introduzca un valor válido
  do {
    printf("Capital (Rango 8000-50000) [%.2f EUR] > ", *capital);
    if (read(line)) {
      value = atof(line);
    } else {
      return;
    }
  } while (value < CAPITAL_MIN || value > CAPITAL_MAX);

  // Se establece el capital inicial
  *capital = value;
}

/**
 * Establece la tasa de interés
 * @param rate Tasa de interés
 */
void set_rate(double* rate) {
  double value;
  buffer_t line;

  // Se solicita la tasa de interés mientras no se introduzca un valor válido
  do {
    printf("Interés (Rango 0.0-100.0) [%.2f %%] > ", *rate);
    if (read(line)) {
      value = atof(line);
    } else {
      return;
    }
  } while (value < RATE_MIN || value > RATE_MAX);

  // Se establece la tasa de interés
  *rate = value;
}

/**
 * Opción 1 del menú principal
 * Establece el capital inicial y la tasa de interés
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option1(double* capital, double* rate, const char* email, int signature) {
  if (check_signature(email, signature)) {
    fclean(stdin);
    set_capital(capital);
    set_rate(rate);
  }
}

/**
 * Opción 2 del menú principal
 * Muestra el submenú de simulación
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 * @param simfile Fichero de simulación
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void menutab(double capital,
             double rate,
             uint_t periods,
             const char* simfile,
             const char* email,
             int signature) {
  char option;

  if (check_signature(email, signature)) {
    fclean(stdin);
    do {
      // Se muestra el submenú de simulación
      clear();
      printf(MENUTAB, capital, rate);

      // Se lee la opción seleccionada
      if (scanf("%c", &option) == 1) {
        clear();

        // Se ejecuta la opción seleccionada
        switch (option) {
          case '1':
            fprinttab(stdout, capital, rate, periods);
            break;
          case '2':
            FILE* output = fopen(simfile, "w");

            if (output) {
              fprinttab(output, capital, rate, periods);
              fclose(output);
              printf("Fichero '%s' creado correctamente.\n", simfile);
            } else {
              fprintf(stderr, FILE_ERROR, simfile, errno, strerror(errno));
            }

            break;
          case 'x':
          case 'X':
            // Se regresa al menú principal
            fclean(stdin);
            return;
          default:
            printf("Opción no válida\n");
            break;
        }

        pause("Presione enter para continuar...");
      }
    } while (true);
  } else {
    pause("Presione enter para continuar...");
  }
}

/**
 * Opción 3 del menú principal
 * Muestra el submenú de simulación probable
 * @param capital Capital inicial
 * @param rates Tasas de interés probables
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 * @param simfile Fichero de simulación probable
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void menusim(double capital,
             const double* rates,
             const int rates_len,
             period_t period,
             const char* simfile,
             const char* email,
             int signature) {
  char option;

  if (check_signature(email, signature)) {
    fclean(stdin);
    do {
      // Se muestra el submenú de simulación probable
      clear();
      printf(MENUSIM, capital);

      // Se lee la opción seleccionada
      if (scanf("%c", &option) == 1) {
        clear();

        // Se ejecuta la opción seleccionada
        switch (option) {
          case '1':
            fprintsim(stdout, capital, rates, rates_len, period);
            break;
          case '2':
            FILE* output = fopen(simfile, "w");

            if (output) {
              fprintsim(output, capital, rates, rates_len, period);
              fclose(output);
              printf("Fichero '%s' creado correctamente.\n", simfile);
            } else {
              fprintf(stderr, FILE_ERROR, simfile, errno, strerror(errno));
            }

            break;
          case 'x':
          case 'X':
            // Se regresa al menú principal
            fclean(stdin);
            return;
          default:
            printf("Opción no válida\n");
            break;
        }

        pause("Presione enter para continuar...");
      }
    } while (true);
  } else {
    pause("Presione enter para continuar...");
  }
}

/**
 * Opción 4 del menú principal
 * Muestra el valor del fondo a un mes determinado
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param email Correo electrónico
 * @param signature Firma de código
 */
void option4(double capital, double rate, const char* email, int signature) {
  if (check_signature(email, signature)) {
    int period;
    // Se convierte la tasa de interés a mensual
    double monthly_rate = convert_rate(rate / 100, QUARTERLY, MONTHLY);

    do {
      // Se solicita el mes mientras no se introduzca un valor válido
      printf("Mes [>=0] > ");
      scanf("%d", &period);
    } while (period < 0);

    // Se imprime el valor del fondo a un mes determinado
    printf(ROW_HEADER ROW ROW_FOOTER, period,
           capitalize(capital, monthly_rate, period),
           pow(1 + monthly_rate, period + 1) - 1,
           capitalize(capital, monthly_rate, period + 1));
  }
}



/**
 * Convierte una tasa de interés de un periodo a otro
 * @param rate Tasa de interés
 * @param orig Periodo de origen
 * @param dest Periodo de destino
 * @return Tasa de interés convertida
 */
double convert_rate(double rate, period_t orig, period_t dest) {
  return pow(1 + rate, (double)orig / dest) - 1;
}

/**
 * Capitaliza una renta a un periodo determinado
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param period Periodo
 * @return Capital final
 */
double capitalize(double capital, double rate, int period) {
  return capital * pow(1 + rate, period);
}

/**
 * Imprime un cuadro de simulación en un archivo
 * @param output Puntero al archivo de salida
 * @param capital Capital inicial
 * @param rate Tasa de interés
 * @param periods Periodos de capitalización
 */
void fprinttab(FILE* output, double capital, double rate, uint_t periods) {
  // Se convierte la tasa de interés a mensual
  double monthly_rate = convert_rate(rate / 100, QUARTERLY, MONTHLY);

  // Se imprime el encabezado del cuadro de simulación
  fprintf(output, TAB_HEADER ROW_HEADER, capital, rate, periods);

  // Se imprimen las filas del cuadro de simulación
  for (uint_t period = 0; period <= periods; period++) {
    fprintf(output, ROW, period, capitalize(capital, monthly_rate, period),
            pow(1 + monthly_rate, period + 1) - 1,
            capitalize(capital, monthly_rate, period + 1));
  }

  // Se imprime el pie del cuadro de simulación
  fprintf(output, ROW_FOOTER);
}

/**
 * Imprime un cuadro de simulación de tasas probables en un archivo
 * @param output Puntero al archivo de salida
 * @param capital Capital inicial
 * @param rates Tasas de interés
 * @param rates_len Longitud del arreglo de las tasas de interés
 * @param period Periodo de las tasas de interés
 */
void fprintsim(FILE* output,
               double capital,
               const double* rates,
               const int rates_len,
               period_t period) {
  double monthly_rate;

  // Se calcula la cantidad de subperiodos
  uint_t subperiods = MONTHLY / period - 1;

  // Se imprime el encabezado del cuadro de simulación
  fprintf(output, SIM_HEADER ROW_HEADER, capital);

  // Se imprimen las filas del cuadro de simulación
  for (uint_t count = 0, rate = 0; rate < rates_len; rate++) {
    // Se convierte la tasa de interés del periodo en el que se encuentra a
    // mensual
    monthly_rate = convert_rate(rates[rate] / 100, period, MONTHLY);

    // Se imprimen las filas del cuadro de simulación
    for (uint_t subperiod = 0; subperiod <= subperiods; subperiod++) {
      fprintf(output, ROW, count++,
              // Se capitaliza al subperiodo actual
              capitalize(capital, monthly_rate, subperiod),
              // Se calcula la tasa aplicada
              pow(1 + monthly_rate, subperiod + 1) - 1,
              // Se capitaliza al siguiente subperiodo
              capitalize(capital, monthly_rate, subperiod + 1));

      // Si se ha llegado al último subperiodo se capitaliza el capital
      if (subperiod == subperiods) {
        capital = capitalize(capital, monthly_rate, subperiod + 1);
      }
    }

    // Se imprime el pie del cuadro de simulación
    fprintf(output, ROW_FOOTER);
  }
}

/********************************************************
 * Definición de funciones de operación de firma
 *******************************************************/

/**
 * Calcula la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @return Firma de código
 */
int firma_de_codigo(const char* email) {
  nia_t nia;
  buffer_t sign;
  int odd = 0, even = 0;

  // Se obtiene el NIA del correo electrónico
  if (sscanf(email, SIGN_NIA_FORMAT, nia) != EOF) {
    // Se recorren sus caracteres
    for (int position = 0; position < SIGN_NIA_LEN; position++) {
      if (position % 2) {
        // Posición impar
        odd += nia[position] ^ SIGN_MASK_ODD;
      } else {
        // Posición par
        even += nia[position] ^ SIGN_MASK_EVEN;
      }
    }

    // Se obtiene la firma aplicando el módulo a ambas sumas
    sprintf(sign, "%02d%02d", odd % SIGN_MOD, even % SIGN_MOD);

    // Se retorna la firma como un entero
    return atoi(sign);
  }

  // Si no se pudo obtener la firma se retorna EOF
  return EOF;
}

/**
 * Comprueba la firma de un NIA contenido en un correo electrónico
 * @param email Correo electrónico
 * @param signature Firma de código
 * @return Éxito de la operación
 */
bool check_signature(const char* email, int signature) {
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
 * Lee una cadena de caracteres hasta encontrar un salto de línea
 * @param buffer Buffer de caracteres
 * @return Número de caracteres leídos
 */
int read(buffer_t buffer) {
  if (fgets(buffer, sizeof(buffer_t), stdin)) {
    // Se busca el salto de línea y se reemplaza por el fin de cadena
    buffer[strcspn(buffer, NEWLINE)] = EOS;
    // Se retorna la longitud de la cadena
    return strlen(buffer);
  }

  // Si no se pudo leer la cadena se retorna EOF
  return EOF;
}
