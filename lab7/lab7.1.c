#include <stdio.h>

#define MENU "Menú\n"

void ejecutaMenu_v1() {
  char op;
  int flagn = 0, flags = 0;
  int cont0 = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, contn = 0,
      conts = 0, contd = 0, contm = 0, contsw = 0;
  do {
    printf(MENU);
    contm++;
    op = getchar();
    switch (op) {
      case '1':
        cont1++;
        break;

      case '2':
        cont1++;
        cont2++;
        break;

      case '3':
        cont1++;
        cont2++;
        cont3++;
        break;

      case '4':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        break;

      case ' ':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        conts++;
        flags = 1;

      case '\n':
        if (!flags) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
          conts++;
        }

        contn++;
        flagn = 1;

      case '0':
        if (!flags && !flagn) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
        }

        if (!flags) {
          conts++;
        }

        if (!flagn) {
          contn++;
        }

        cont0++;
        break;

      default:
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        cont0++;
        conts++;
        contn++;
        contd++;
    }

    contsw++;
    flags = 0;
    flagn = 0;
  } while (op != '0');

  printf(
      "Contadores [ejecutaMenu_v1]:\n"
      "Menu: %d\n"
      "Case '1': %d\n"
      "Case '2': %d\n"
      "Case '3': %d\n"
      "Case '4': %d\n"
      "Case ' ': %d\n"
      "Case '\\n': %d\n"
      "Case '0': %d\n"
      "Default: %d\n"
      "Suma de contadores: %d\n",
      contm, cont1, cont2, cont3, cont4, conts, contn, cont0, contd,
      cont1 + cont2 + cont3 + cont4 + conts + contn + cont0 + contd);
}

void ejecutaMenu_v2() {
  char op = '1';
  int flagn = 0, flags = 0;
  int cont0 = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, contn = 0,
      conts = 0, contd = 0, contm = 0, contsw = 0;
  while (op != '0') {
    printf(MENU);
    contm++;
    op = getchar();
    switch (op) {
      case '1':
        cont1++;
        break;

      case '2':
        cont1++;
        cont2++;
        break;

      case '3':
        cont1++;
        cont2++;
        cont3++;
        break;

      case '4':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        break;

      case ' ':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        conts++;
        flags = 1;

      case '\n':
        if (!flags) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
          conts++;
        }

        contn++;
        flagn = 1;

      case '0':
        if (!flags && !flagn) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
        }

        if (!flags) {
          conts++;
        }

        if (!flagn) {
          contn++;
        }

        cont0++;
        break;

      default:
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        cont0++;
        conts++;
        contn++;
        contd++;
    }

    contsw++;
    flags = 0;
    flagn = 0;
  }

  printf(
      "Contadores [ejecutaMenu_v2]:\n"
      "Menu: %d\n"
      "Case '1': %d\n"
      "Case '2': %d\n"
      "Case '3': %d\n"
      "Case '4': %d\n"
      "Case ' ': %d\n"
      "Case '\\n': %d\n"
      "Case '0': %d\n"
      "Default: %d\n"
      "Suma de contadores: %d\n",
      contm, cont1, cont2, cont3, cont4, conts, contn, cont0, contd,
      cont1 + cont2 + cont3 + cont4 + conts + contn + cont0 + contd);
}

void ejecutaMenu_v3() {
  char op;
  int flagn = 0, flags = 0;
  int cont0 = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, contn = 0,
      conts = 0, contd = 0, contm = 0, contsw = 0;
  printf(MENU);
  contm++;
  op = getchar();
  while (op != '0') {
    switch (op) {
      case '1':
        cont1++;
        break;

      case '2':
        cont1++;
        cont2++;
        break;

      case '3':
        cont1++;
        cont2++;
        cont3++;
        break;

      case '4':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        break;

      case ' ':
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        conts++;
        flags = 1;

      case '\n':
        if (!flags) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
          conts++;
        }

        contn++;
        flagn = 1;

      case '0':
        if (!flags && !flagn) {
          cont1++;
          cont2++;
          cont3++;
          cont4++;
        }

        if (!flags) {
          conts++;
        }

        if (!flagn) {
          contn++;
        }

        cont0++;
        break;

      default:
        cont1++;
        cont2++;
        cont3++;
        cont4++;
        cont0++;
        conts++;
        contn++;
        contd++;
    }

    contsw++;
    flags = 0;
    flagn = 0;
    printf(MENU);
    contm++;
    op = getchar();
  }

  printf(
      "Contadores [ejecutaMenu_v3]:\n"
      "Menu: %d\n"
      "Case '1': %d\n"
      "Case '2': %d\n"
      "Case '3': %d\n"
      "Case '4': %d\n"
      "Case ' ': %d\n"
      "Case '\\n': %d\n"
      "Case '0': %d\n"
      "Default: %d\n"
      "Suma de contadores: %d\n",
      contm, cont1, cont2, cont3, cont4, conts, contn, cont0, contd,
      cont1 + cont2 + cont3 + cont4 + conts + contn + cont0 + contd);
}

int main() {
  fflush(stdin);
  printf("Función: ejecutaMenu_v1()\n");
  ejecutaMenu_v1();

  fflush(stdin);
  printf("Función: ejecutaMenu_v2()\n");
  ejecutaMenu_v2();

  fflush(stdin);
  printf("Función: ejecutaMenu_v3()\n");
  ejecutaMenu_v3();

  return 0;
}
