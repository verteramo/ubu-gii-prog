#ifndef _C_FACIL_H
# define _C_FACIL_H
/*archivo cabecera C con definiciones de tipos, ctes y macros para entrada/salida de datos en pantalla, version simplificada,
  @autor CPA@LSI.UBu
  @version 1/oct/2014
  @licencia CC-BY-NC-SA
  objetivo: ocultar inicialmente los detalles de la E/S al aprender a programar*/
	//COMENTARIOS NECESARIOS DE CABECERA DE PROGRAMA
# ifndef PROGRAMA
#  error No definida constante PROGRAMA, con el nombre del programa en la primera línea (antes de #include"c_facil.h")
# endif
# ifndef DESCRIPCION
#  error No definida constante DESCRIPCION, con la descripción del programa (antes de #include"c_facil.h")
# endif
# ifndef AUTOR
#  error No definida constante AUTOR, con el/los autor/es del programa, incluir el grupo y el ordenador (antes de #include"c_facil.h")
# endif
# ifndef VERSION
#  error No definida constante VERSION, con la version del programa. Ej: v1.3 de 21/dic/2012 (antes de #include"c_facil.h")
# endif

	//TIPOS BÁSICOS y su Entrada/Salida básica
# include<stdio.h>
//N: entrada/salida de números naturales en base 10, en base 8 y en base 16 (Prg.T2)
typedef unsigned NATURAL;	//uso: NATURAL num;
# define escribeNaturalB8(num)	 printf("%#o",(num))
# define escribeNaturalB16(num)	 printf("%#x",(num))
# define escribeNaturalB10(num)	 printf("%u",(num))
# define escribeNatural(num)	 escribeNaturalB10(num)
# define escribeNaturalOps(base, minCols, minDigits, num)		\
				 printf((base)==16?"%*.*x"		\
					:(base)==8?"%*.*o":"%*.*u",	\
					(minCols),(minDigits),(num))
# define leeNatural(dir_var)	 scanf("%u",(dir_var))
//Z: entrada/salida de números enteros (Prg.T2)
typedef int ENTERO;		//uso: ENTERO num;
# define escribeEntero(num)	 printf("%d",(num))
# define escribeEnteroOps(signo,minCols, minDigits, num)		\
				 printf((signo)=='+'?"%+*.*d":"%*.*d",	\
					(minCols),(minDigits),(num))
# define leeEntero(dir_var)	 scanf("%i",(dir_var))
//la nada (Prg.T3)
typedef void PROCEDIMIENTO;
typedef void NADA;
//Q: entrada/salida de números racionales (Prg.T4)
typedef double RACIONAL;	//uso: RACIONAL x;
# define escribeNumero(x)	 printf("%g", (x))
# define escribeNumeroSigno(x)	 printf("%+g",(x))
# define escribeNumeroPuntoFijo(minCols, nDecimales, x)			\
				 printf("%*.*f",(minCols),(nDecimales),(x))
# define escribeNumeroCientifico(minCols, nDecimales, x)		\
				 printf("%*.*e",(minCols),(nDecimales),(x))
# define leeNumero(dir_var)	 scanf("%lg",(dir_var))
//Caracteres: entrada/salida de símbolos (Prg.T4)
typedef unsigned char CARACTER;
# define escribeCaracter(c)	 printf("%c",(c))
# define leeCaracter(dir_var)	 scanf("%c",(dir_var))
//Cadenas: entrada/salidas de frases (Prg.TA)
typedef char *FRASE;
# define escribeFrase(s)	 printf("%s",(s))

	//funciones de entrada/salida (con secuencias ANSI)
enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
# define activaColor(color)	 printf("\33[%um",(color))
# define desactivaTintaFondo()	 activaColor(0)
# define activaTinta(color)	 activaColor(30+((color)&7))
# define activaFondo(color)	 activaColor(40+((color)&7))
# define mueveCursor(fila,col)		printf("\33[%u;%uH",(fila),(col))
# define recuerdaPosicionCursor()	printf("\33[s")
# define mueveCursorPosicionRecordada()	printf("\33[u")
# define cls_()				printf("\33[2J")
# define cls()				mueveCursor(1,1)+cls_()
//leer (y olvidar) una línea del teclado, dejando el buffer de teclado vacío
# define readLN()		 (scanf("%*[^\n]")<0?-1:scanf("%*c"))
//idem poniendo un mensaje de pausa
# define pausa()	(activaFondo(WHITE),activaTinta(BLUE),		\
			 escribeFrase("Pulsa <ENTER> para seguir"),	\
			 desactivaTintaFondo(),readLN())

