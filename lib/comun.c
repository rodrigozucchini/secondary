#include "comun.h"
#include <ctype.h>
#include <stdio.h>

void convertirAMayusculas(char *cadena) {
    while (*cadena) {
        *cadena = toupper(*cadena);
        cadena++;
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
