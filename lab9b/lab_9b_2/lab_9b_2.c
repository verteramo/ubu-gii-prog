/**
 * @file    lab_9b_2.c
 * @brief   Documentador de código
 * @version 1.0
 * @date    04/05/2024
 * @autor   Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @compile gcc -Wall -o lab_9b_2 lab_9b_2.c
 * @execute ./lab_9b_2
 */

/********************************************************
 * Librerías
 *******************************************************/

#include <ctype.h>
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

/** Nombre de la función principal */
#define MAIN "main"

/** Formato de mensaje de error de archivo */
#define FILE_ERROR "Error al abrir el fichero '%s' (%d: %s).\n"

/** Extensión de los archivos documentados */
#define OUTPUT_FILENAME "docs.c"

/********************************************************
 * Literales de tipos de datos en C
 *******************************************************/

/** Tamaño del arreglo de tipos de datos en C */
#define C_TYPES_SIZE 11

/** Tipos de datos en C */
#define C_TYPES                                                              \
  (const char*[]) {                                                          \
    "char", "double", "float", "int", "long", "short", "signed", "unsigned", \
        "void", "bool", "string"                                             \
  }

/********************************************************
 * Literales de formato
 *******************************************************/

/** Formato de fecha */
#define DATE_FORMAT "%02u/%02u/%04u"

/** Formato de versión */
#define VERSION_FORMAT "%u.%u.%u"

/********************************************************
 * Literales de valores por defecto
 *******************************************************/

/** Autor por defecto */
#define DEFAULT_AUTHOR "Desconocido"

/** Fecha por defecto */
#define DEFAULT_DATE "01/01/1970"

/** Versión por defecto */
#define DEFAULT_VERSION "1.0.0"

/** Descripción por defecto */
#define DEFAULT_DESCRIPTION "Sin descripción"

/** Fichero por defecto */
#define DEFAULT_FILE "codigo.c"

/********************************************************
 * Literales de interfaz
 *******************************************************/

/** Menú principal */
#define MENU                \
  "Documentador\n"          \
  "1. Autor    [%s]\n"      \
  "2. Fecha    [%s]\n"      \
  "3. Versión  [%s]\n"     \
  "4. Objetivo [%s]\n"      \
  "5. Documentar fichero\n" \
  "X. Salir\n"              \
  "Opción > "

/********************************************************
 * Literales de comentarios
 *******************************************************/

/** Comentario de cabecera */
#define COMMENT_HEADER                          \
  "/*\n"                                        \
  "-----------------------------------------\n" \
  "       Programa  : %s\n"                     \
  "       Autor     : %s\n"                     \
  "       Versión   : %s\n"                    \
  "       Fecha     : %s\n"                     \
  "       Nº líneas : %u\n"                   \
  "       Objetivo  : %s\n"                     \
  "-----------------------------------------\n" \
  "*/\n\n" COMMENT_PROTOTYPE

/** Comentario de función */
#define COMMENT_FUNCTION                        \
  "/*\n"                                        \
  "-----------------------------------------\n" \
  "Función  : %s()\n"                          \
  "Objetivo :\n"                                \
  "Versión  : %s\n\n"                            \
  "%s\n"                                        \
  "@return %s\n"                                \
  "-----------------------------------------\n" \
  "*/\n%s\n"

/** Comentario de parámetro */
#define COMMENT_PARAM "@param %s"

/** Comentario de prototipo */
#define COMMENT_PROTOTYPE "%s //Prototipo %s\n"

/** Comentario de variable */
#define COMMENT_VARIABLE "%s //Variable %s:\n"

/********************************************************
 * Tipos de datos
 *******************************************************/

/** Buffer de caracteres */
typedef char buffer_t[UCHAR_MAX + 1];

/** Entero sin signo */
typedef unsigned int uint_t;

/** Tipos de línea */
typedef enum line_type {
  COMMON,
  PREPROCESSOR,
  PROTOTYPE,
  VARIABLE,
  FUNCTION
} line_type_t;

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

/**
 * Elimina los espacios en blanco al principio y al final de una cadena
 * @param str Cadena a limpiar
 * @return Cadena limpia
 */
char* trim(char* str);

/********************************************************
 * Prototipos de funciones de identificación
 *******************************************************/

/**
 * Comprueba si un token es un tipo de dato en C
 * @param token Token a comprobar
 * @return true si el token es un tipo de dato, false en caso contrario
 */
