#include <stdio.h>
#include <string.h>

// DEFINICION DE COLORES PARA USAR
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"

#define MAX_CLIENTES 1000

// 
// Estructura para representar un cliente
typedef struct {
    int id;
    char nombres[50];
    int dni;
    int telefono;
} Cliente;


int menuPrincipal();
void busquedaClientes();
void agregarCliente();
int obtenerUltimoIDCliente();
int eliminarDatos();
void eliminarTodo();
void eliminarUsuario();


int main()
{	
	menuPrincipal();
	return 0;
}

int menuPrincipal() {
	int opcionPrincipal; 
    
    do {
        printf(YELLOW"Hola bienvenido a tu listador de contacto de clientes");
        printf("\n");
        printf(
        "En este momento vas a poder realizar acciones en la aplicacion\n"
        "\n"
        "OPCIONES DE MENU\n"
        GREEN"PRESIONANDO 1 VAS A VER CLIENTE Y SU TELEFONO\n"
        GREEN"PRESIONANDO 2 VAS A AGREGAR UN CLIENTE Y SU TELEFONO\n"
        GREEN"PRESIONANDO 3 VAS A MODIFICAR UN CLIENTE Y SU TELEFONO\n"
        GREEN"PRESIONANDO 4 VAS A ELIMINAR TODO O UN CLIENTE Y SU TELEFONO\n"
        "\n"
        RED"PRESIONANDO ESCAPE O ESC SALES DEL PROGRAMA\n"
        YELLOW"\n"
        );
        
        scanf("%d", &opcionPrincipal);
        
         switch(opcionPrincipal) {
            case 1:
                printf(GREEN"Seleccionaste Mostrar Clientes\n");
                busquedaClientes();
                break;
            case 2:
                printf(GREEN"Seleccionaste Agregar Cliente\n");
                agregarCliente();
                break;
            case 3:
                printf(GREEN"Seleccionaste Modificar Cliente\n");
                break;
            case 4:
                printf(GREEN"Seleccionaste Eliminar Clientes O Eliminar Todo\n");
                eliminarDatos();
                break;
            case 27:
                printf(RED"Seleccionaste Salir\n");
                break;
            default:
                printf("Opcion no valida, por favor seleccione la opciones que muestra el menu\n");
                printf("\n");
                break;
        }
    } while (opcionPrincipal != 27);
    
    return opcionPrincipal;
}


int eliminarDatos() {
	int opcionEliminar;
	
	printf("\n");
	printf(
	YELLOW"En este momento vas a poder realizar acciones de eliminacion\n"
	"\n"
	YELLOW"OPCIONES DE MENU\n"
	GREEN"PRESIONANDO 1 ELIMINAR UN CLIENTE\n"
	"\n"
	RED"PRESIONANDO 8 ELIMINAS TODO\n"
	RED"PRESIONANDO 9 VAS AL MENU PRINCIPAL\n"
	RED"PRESIONANDO ESCAPE O ESC SALES DEL PROGRAMA\n"
	YELLOW"\n"
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

// BUSQUEDA

void busquedaClientes() {
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile == NULL) {
        printf("Error al abrir el archivo de clientes.\n");
        return;
    }

    Cliente cliente;

    printf("Clientes:\n");
    while (fread(&cliente, sizeof(Cliente), 1, clientesFile) == 1) {
        printf("ID Cliente: %d, Nombre: %s, DNI: %d, Telefono: %d\n", cliente.id, cliente.nombres, cliente.dni, cliente.telefono);
    }
    fclose(clientesFile);
}


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
    scanf(" %[^\n]", nuevoCliente.nombres);
    printf("Ingrese el DNI del cliente: ");
    scanf("%d", &nuevoCliente.dni);
    printf("Ingrese el telefono: ");
    scanf("%d", &nuevoCliente.telefono);

    // Verificar si el cliente ya existe
    FILE *clientesFile = fopen("clientes.bin", "rb");
    if (clientesFile != NULL) {
        Cliente clienteExistente;
        while (fread(&clienteExistente, sizeof(Cliente), 1, clientesFile) == 1) {
            if (strcmp(clienteExistente.nombres, nuevoCliente.nombres) == 0 && clienteExistente.dni == nuevoCliente.dni) {
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
     menuPrincipal();
}



void eliminarTodo() {
    if (remove("clientes.bin") != 0) {
        printf("Error al eliminar el archivo de clientes.\n");
    }

    printf("Todos los archivos de la base de datos han sido eliminados.\n");
}

void eliminarUsuario() {

}