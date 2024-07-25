#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <listarClientes.h>
#include <abm.h>

void convertirAMayusculas(char *cadena);
void agregarCliente();
void listarClientes();
void listarClientesAZ();
void listarClientesZA();
void buscarClientesPorCriterio();
void modificarCliente();
int eliminarDatos();
void menuPrincipal();

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int opcionPrincipal;

    do {
        printf("Hola, bienvenido a tu listador de contacto de clientes\n");
        printf(
            "\nOPCIONES DE MENU\n"
            "1. Ver todos los clientes y su telefono por orden de insercion\n"
            "2. Ver todos los clientes y su telefono ordenados A-Z por su nombre\n"
            "3. Ver todos los clientes y su telefono ordenados Z-A por su nombre\n"
            "4. Buscar clientes por DNI, nombre o telefono\n"
            "5. Agregar un cliente y su telefono\n"
            "6. Modificar un cliente y su telefono\n"
            "7. Eliminar un cliente o eliminar todo\n"
            "10. Salir del programa\n"
        );

        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcionPrincipal) != 1) {
            printf("Opcion no valida, por favor ingrese un numero.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (opcionPrincipal) {
            case 1:
                listarClientes();
                break;
            case 2:
                listarClientesAZ();
                break;
            case 3:
                listarClientesZA();
                break;
            case 4:
                buscarClientesPorCriterio();
                break;
            case 5:
                agregarCliente();
                break;
            case 6:
                modificarCliente();
                break;
            case 7:
                eliminarDatos();
                break;
            case 10:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida, por favor seleccione una opción del menu.\n");
                break;
        }
    } while (opcionPrincipal != 10);
}