bool is_type(const char* token);

/**
 * Obtiene el tipo de línea de una cadena de texto
 * @param line Cadena de texto
 * @return Tipo de línea
 */
line_type_t get_line_type(const char* line);

/**
 * Obtiene el nombre de una variable, función o prototipo
 * @param line Línea de código
 * @param name Nombre de la variable, función o prototipo
 */
void scan_name(const char* line, char* name);

/**
 * Obtiene los parámetros de una función
 * @param line Línea de código
 * @param parameters Parámetros de la función
 */
void scan_params(const char* line, char* parameters);

/**
 * Obtiene el tipo de una función
 * @param line Línea de código
 * @param type Tipo de la función
 */
void scan_type(const char* line, char* type);

/********************************************************
 * Prototipos de funciones de documentación
 *******************************************************/

/**
 * Cuenta las líneas de un fichero
 * @param file Fichero a contar
 * @return Número de líneas
 */
int count_lines(FILE* file);

/**
 * Comenta un fichero de código
 * @param output Fichero de salida
 * @param program Nombre del programa
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 * @param input Fichero de entrada
 */
void comment(FILE* output,
             const char* program,
             const char* author,
             const char* date,
             const char* version,
             const char* description,
             FILE* input);

/********************************************************
 * Prototipos de funciones de validación
 *******************************************************/

/**
 * Comprueba si un año es bisiesto
 * @param year Año a comprobar
 * @return true si el año es bisiesto, false en caso contrario
 */
bool is_leap_year(uint_t year);

/**
 * Comprueba si una fecha es válida
 * @param date Fecha a comprobar
 * @return true si la fecha es válida, false en caso contrario
 */
bool is_valid_date(const char* date);

/**
 * Comprueba si una versión es válida
 * @param version Versión a comprobar
 * @return true si la versión es válida, false en caso contrario
 */
bool is_valid_version(const char* version);

/********************************************************
 * Prototipos de funciones de interfaz
 *******************************************************/

/**
 * Menú principal
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 * @param default_file Fichero por defecto
 * @return Código de salida
 */
int menu(buffer_t author,
         buffer_t date,
         buffer_t version,
         buffer_t description,
         const char* default_file);

/**
 * Establece el autor del documento
 * @param author Autor del documento
 */
void set_author(buffer_t author);

/**
 * Establece la fecha del documento
 * @param date Fecha del documento
 */
void set_date(buffer_t date);

/**
 * Establece la versión del documento
 * @param version Versión del documento
 */
void set_version(buffer_t version);

/**
 * Establece la descripción del documento
 * @param description Descripción del documento
 */
void set_description(buffer_t description);

/**
 * Documenta un fichero de código
 * @param default_file Fichero por defecto
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 */
void document(const char* default_file,
              const char* author,
              const char* date,
              const char* version,
              const char* description);

/********************************************************
 * Función principal
 *******************************************************/

int main() {
  // Configuración por defecto
  buffer_t author = DEFAULT_AUTHOR;
  buffer_t date = DEFAULT_DATE;
  buffer_t version = DEFAULT_VERSION;
  buffer_t description = DEFAULT_DESCRIPTION;

  // Menú principal
  return menu(author, date, version, description, DEFAULT_FILE);
}

/********************************************************
 * Definición de funciones de interfaz
 *******************************************************/

/**
 * Menú principal
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 * @param default_file Fichero por defecto
 * @return Código de salida
 */
int menu(buffer_t author,
         buffer_t date,
         buffer_t version,
         buffer_t description,
         const char* default_file) {
  char option;

  do {
    // Se muestra el menú principal
    clear();
    printf(MENU, author, date, version, description);

    // Se lee la opción seleccionada
    if (scanf(" %c", &option) == 1) {
      clear();

      // Se ejecuta la opción seleccionada
      switch (option) {
        case '1':
          set_author(author);
          break;
        case '2':
          set_date(date);
          break;
        case '3':
          set_version(version);
          break;
        case '4':
          set_description(description);
          break;
        case '5':
          document(default_file, author, date, version, description);
          break;
        case 'x':
        case 'X':
          // Se sale del programa
          return EXIT_SUCCESS;
        default:
          printf("Opción incorrecta\n");
      }
    }
  } while (true);
}

/**
 * Establece el autor del documento
 * @param author Autor del documento
 */
void set_author(buffer_t author) {
  buffer_t read_author;

  printf("Autor [%s] > ", author);

  if (read(read_author)) {
    strcpy(author, read_author);
  }
}

