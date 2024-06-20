#include <stdio.h>

long Fibonacci(int k) {
    printf("Llamada: Fibonacci(%d)\n", k);
	long fibo=0;	         //variable auxiliar para el cálculo
	if (k==0 || k==1)	//Puntos de salida de la recursividad
		fibo=(long)1;
	else
		//Caso general: cálculo recursivo
		fibo = Fibonacci(k-1) + Fibonacci(k-2);
	return fibo;
}

int main() {
    printf("Fibonacci(5): %ld\n", Fibonacci(5));
    return 0;
}
