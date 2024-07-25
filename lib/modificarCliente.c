#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/comun.h"
#include "../includes/abm.h"

void modificarCliente() {
    char dni[50];
    printf("Ingrese el DNI del cliente a modificar: ");
    scanf("%49s", dni);
    convertirAMayusculas(dni);

    FILE *clientesFile = fopen("clientes.bin", "rb+");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        if (strcmp(cliente.dni, dni) == 0) {
            encontrado = 1;
            printf("Cliente encontrado. Ingrese los nuevos datos (deje en blanco para mantener el dato actual):\n");

            printf("Nombre actual: %s\n", cliente.nombres);
            printf("Ingrese el nuevo nombre: ");
            limpiarBuffer();
            fgets(cliente.nombres, sizeof(cliente.nombres), stdin);
            cliente.nombres[strcspn(cliente.nombres, "\n")] = '\0';

            printf("Telefono actual: %s\n", cliente.telefono);
            printf("Ingrese el nuevo telefono: ");
            fgets(cliente.telefono, sizeof(cliente.telefono), stdin);
            cliente.telefono[strcspn(cliente.telefono, "\n")] = '\0';

            if (cliente.nombres[0] == '\0') {
                strcpy(cliente.nombres, cliente.nombres);
            } else {
                convertirAMayusculas(cliente.nombres);
            }

            if (cliente.telefono[0] == '\0') {
                strcpy(cliente.telefono, cliente.telefono);
            } else {
                convertirAMayusculas(cliente.telefono);
            }

            fseek(clientesFile, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, clientesFile);
            printf("Datos del cliente actualizados correctamente.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente con DNI %s no encontrado.\n", dni);
    }

    fclose(clientesFile);
}