/**
 * Establece la fecha del documento
 * @param date Fecha del documento
 */
void set_date(buffer_t date) {
  buffer_t read_date;

  printf("Fecha [%s] > ", date);

  if (read(read_date)) {
    // Se comprueba si la fecha es válida
    if (is_valid_date(read_date)) {
      strcpy(date, read_date);
    } else {
      fprintf(stderr, "Fecha inválida\n");
    }
  }
}

/**
 * Establece la versión del documento
 * @param version Versión del documento
 */
void set_version(buffer_t version) {
  buffer_t read_version;

  printf("Versión [%s] > ", version);

  if (read(read_version)) {
    // Se comprueba si la versión es válida
    if (is_valid_version(read_version)) {
      strcpy(version, read_version);
    } else {
      fprintf(stderr, "Versión inválida\n");
    }
  }
}

/**
 * Establece la descripción del documento
 * @param description Descripción del documento
 */
void set_description(buffer_t description) {
  buffer_t read_description;

  printf("Objetivo [%s] > ", description);

  if (read(read_description)) {
    strcpy(description, read_description);
  }
}

/**
 * Documenta un fichero de código
 * @param default_file Fichero por defecto
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 */
void document(const char* default_file,
              const char* author,
              const char* date,
              const char* version,
              const char* description) {
  FILE *input, *output;
  buffer_t input_filename, output_filename;

  // Se solicita el nombre del fichero de entrada
  printf("Fichero de entrada [%s] > ", default_file);

  // Si no se introduce un nombre se toma el fichero por defecto
  if (!read(input_filename)) {
    strcpy(input_filename, default_file);
  }

  // Se abre el fichero de entrada
  input = fopen(input_filename, "r");

  // Se documenta el fichero
  if (input) {
    // Se abre el fichero de salida
    output = fopen(OUTPUT_FILENAME, "w");

    if (output) {
      // Se comenta el fichero de código
      comment(stdout, input_filename, author, date, version, description,
              input);
    } else {
      // Se muestra un mensaje de error si no se puede abrir el fichero de
      // salida
      fprintf(stderr, FILE_ERROR, output_filename, errno, strerror(errno));
    }

    fclose(input);
  } else {
    // Se muestra un mensaje de error si no se puede abrir el fichero de entrada
    fprintf(stderr, FILE_ERROR, input_filename, errno, strerror(errno));
  }

  // Se pausa la ejecución del programa
  pause("Documentación generada.\nPresione enter para continuar...");
}

/********************************************************
 * Definición de funciones de documentación
 *******************************************************/

/**
 * Cuenta las líneas de un fichero
 * @param file Fichero a contar
 * @return Número de líneas
 */
int count_lines(FILE* file) {
  int lines = 0;
  buffer_t line;

  // Se cuentan las líneas del fichero
  while (fgets(line, sizeof(buffer_t), file)) {
    lines++;
  }

  // Se retorna el número de líneas
  return lines;
}

/**
 * Comenta un fichero de código
 * @param output Fichero de salida
 * @param program Nombre del programa
 * @param author Autor del documento
 * @param date Fecha del documento
 * @param version Versión del documento
 * @param description Descripción del documento
 * @param input Fichero de entrada
 */
void comment(FILE* output,
             const char* program,
             const char* author,
             const char* date,
             const char* version,
             const char* description,
             FILE* input) {
  uint_t lines;
  buffer_t line, name, params, type;
  bool preprocessor;

  // Se cuenta el número de líneas del fichero
  lines = count_lines(input);
  // Se reinicia el puntero del fichero
  rewind(input);

  // Se lee línea a línea el fichero de entrada
  while (fgets(line, sizeof(buffer_t), input)) {
    // Se elimina el salto de línea
    line[strlen(line) - 2] = EOS;

    // Se identifica el tipo de línea
    switch (get_line_type(line)) {
      case PREPROCESSOR:
        // Si es un preprocesador se añade tal cual
        preprocessor = true;
        fprintf(output, "%s\n", line);
        break;

      case PROTOTYPE:
        // Si es un prototipo se obtiene el nombre
        scan_name(line, name);

        // Si le precede un preprocesador se añade el comentario de cabecera
        if (preprocessor) {
          fprintf(output, COMMENT_HEADER, program, author, version, date, lines,
                  description, line, name);
          preprocessor = false;
        } else {
          fprintf(output, COMMENT_PROTOTYPE, line, name);
        }
        break;

      case VARIABLE:
        // Si es una variable se obtiene el nombre y se añade un comentario
        scan_name(line, name);
        fprintf(output, COMMENT_VARIABLE, line, name);
        break;

      case FUNCTION:
        // Si es una función se obtiene el nombre, los parámetros y el tipo
        scan_name(line, name);

        // Si no es la función principal se añade un comentario de función
        if (strcmp(name, MAIN) != 0) {
          scan_params(line, params);
          scan_type(line, type);
          fprintf(output, COMMENT_FUNCTION, name, version, params, type, line);
        } else {
          fprintf(output, "%s\n", line);
        }

        break;

      default:
        // Si es una línea de código normal se añade tal cual
        fprintf(output, "%s\n", line);
        break;
    }
  }
}

