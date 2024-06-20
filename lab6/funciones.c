#include <stdio.h>

void funcion_B(char c) {
    if (c > 64) {
         funcion_B(c-1);
         printf("%c", c);
    } else
         printf("\n");
    return;
}

void funcion_A(char c) {
    if (c > 64) {
         printf("%c", c);
         funcion_A(c-1);
    } else
         printf("\n");
    return;
}

long calcular_A (long saldo) {
    long acum=0;
    if (saldo > 0) {
        acum +=1;
        acum += calcular_A (saldo -1 );
    } else
        acum=1;
    return acum;
}

long calcular_B (long saldo) {
    long acum=0;
    if (saldo > 0) {
        acum += calcular_B (saldo -1 );
        acum +=1;
     } else
        acum=2;
    return acum;
}

void dibuja(char c, int tamano, int tamano_ini) {
    if (tamano > 0) {
        printf("%c", c);
        dibuja(c, tamano-1, tamano_ini);
    } else {
        printf("\n");
        dibuja(c, tamano-1, tamano-1);
    }
    return;
}

int main() {
    //dibuja('*', 3, 3);

    //printf("calcular_A(12): %ld\ncalcular_B(12): %ld\n",
    //        calcular_A(12), calcular_B(12));

    printf("Ejecución funcion_A\n");
    funcion_A('E');
    printf("\n\nEjecución funcion_B\n");
    funcion_B('E');

    printf("\n");

    return 0;
}
