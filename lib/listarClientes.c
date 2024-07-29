#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../includes/comun.h"
#include "../includes/listarClientes.h"

void listarClientes() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente *clientes = NULL;
    size_t capacidad = 0;
    size_t cantidad = 0;

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        // Redimensionar el buffer si es necesario
        if (cantidad >= capacidad) {
            capacidad += 10;
            clientes = realloc(clientes, capacidad * sizeof(Cliente));
            if (clientes == NULL) {
                printf("Error de memoria.\n");
                fclose(clientesFile);
                return;
            }
        }
        clientes[cantidad++] = cliente;
    }

    fclose(clientesFile);

    // Listar los clientes
    printf("Listado de clientes:\n\n");
    for (size_t i = 0; i < cantidad; ++i) {
        printf("ID Cliente: %d, Nombre: %s, DNI: %s, Telefono: %s\n",
               clientes[i].id, clientes[i].nombres, clientes[i].dni, clientes[i].telefono);
    }

    free(clientes);
}

void intercambiarClientes(Cliente *a, Cliente *b) {
    Cliente temp = *a;
    *a = *b;
    *b = temp;
}

// Función de comparación para ordenar clientes por nombre (de A a Z)
// Función de comparación para ordenar clientes de A a Z por nombre
int compararClientesAZ(const void *a, const void *b) {
    // Convertir los punteros void a punteros a Cliente
    const Cliente *clienteA = (const Cliente *)a;
    const Cliente *clienteB = (const Cliente *)b;
    
    // Comparar los nombres de los clientes usando strcmp
    return strcmp(clienteA->nombres, clienteB->nombres);
}

// Función de comparación para ordenar clientes de Z a A por nombre
int compararClientesZA(const void *a, const void *b) {
    // Convertir los punteros void a punteros a Cliente
    const Cliente *clienteA = (const Cliente *)a;
    const Cliente *clienteB = (const Cliente *)b;
    
    // Comparar los nombres de los clientes usando strcmp en orden inverso
    return strcmp(clienteB->nombres, clienteA->nombres);
}

// Función para listar clientes en orden alfabético (A-Z)
void listarClientesAZ() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente *clientes = NULL;
    size_t capacidad = 0;
    size_t cantidad = 0;

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        // Redimensionar el buffer si es necesario
        if (cantidad >= capacidad) {
            capacidad += 10;
            clientes = realloc(clientes, capacidad * sizeof(Cliente));
            if (clientes == NULL) {
                printf("Error de memoria.\n");
                fclose(clientesFile);
                return;
            }
        }
        clientes[cantidad++] = cliente;
    }

    fclose(clientesFile);

    // Ordenar los clientes de A a Z por nombre
    qsort(clientes, cantidad, sizeof(Cliente), compararClientesAZ);

    // Listar los clientes
    printf("Listado de clientes (A-Z):\n\n");
    for (size_t i = 0; i < cantidad; ++i) {
        printf("ID Cliente: %d, Nombre: %s, DNI: %s, Telefono: %s\n",
               clientes[i].id, clientes[i].nombres, clientes[i].dni, clientes[i].telefono);
    }

    free(clientes);
}

// Función para listar clientes en orden alfabético (Z-A)
void listarClientesZA() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente *clientes = NULL;
    size_t capacidad = 0;
    size_t cantidad = 0;

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        // Redimensionar el buffer si es necesario
        if (cantidad >= capacidad) {
            capacidad += 10;
            clientes = realloc(clientes, capacidad * sizeof(Cliente));
            if (clientes == NULL) {
                printf("Error de memoria.\n");
                fclose(clientesFile);
                return;
            }
        }
        clientes[cantidad++] = cliente;
    }

    fclose(clientesFile);

    // Ordenar los clientes de Z a A por nombre
    qsort(clientes, cantidad, sizeof(Cliente), compararClientesZA);

    // Listar los clientes
    printf("Listado de clientes (Z-A):\n\n");
    for (size_t i = 0; i < cantidad; ++i) {
        printf("ID Cliente: %d, Nombre: %s, DNI: %s, Telefono: %s\n",
               clientes[i].id, clientes[i].nombres, clientes[i].dni, clientes[i].telefono);
    }

    free(clientes);
}