/********************************************************
 * Prototipos de funciones de identificación
 *******************************************************/

/**
 * Comprueba si un token es un tipo de dato en C
 * @param token Token a comprobar
 * @return true si el token es un tipo de dato, false en caso contrario
 */
bool is_type(const char* token) {
  for (uint_t type = 0; type < C_TYPES_SIZE; type++) {
    // Si el token es un tipo de dato en C se retorna verdadero
    if (strcmp(token, C_TYPES[type]) == 0) {
      return true;
    }
  }

  return false;
}

/**
 * Obtiene el tipo de línea de una cadena de texto
 * @param line Cadena de texto
 * @return Tipo de línea
 */
line_type_t get_line_type(const char* line) {
  char *token, *trimmed;
  buffer_t buffer;

  /**
   * Los caracteres literales como numeral, paréntesis, punto y coma, etc.
   * se utilizan tal cual, la sobrecarga que supondría definirlos con
   * directivas de preprocesador no aportaría una ganancia justificada de
   * claridad.
   */

  // Se copia la línea en un buffer para no modificar la original
  strcpy(buffer, line);
  // Se eliminan los espacios en blanco al principio y al final de la línea
  trimmed = trim(buffer);

  // Si la línea no está vacía
  if (strlen(trimmed)) {
    // Si la línea comienza con un numeral es un preprocesador
    if (trimmed[0] == '#') {
      return PREPROCESSOR;
    }

    // Se obtiene el primer token de la línea
    token = strtok(trimmed, " ");

    if (is_type(token)) {
      // Se saltan los tipos de datos
      while (is_type(token)) {
        token = strtok(NULL, " ");
      }

      if (strchr(line, '(')) {
        // Si tiene paréntesis es una función o un prototipo
        if (strchr(line, ';')) {
          // Si tiene punto y coma es un prototipo
          return PROTOTYPE;
        } else {
          // Si no tiene punto y coma es una función
          return FUNCTION;
        }
      } else {
        // Si no tiene paréntesis es una variable
        return VARIABLE;
      }
    }
  }

  // Si no se cumple ninguna condición es una línea de código común
  return COMMON;
}

/**
 * Obtiene el nombre de una variable, función o prototipo
 * @param line Línea de código
 * @param name Nombre de la variable, función o prototipo
 */
void scan_name(const char* line, char* name) {
  char* token;
  buffer_t buffer;

  // Se copia la línea en un buffer para no modificar la original
  strcpy(buffer, line);
  // Se obtiene el primer token de la línea
  token = strtok(trim(buffer), " ");

  // Se saltan los tipos de datos de la línea
  while (is_type(token)) {
    token = strtok(NULL, " ");
  }

  // Solo caracteres permitidos en identificadores (tema 1)
  for (uint_t i = 0; i < strlen(token); i++) {
    // Si no es un carácter alfanumérico o un guion bajo
    // se elimina el resto de la cadena
    if (!isalnum(token[i]) && token[i] != '_') {
      token[i] = EOS;
      break;
    }
  }

  // Se copia el token en el nombre
  strcpy(name, token);
}

/**
 * Obtiene los parámetros de una función
 * @param line Línea de código
 * @param parameters Parámetros de la función
 */
