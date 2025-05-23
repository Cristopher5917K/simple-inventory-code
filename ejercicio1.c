#include <stdio.h>
#include <string.h>

#define MAX_PRODUCT 5

void mostrarMenu() {
    printf("\n----- MENU -----\n");
    printf("1. Ingresar productos\n");
    printf("2. Listar productos\n");
    printf("3. Buscar producto por nombre\n");
    printf("4. Editar producto\n");
    printf("5. Eliminar producto\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}

void limpiarBuffer() {
    while (getchar() != '\n');
}

float ingresarTiempoMaximo() {
    float valor;
    do {
        printf("\nIngrese el tiempo maximo: ");
        scanf("%f", &valor);
        limpiarBuffer();
        if (valor <= 0)
            printf("\nValor invalido, intentelo de nuevo");
    } while (valor <= 0);
    return valor;
}

float ingresarRecursosDisponibles() {
    float valor;
    do {
        printf("\nIngrese los recursos disponibles: ");
        scanf("%f", &valor);
        limpiarBuffer();
        if (valor <= 0)
            printf("\nValor invalido, intentelo de nuevo");
    } while (valor <= 0);
    return valor;
}

float leerTiempo(const char *mensaje) {
    float tiempo;
    do {
        printf("%s", mensaje);
        scanf("%f", &tiempo);
        limpiarBuffer();
        if (tiempo <= 0)
            printf("\nValor invalido, intentelo de nuevo\n");
    } while (tiempo <= 0);
    return tiempo;
}

int leerEntero(const char *mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        limpiarBuffer();
        if (valor <= 0)
            printf("\nValor invalido, intentelo de nuevo");
    } while (valor <= 0);
    return valor;
}

int ingresarProductos(char nomProduc[][50], float tiempos[], int recursos[], float tiempoMax, float recursosMax) {
    float tiempoAcumulado = 0;
    int recursosAcumulados = 0;
    int productos = 0;

    for (int i = 0; i < MAX_PRODUCT; i++) {
        if (tiempoAcumulado >= tiempoMax || recursosAcumulados >= recursosMax) {
            printf("\nSe alcanzó el limite de tiempo o recursos.\n");
            break;
        }

        printf("\nProducto %d\n", i + 1);
        printf("Nombre: ");
        scanf("%s", nomProduc[i]);

        float tiempo;
        do {
            tiempo = leerTiempo("Tiempo de fabricacion: ");
            if (tiempoAcumulado + tiempo > tiempoMax) {
                printf("Excede el tiempo maximo. Restante: %.2f\n", tiempoMax - tiempoAcumulado);
            }
        } while (tiempoAcumulado + tiempo > tiempoMax);

        int recurso;
        do {
            recurso = leerEntero("Cantidad de recursos: ");
            if (recursosAcumulados + recurso > recursosMax) {
                printf("Excede recursos maximos. Restante: %.0f\n", recursosMax - recursosAcumulados);
            }
        } while (recursosAcumulados + recurso > recursosMax);

        tiempoAcumulado += tiempo;
        recursosAcumulados += recurso;
        tiempos[i] = tiempo;
        recursos[i] = recurso;
        productos++;
    }

    return productos;
}

void listarProductos(char nomProduc[][50], int total) {
    if (total == 0) {
        printf("No hay productos para mostrar.\n");
        return;
    }

    printf("\nProductos ingresados:\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s\n", i + 1, nomProduc[i]);
    }
}

void buscarProducto(char nomProduc[][50], float tiempos[], int recursos[], int total) {
    if (total == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    char nombreBuscar[50];
    printf("Ingrese el nombre del producto a buscar: ");
    scanf("%s", nombreBuscar);

    for (int i = 0; i < total; i++) {
        if (strcmp(nombreBuscar, nomProduc[i]) == 0) {
            printf("Producto: %s\n", nomProduc[i]);
            printf(" - Tiempo: %.2f\n", tiempos[i]);
            printf(" - Recursos: %d\n", recursos[i]);
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

void editarProducto(char nomProduc[][50], float tiempos[], int recursos[], int total, float tiempoMax, float recursosMax) {
    if (total == 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    listarProductos(nomProduc, total);

    int indice;
    printf("Ingrese el numero del producto a editar (1-%d): ", total);
    scanf("%d", &indice);
    limpiarBuffer();
    indice--;

    if (indice < 0 || indice >= total) {
        printf("Indice invalido.\n");
        return;
    }

    printf("Nuevo nombre: ");
    scanf("%s", nomProduc[indice]);

    tiempos[indice] = leerTiempo("Nuevo tiempo de fabricacion: ");
    recursos[indice] = leerEntero("Nueva cantidad de recursos: ");

    printf("Producto actualizado con exito.\n");
}

int eliminarProducto(char nomProduc[][50], float tiempos[], int recursos[], int total) {
    if (total == 0) {
        printf("No hay productos para eliminar.\n");
        return total;
    }

    listarProductos(nomProduc, total);

    int indice;
    printf("Ingrese el numero del producto a eliminar (1-%d): ", total);
    scanf("%d", &indice);
    limpiarBuffer();
    indice--;

    if (indice < 0 || indice >= total) {
        printf("Indice invalido.\n");
        return total;
    }

    for (int i = indice; i < total - 1; i++) {
        strcpy(nomProduc[i], nomProduc[i + 1]);
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    printf("Producto eliminado con exito.\n");
    return total - 1;
}

int main() {
    char nomProduc[MAX_PRODUCT][50];
    float tiempos[MAX_PRODUCT] = {0};
    int cantidadRecursos[MAX_PRODUCT] = {0};
    float tiempoMax = 0, recursosDisponibles = 0;
    int productosIngresados = 0;

    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1:
                tiempoMax = ingresarTiempoMaximo();
                recursosDisponibles = ingresarRecursosDisponibles();
                productosIngresados = ingresarProductos(nomProduc, tiempos, cantidadRecursos, tiempoMax, recursosDisponibles);
                break;
            case 2:
                listarProductos(nomProduc, productosIngresados);
                break;
            case 3:
                buscarProducto(nomProduc, tiempos, cantidadRecursos, productosIngresados);
                break;
            case 4:
                editarProducto(nomProduc, tiempos, cantidadRecursos, productosIngresados, tiempoMax, recursosDisponibles);
                break;
            case 5:
                productosIngresados = eliminarProducto(nomProduc, tiempos, cantidadRecursos, productosIngresados);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 6);

    return 0;
}
