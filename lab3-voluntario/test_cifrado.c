/**
 * @file    test_cifrado.c
 * @brief   Programa para el cifrado/descifrado de contraseñas.
 * @author  Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
 * @date    2021-10-14
 * @compile gcc -Wall -o test_cifrado test_cifrado.c
 * @execute ./test_cifrado
 */

/********************************************************
 * Librerías
 *******************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************
 * Literales auxiliares
 *******************************************************/

/** Carácter mínimo */
#define MIN 'A'

/** Carácter máximo */
#define MAX 'Z'

/** Carácter nulo */
#define NUL '\0'

/** Longitud de la contraseña */
#define LENGTH 5

/** Máscara para el cifrado */
#define MASK 0b1100

/** Máscara para los bits de menor peso */
#define LMASK 0b11

/** Máscara para los bits de mayor peso */
#define HMASK MASK

/********************************************************
 * Tipos de datos
 *******************************************************/

/**
 * No son tipos de datos estrictamente necesarios,
 * pero aumentan la legibilidad y semántica del código.
 */

/** Byte */
typedef char byte;

/** Contraseña */
typedef char password[LENGTH + 1];

/********************************************************
 * Prototipos de funciones
 *******************************************************/

/**
 * @brief Verifica si un carácter es una letra A-Z.
 * @param ch Carácter a verificar.
 * @return true si el carácter es una letra A-Z, false en caso contrario.
 */
bool is_valid_char(char ch);

/**
 * @brief Aplica una máscara a un carácter (Fase 1).
 * @param ch Carácter a filtrar.
 * @param mask Máscara a aplicar.
 * @return Carácter filtrado.
 */
char filter(char ch, byte mask);

/**
 * @brief Intercambia los bits de un carácter (Fase 2).
 * @param ch Carácter a intercambiar.
 * @param hmask Máscara para los bits de mayor peso.
 * @param lmask Máscara para los bits de menor peso.
 * @return Carácter con los bits intercambiados.
 */
char exchange(char ch, byte hmask, byte lmask);

/**
 * @brief Cifra un carácter.
 * @param ch Carácter a cifrar.
 * @param mask Máscara a aplicar.
 * @param hmask Máscara para los bits de mayor peso.
 * @param lmask Máscara para los bits de menor peso.
 * @return Carácter cifrado.
 */
char encoder(char ch, byte mask, byte hmask, byte lmask);

/**
 * @brief Descifra un carácter.
 * @param ch Carácter a descifrar.
 * @param mask Máscara a aplicar.
 * @param hmask Máscara para los bits de mayor peso.
 * @param lmask Máscara para los bits de menor peso.
 * @return Carácter descifrado.
 */
char decoder(char ch, byte mask, byte hmask, byte lmask);

/**
 * @brief Verifica si una cadena de caracteres es válida.
 * @param passwd Cadena de caracteres a verificar.
 * @return true si la cadena es válida, false en caso contrario.
 */
bool is_valid_string(const char* passwd);

/**
 * @brief Cifra una cadena de caracteres.
 * @param passwd Cadena de caracteres a cifrar.
 * @return Cadena de caracteres cifrada.
 */
void crypt(char* passwd);

/**
 * @brief Descifra una cadena de caracteres.
 * @param passwd Cadena de caracteres a descifrar.
 * @return Cadena de caracteres descifrada.
 */
void decrypt(char* passwd);

/********************************************************
 * Función principal
 *******************************************************/

int main() {
  password passwd;

  printf("Contraseña ([A-Z]{5}) > ");
  scanf("%s", passwd);

  // Verificación de la contraseña
  if (strlen(passwd) != LENGTH || !is_valid_string(passwd)) {
    fprintf(stderr, "Error: Contraseña inválida\n");
    return EXIT_FAILURE;
  }

  // Cifrado de la contraseña
  crypt(passwd);
  printf("Contraseña cifrada > '%s'\n", passwd);

  // Descifrado de la contraseña
  decrypt(passwd);
  printf("Contraseña descifrada > '%s'\n", passwd);

  return EXIT_SUCCESS;
}

/********************************************************
 * Definición de funciones
 *******************************************************/

/** Verifica si un carácter es una letra A-Z. */
bool is_valid_char(char ch  // Carácter a verificar.
) {
  return ch >= MIN && ch <= MAX;
}

/** Aplica una máscara a un carácter (Fase 1). */
char filter(char ch,   // Carácter a filtrar.
            byte mask  // Máscara a aplicar.
) {
  return ch ^ mask;
}

/** Intercambia los bits de un carácter (Fase 2). */
char exchange(char ch,     // Carácter a intercambiar.
              byte hmask,  // Máscara para los bits de mayor peso.
              byte lmask   // Máscara para los bits de menor peso.
) {
  return ((ch & hmask) >> 2) | ((ch & lmask) << 2) | (ch >> 4 << 4);
}

/** Cifra un carácter. */
char encoder(char ch,     // Carácter a cifrar.
             byte mask,   // Máscara a aplicar.
             byte hmask,  // Máscara para los bits de mayor peso.
             byte lmask   // Máscara para los bits de menor peso.
) {
  return exchange(filter(ch, mask), hmask, lmask);
}

/** Descifra un carácter. */
char decoder(char ch,     // Carácter a descifrar.
             byte mask,   // Máscara a aplicar.
             byte hmask,  // Máscara para los bits de mayor peso.
             byte lmask   // Máscara para los bits de menor peso.
) {
  return filter(exchange(ch, hmask, lmask), mask);
}

/** Verifica si una cadena de caracteres es válida. */
bool is_valid_string(const char* passwd  // Cadena de caracteres a verificar.
) {
  return *passwd == NUL ||
         (is_valid_char(*passwd) && is_valid_string(++passwd));
}

/** Cifra una cadena de caracteres. */
void crypt(char* passwd  // Cadena de caracteres a cifrar.
) {
  if (*passwd != NUL) {
    *passwd = encoder(*passwd, MASK, HMASK, LMASK);
    crypt(++passwd);
  }
}

/** Descifra una cadena de caracteres. */
void decrypt(char* passwd  // Cadena de caracteres a descifrar.
) {
  if (*passwd != NUL) {
    *passwd = decoder(*passwd, MASK, HMASK, LMASK);
    decrypt(++passwd);
  }
}
