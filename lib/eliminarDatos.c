#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
    int found = 0;

    printf("Ingrese el DNI del cliente a eliminar: ");
    scanf("%49s", dni);
    convertirAMayusculas(dni);

    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente clientes[MAX_CLIENTES];
    int count = 0;

    while (fread(&clientes[count], sizeof(Cliente), 1, clientesFile) == 1) {
        count++;
    }
    fclose(clientesFile);

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        printf("Error al abrir el archivo temporal.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(clientes[i].dni, dni) != 0) {
            fwrite(&clientes[i], sizeof(Cliente), 1, tempFile);
        } else {
            found = 1;
        }
    }
    fclose(tempFile);

    remove("clientes.bin");
    rename("temp.bin", "clientes.bin");

    if (found) {
        printf("Cliente eliminado correctamente.\n");
    } else {
        printf("No se encontro un cliente con el DNI proporcionado.\n");
    }
}

void eliminarTodo() {
    if (remove("clientes.bin") != 0) {
        printf("Error al eliminar el archivo de clientes.\n");
    } else {
        printf("Todos los archivos de la base de datos han sido eliminados.\n");
    }
}