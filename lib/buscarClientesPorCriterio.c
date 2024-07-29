#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/comun.h"
#include "../includes/abm.h"

void buscarClientesPorCriterio() {
    char criterio[50];
    char valor[50];
    int found = 0;

    printf("Ingrese el criterio de busqueda (nombre, DNI o telefono): ");
    scanf("%s", criterio);
    convertirAMayusculas(criterio);
    printf("Ingrese el valor a buscar: ");
    scanf("%s", valor);
    convertirAMayusculas(valor);


    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }


    Cliente cliente;
    printf("Resultados de la busqueda:\n\n");
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        if ((strcmp(criterio, "NOMBRE") == 0 && strstr(cliente.nombres, valor) != NULL) ||
            (strcmp(criterio, "DNI") == 0 && strstr(cliente.dni, valor) != NULL) ||
            (strcmp(criterio, "TELEFONO") == 0 && strstr(cliente.telefono, valor) != NULL)) {
            printf("ID Cliente: %d, Nombre: %s, DNI: %s, Telefono: %s\n", cliente.id, cliente.nombres, cliente.dni, cliente.telefono);
            found = 1;
        }
    }
    fclose(clientesFile);


    if (!found) {
        printf("No se encontraron resultados para el criterio proporcionado.\n");
    }


    return;
}
