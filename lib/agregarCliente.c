#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/comun.h"
#include "../includes/abm.h"

int obtenerUltimoIDCliente() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        return 0;
    }

    fseek(clientesFile, -sizeof(Cliente), SEEK_END);
    Cliente ultimoCliente;
    fread(&ultimoCliente, sizeof(Cliente), 1, clientesFile);
    fclose(clientesFile);

    return ultimoCliente.id;
}

void agregarCliente() {
    Cliente nuevoCliente;
    nuevoCliente.id = obtenerUltimoIDCliente() + 1;
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", nuevoCliente.nombres);
    convertirAMayusculas(nuevoCliente.nombres);
    printf("Ingrese el DNI del cliente: ");
    scanf("%s", nuevoCliente.dni);
    convertirAMayusculas(nuevoCliente.dni);
    printf("Ingrese el telefono: ");
    scanf("%s", nuevoCliente.telefono);
    convertirAMayusculas(nuevoCliente.telefono);

    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile != NULL) {
        Cliente clienteExistente;
        while (fread(&clienteExistente, sizeof(Cliente), 1, clientesFile) == 1) {
            if (strcmp(clienteExistente.dni, nuevoCliente.dni) == 0) {
                printf("El cliente ya existe en el sistema.\n");
                fclose(clientesFile);
                return;
            }
        }
        fclose(clientesFile);
    }

    clientesFile = fopen("clientes.bin", "ab");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    fwrite(&nuevoCliente, sizeof(Cliente), 1, clientesFile);
    fclose(clientesFile);

    printf("Cliente y telefono agregados correctamente.\n");
}