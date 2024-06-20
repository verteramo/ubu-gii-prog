/*Directiva al preprocesador*/
#include<stdio.h>
#define N 5/*cte.*/

/*Definición de la función ppal.*/
int main(){

 printf("%u *%2u =%4u\t%o *%2o =%4o\t%X *%2X =%4X\n",0,N, 0,0,N, 0,0,N, 0);
 printf("%u *%2u =%4u\t%o *%2o =%4o\t%X *%2X =%4X\n",1,N, 5,1,N, 5,1,N, 5);
 printf("%u *%2u =%4u\t%o *%2o =%4o\t%X *%2X =%4X\n",2,N,10,2,N,10,2,N,10);

 return 0;
}