//paso por referencia, calcular la dirección de memoria de una variable y el contenido de una dirección
typedef unsigned *DIREC_MEM_NATURAL;
typedef int *DIREC_MEM_ENTERO;
typedef double *DIREC_MEM_RACIONAL;
# define dirMem(var)			 &(var)
# define contenido(dir)			 *(dir)
//operaciones aritméticas: Nº <= operacion(Nº, Nº)
# define productoNumeros(op1,op2)	 ((op1)*(op2))
# define divisionNumeros(op1,op2)	 ((RACIONAL)(op1)/(op2))
# define cocienteEnteros(op1,op2)	 ((ENTERO)((op1)/(op2)))
# define restoEnteros(op1,op2)		 ((op1)%(op2))
# define sumaNumeros(op1,op2)		 ((op1)+(op2))
# define restaNumeros(op1,op2)		 ((op1)-(op2))
//operaciones relacionales: Lógico <= operacion(Nº, Nº)
# define siIgualValor(op1, op2)		 ((op1)==(op2))
# define siDistintoValor(op1, op2)	 ((op1)!=(op2))
# define siMenorValor(op1, op2)		 ((op1)<(op2))
# define siMayorIgualValor(op1, op2)	 ((op1)>=(op2))
# define siMayorValor(op1, op2)		 ((op1)>(op2))
# define siMenorIgualValor(op1, op2)	 ((op1)<=(op2))
//operación de asignación
# define asignaValorA(var,expr)		 ((var)=(expr))
# include <math.h>

//funciones de lectura de datos dejando el buffer vacío
NATURAL leeNaturalLN(NADA) {
  NATURAL n;
  if(0 <= leeNatural(dirMem(n)))
    readLN();
  return n;
}

ENTERO leeEnteroLN(NADA) {
  ENTERO  n;
  if(0 <= leeEntero(dirMem(n)))
    readLN();
  return n;
}

RACIONAL leeNumeroLN(NADA) {
  RACIONAL n;
  if(0 <= leeNumero(dirMem(n)))
    readLN();
  return n;
}

CARACTER leeCaracterLN(NADA) {
  CARACTER c = getchar();
  if(c != -1 && c != '\n')
    readLN();
  return c;
}

# define pideNatural(frase)	 (escribeFrase(frase),leeNaturalLN())
# define pideEntero(frase)	 (escribeFrase(frase),leeEnteroLN())
# define pideNumero(frase)	 (escribeFrase(frase),leeNumeroLN())
# define pideCaracter(frase)	 (escribeFrase(frase),leeCaracterLN())

# include <termios.h>
CARACTER obtenTecla() {
  struct termios t;
  tcgetattr(0, &t);
  tcflag_t old_flag = t.c_lflag;
  t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(0, TCSANOW, &t);
  int     c = getchar();
  t.c_lflag = old_flag;
  tcsetattr(0, TCSANOW, &t);
  return c;
}

	//PROGRAMA: comentar si no se va a usar argumentos
//# define ENV(i)       (envv[i])
//# define arg(i)       ((i)<argc?argv[i]:"")
//# define nArgs        (argc)
# define declaraArgs		// ENTERO argc,FRASE argv[]     //,FRASE*envv
# define aboutOf() (printf("\n\t\t%s\n%32s%s\n%32c%s\n\t%s\n%40c",	\
		    PROGRAMA,"por ",AUTOR,' ',VERSION,DESCRIPCION,' '),pausa())
# define msgFinPrg()	(printf("\t"),activaFondo(WHITE),activaTinta(BLUE),			\
			 printf("Fin del programa %s. Pulsa <ENTER>", PROGRAMA),\
			 desactivaTintaFondo(),readLN())
# define PRG()	  PROCEDIMIENTO _prg_(NADA);				\
		  int main(declaraArgs){aboutOf();_prg_();msgFinPrg();return 0;}	\
		  PROCEDIMIENTO _prg_()
#endif
