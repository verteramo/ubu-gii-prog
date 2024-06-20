/**
 * Constantes
 */

// Longitud del NIA
#define NIA_LEN 8

/**
 * Tipos de datos
 */

// Está definido en el ejercicio 1,
// se vuelve a definir aquí para evidenciar la dependencia
typedef unsigned int uint;

// Tipo de dato NIA
typedef char nia_t[NIA_LEN];

/*
**************************************************
@author: Marcelo Verteramo Pérsico <mvp1011@alu.ubu.es>
@version: 1.0
@date: 10/04/2024
@function: firma_de_codigo
@objetivo: ofrecer la firma de código personalizada por alumno
@param1: email (por referencia) - email del alumno
@return: el resto de la división por 64 de la suma
         de los valores ASCII de los caracteres del NIA
**************************************************
*/
int firma_de_codigo(char* email) {
  nia_t nia;
  uint suma = 0;

  // Se extraen los primeros 7 caracteres del email
  sscanf(email, "%7s", nia);

  // Se suman los valores ASCII de los caracteres del NIA
  for (int i = 0; i < NIA_LEN - 1; i++) {
    suma += (int)nia[i];
  }

  // Se devuelve el resto de la división por 64 de la suma
  return suma % 64;
}
