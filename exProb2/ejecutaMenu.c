#define MENU "Menu:...\nIntroduce una opción del 1 al 4 y 0 para salir\n"

void ejecutaMenu_v1() {
    char op;
    int switchCounter = 0; // Counter variable to track the number of times switch is executed
    do {
        printf("%s", MENU);
        op = getchar();
        switchCounter++; // Increment the counter each time switch is executed
        switch(op) {
            case '1':
                printf("Ejecuta el caso 1\n");
                break;
            case '2':
                printf("Ejecuta el caso 2\n");
                break;
            case '3':
                printf("Ejecuta el caso 3\n");
                break;
            case '4':
                printf("Ejecuta el caso 4\n");
                break;
            case '\n':
            case ' ':
            case '0':
                break;
            default:
                printf("Error: opción no válida\n");
                break;
        }
    } while (op != '0');
    printf("Caso: 0 Salir\n");
    printf("El switch se ha ejecutado %d veces.\n", switchCounter); // Print the number of times switch is executed
}

int main() {
    ejecutaMenu_v1();
    return 0;
}
