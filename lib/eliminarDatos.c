#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../includes/comun.h"
#include "../includes/abm.h"

int eliminarDatos() {
    int opcionEliminar;
   
    printf("\n");
    printf(
    "En este momento vas a poder realizar acciones de eliminacion\n"
    "\n"
    "OPCIONES DE MENU\n"
    "PRESIONANDO 1 ELIMINAR UN CLIENTE\n"
    "\n"
    "PRESIONANDO 8 ELIMINAS TODO\n"
    "PRESIONANDO 9 VAS AL MENU PRINCIPAL\n"
    "PRESIONANDO ESCAPE O ESC SALES DEL PROGRAMA\n"
    "\n"
    );
    scanf("%d", &opcionEliminar);
   
    switch(opcionEliminar) {
            case 1:
                eliminarUsuario();
                break;
            case 8:
                eliminarTodo();
                break;
            default:
                printf("Opcion no valida, por favor seleccione la opciones que muestra el menu\n");
                printf("\n");
                break;
        }


    return opcionEliminar;
}


void eliminarUsuario() {
    char dni[50];
    int encontrado = 0;

    printf("Ingrese el DNI del cliente a eliminar: ");
    scanf("%s", dni);
    convertirAMayusculas(dni);

    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    // Inicializar variables para manejo de memoria dinámica
    Cliente *clientes = NULL;
    size_t capacidad = 0;
    size_t cantidad = 0;
    size_t incremento = 10; // Incremento de la capacidad del buffer

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        // Redimensionar el buffer si es necesario
        if (cantidad >= capacidad) {
            capacidad += incremento;
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

    // Reabrir el archivo en modo de escritura para sobrescribir los datos
    FILE *clientesFileWrite = fopen("clientes.bin", "wb");
    if (clientesFileWrite == NULL) {
        printf("Error al abrir el archivo de clientes para escritura.\n");
        free(clientes);
        return;
    }

    // Escribir solo los clientes que no sean el que se va a eliminar
    for (size_t i = 0; i < cantidad; i++) {
        if (strcmp(clientes[i].dni, dni) != 0) {
            fwrite(&clientes[i], sizeof(Cliente), 1, clientesFileWrite);
        } else {
            encontrado = 1;
        }
    }
    fclose(clientesFileWrite);
    free(clientes);

    if (encontrado) {
        printf("Cliente eliminado correctamente.\n");
    } else {
        printf("No se encontró un cliente con el DNI proporcionado.\n");
    }
}

void eliminarTodo() {
    if (remove("clientes.bin") != 0) {
        printf("Error al eliminar el archivo de clientes.\n");
    } else {
        printf("Todos los archivos de la base de datos han sido eliminados.\n");
    }
}