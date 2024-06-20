#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int crc(const char* ordinal);

int crc(const char* ordinal) {
  // Caso base: cuando llegamos al final de la cadena
  if (*ordinal == '\0')
    return 0;

  // Convertir el dígito de carácter a entero
  int digito =
      *ordinal -
      '0';  // Restar el código ASCII de '0' para obtener el valor numérico

  // Calcular el XOR con la máscara 12 y llamar recursivamente con el siguiente
  // dígito
  return (digito ^ 12) + crc(ordinal + 1);
}
