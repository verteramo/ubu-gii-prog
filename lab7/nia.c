#include <string.h>

int firma_de_codigo(char *NIA) {
    int suma = 0;
    int i;
    int longitud = strlen(NIA);

    // Sumar los valores ASCII de los caracteres del NIA
    for (i = 0; i < longitud; i++) {
        suma += (int)NIA[i];
    }

    // Calcular el resto de la división entre 64
    int resto = suma % 64;

    return resto;
}

int main() {
    char email[] = "abc1234@alu.ubu.es";
    char NIA[8]; // Tamaño 8 para incluir el carácter nulo '\0'
    
    // Extraer el NIA del email
    sscanf(email, "%7s", NIA);

    // Calcular y mostrar la firma de código
    printf("Firma de código para el NIA %s: %d\n", NIA, firma_de_codigo(NIA));

    return 0;
}