void scan_params(const char* line, char* parameters) {
  char *token, *param;
  buffer_t buffer, param_str;

  // Se copia la línea en un buffer para no modificar la original
  strcpy(buffer, line);
  // Se vacía el buffer de parámetros
  strcpy(parameters, "");

  // Se busca el primer paréntesis de apertura
  token = strtok(buffer, "(");
  // Se busca el token a la derecha del paréntesis
  token = strtok(NULL, "(");
  // Se omiten los caracteres sobrantes
  token = trim(strtok(token, "){"));

  // Si hay parámetros
  if (strlen(token)) {
    // Se obtiene el primer parámetro
    param = strtok(token, ",");

    // Mientras haya parámetros
    while (param) {
      // Si el buffer no está vacío
      if (strlen(parameters)) {
        // Se añade un salto de línea
        strcat(parameters, "\n");
      }
      // Se añade el comentario de parámetro
      sprintf(param_str, COMMENT_PARAM, trim(param));
      // Se acumulan los parámetros en el buffer
      strcat(parameters, param_str);
      // Se obtiene el siguiente parámetro
      param = strtok(NULL, ",");
    }
  }
}

/**
 * Obtiene el tipo de una función
 * @param line Línea de código
 * @param type Tipo de la función
 */
void scan_type(const char* line, char* type) {
  char* token;
  buffer_t buffer;

  // Se copia la línea en un buffer para no modificar la original
  strcpy(buffer, line);
  // Se vacía el buffer de tipo
  strcpy(type, "");

  // Se obtiene el primer token de la línea
  token = strtok(buffer, " ");

  // Mientras el token sea un tipo de dato
  if (is_type(token)) {
    while (is_type(token)) {
      // Si el buffer no está vacío
      if (strlen(type)) {
        // Se añade un espacio en blanco
        strcat(type, " ");
      }

      // Se acumulan los tipos de datos en el buffer
      strcat(type, token);

      // Se obtiene el siguiente token
      token = strtok(NULL, " ");
    }
  }
}

/********************************************************
 * Definición de funciones de validación
 *******************************************************/

/**
 * Comprueba si un año es bisiesto
 * @param year Año a comprobar
 * @return true si el año es bisiesto, false en caso contrario
 */
bool is_leap_year(uint_t year) {
  // Un año es bisiesto si es divisible por 4 y
  // no es divisible por 100 o es divisible por 400
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
 * Comprueba si una fecha es válida
 * @param date Fecha a comprobar
 * @return true si la fecha es válida, false en caso contrario
 */
bool is_valid_date(const char* date) {
  uint_t year, month, day;

  // Se comprueba si la fecha tiene el formato correcto
  if (sscanf(date, DATE_FORMAT, &day, &month, &year) == 3) {
    if (day >= 1 || month >= 1 || month <= 12 || year >= 1) {
      switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
          // Se comprueba si el día es válido para meses con 31 días
          return day <= 31;
        case 4:
        case 6:
        case 9:
        case 11:
          // Se comprueba si el día es válido para meses con 30 días
          return day <= 30;
        case 2:
          // Se comprueba si el día es válido para febrero
          return day <= (is_leap_year(year) ? 29 : 28);
      }
    }
  }

  return false;
}

/**
 * Comprueba si una versión es válida
 * @param version Versión a comprobar
 * @return true si la versión es válida, false en caso contrario
 */
bool is_valid_version(const char* version) {
  uint_t major, minor, patch;
  // Se comprueba si la versión tiene el formato correcto
  // Se permite que la versión tenga solo el número mayor en adelante
  return sscanf(version, VERSION_FORMAT, &major, &minor, &patch) >= 1;
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
  return getchar();
}

/**
 * Lee una cadena de caracteres hasta encontrar un salto de línea
 * @param buffer Buffer de caracteres
 * @return Número de caracteres leídos
 */
int read(buffer_t buffer) {
  fclean(stdin);
  if (fgets(buffer, sizeof(buffer_t), stdin)) {
    // Se elimina el salto de línea
    buffer[strcspn(buffer, NEWLINE)] = EOS;
    // Se retorna el número de caracteres leídos
    return strlen(buffer);
  }

  // Si no se ha leído nada se retorna EOF
  return EOF;
}

/**
 * Elimina los espacios en blanco al principio y al final de una cadena
 * @param str Cadena a limpiar
 * @return Cadena limpia
 */
char* trim(char* str) {
  char* end;

  // Avanza el puntero mientras se encuentren espacios al principio
  while (isspace(*str)) {
    str++;
  }

  if (str) {
    // Retrocede el puntero mientras se encuentren espacios al final
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
      end--;
    }

    // Añade el carácter de fin de cadena
    end[1] = EOS;
  }

  // Retorna la posición del primer carácter no espacio
  return str;
}
