#include<stdio.h>
enum Dias_Sem {DOMINGO, LUNES, MARTES, MIERCOLES, JUEVES, VIERNES, SABADO};

int main(){
  enum Dias_Sem dia_sem;
  unsigned dia, mes, anno,m,a;

 printf("Introduce una fecha del calendario gregoriano(dd mm aaa)");
     scanf("%u%u%u", &dia, &mes, &anno);

     m = mes + 9;
     a = (anno + m/12 -1)%1600;
     m%=12;
     dia_sem = (2 + a + a/4 - a/100 + a/400 +
               m*2 + (m/5)*3 + (m%5+1)/2
               + dia) %7;
     printf("considerando\t%u: Lunes\n", LUNES);
     printf(            "\t\t%u: Martes\n", MARTES);
     printf(            "\t\t%u: Miércoles\n", MIERCOLES);
     printf(            "\t\t%u: Jueves\n", JUEVES);
     printf(            "\t\t%u: Viernes\n", VIERNES);
     printf(            "\t\t%u: Sábado\n", SABADO);
     printf(            "\t\t%u: Domingo\n", DOMINGO);
     printf("el %02u/%.2u/%4u es %u\n", dia, mes, anno, dia_sem);

     return 0;
}



