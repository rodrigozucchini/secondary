#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/comun.h"
#include "../includes/listarClientes.h"

void listarClientes() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente cliente;

    printf("Clientes:\n\n");
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        printf("ID Cliente: %d, Nombre: %s, DNI: %s, Telefono: %s\n", cliente.id, cliente.nombres, cliente.dni, cliente.telefono);
    }
    printf("\n");
    fclose(clientesFile);
}

void listarClientesAZ() {

}

void listarClientesZA() {

}

