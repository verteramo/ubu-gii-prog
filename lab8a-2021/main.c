/**
 * Lab8A
 * Autor: Marcelo Verteramo Pérsico (mvp1011)
 * Fecha: Marzo 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Manejo de entrada salida
 */

#ifdef WIN32
  #define clear() system("cls")
#else //UNIX
  #define clear() system("clear")
#endif

#define clean() scanf("%*s")
#define getkey() fgetc(stdin); getchar()
#define wait(prompt) printf(prompt); getkey()
#define error(message) fprintf(stderr, message)

/**
 * Modos de apertura de fichero
 */
#define EOS             '\0'
#define EOL             '\n'
#define READ_MODE       "r"
#define WRITE_MODE      "w"
#define APPEND_MODE     "a"
#define CREATE_MODE     "w+"
#define READWRITE_MODE  "r+"
#define READAPPEND_MODE "a+"

/**
 * Ficheros de texto
 */
#define NAMES_FNAME "titanic_names.csv"
#define DATA_FNAME  "titanic_data.csv"
#define BIN_FNAME   "titanic.bin"

#define MENU                                   \
  "Lab8A - Titanic\n"                          \
  "----------------------------------------\n" \
  "0. Configuración e inicialización\n"        \
  "1. Lista de embarque\n"                     \
  "2. Búsqueda de un pasajero\n"               \
  "3. Estadísticas de embarque\n"              \
  "4. Estadísticas de superviviencia\n"        \
  "5. Agregar un polizón\n"                    \
  "6. Lectura de binarios\n"                   \
  "7. Cambio de parámetros de configuración\n" \
  "8. Salir\n"                                 \
  "Opción: "

#define MAX_NAME 127

typedef enum { false, true } bool;
typedef enum { male, female } sex;
typedef enum { first = 1, second, third } class;

typedef struct {
  bool survivor;
  float age;
  sex sex;
  class class;
} data;

typedef struct {
    char name[MAX_NAME];
    data data;
} passenger;

int menu();
int count_lines(char *fname);

int read_line(FILE *file, int max, char *output);
data read_data(FILE *file);
passenger* read_passengers(int lines, char *names_fname, char *data_fname);
int print_passengers(passenger *list);
void initialize();

int main(int argc, char **argv) {
  passenger *passengers = NULL;
  int lines = count_lines(NAMES_FNAME);

  if(lines != count_lines(DATA_FNAME)) {
    error("Los ficheros no poseen el mismo número de líneas\n");
    return EXIT_FAILURE;
  }

  FILE *csv = fopen(NAMES_FNAME, READ_MODE);

  char name[MAX_NAME];
  read_line(csv, MAX_NAME, name);

  printf("%s\n", name);

  return EXIT_SUCCESS;
  //return menu();
}

//passenger* read_passengers(int lines, char *names_fname, char* data_fname) {
//  passenger passengers[lines];
//  FILE *fnames = fopen(names_fname, READ_MODE);
//  FILE *fdata  = fopen(data_fname, READ_MODE);
//
//  while(!feof(fnames) && !feof(fdata)) {
//    passenger passenger;
//    passenger.name = read_line(fnames, MAX_NAME);
//    passenger.data = read_data(fdata);
//  }
//}

int read_line(FILE *file, int max, char *output) {
  char c;
  int chars = 0;
  do {
    c = fgetc(file);
    memcpy(output, &c, 1);
    chars++;
  } while(c != EOS);
  return chars;
}

data read_data(FILE *file) {
  data data;
  scanf("%u,%f,%u,%u\n", &data.survivor, &data.age, &data.sex, &data.class);
  return data;
}

int count_lines(char *fname) {
  char character;
  int lines = 0;
  FILE *file = fopen(fname, READ_MODE);

  if(file != NULL) {
    do {
      if((character = fgetc(file)) == EOL) {
        lines++;
      }
    } while(character != EOF);
  }

  return lines;
}

void initialize() {
  
}

int menu() {
  int option;

  do {
    clear();
    printf(MENU);

    if(scanf("%d", &option) == 1) {
      switch(option) {
        case 0: // Configuración e inicialización
          break;

        case 1: // Lista de embarque
          break;
  
        case 2: // Búsqueda de un pasajero
          break;
  
        case 3: // Estadísticas de embarque
          break;
  
        case 4: // Estadísticas de superviviencia
          break;
  
        case 5: // Agregar un polizón
          break;
  
        case 6: // Lectura de binarios
          break;
  
        case 7: // Cambio de parámetros de configuración
          break;
  
        case 8:
          printf("Muchas gracias, hasta pronto!\n");
          return EXIT_SUCCESS;

        default:
          error("Opción incorrecta.\n");
          wait("Pulse <ENTER> para continuar ...");
          break;
      }
    }
    else {
      clean();
      error("Entrada incorrecta.\n");
      wait("Pulse <ENTER> para continuar...");
    }
  } while(option != 8);
}

