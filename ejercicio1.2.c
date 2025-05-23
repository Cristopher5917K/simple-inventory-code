#include <stdio.h>
#include <string.h>

#define MAX_PRODUCT 5

void ingresarLimites(float *tiempoMax, float *recursosDisponibles) {
    printf("Ingrese el tiempo maximo para cumplir la demanda: ");
    while (scanf("%f", tiempoMax) != 1 || *tiempoMax <= 0) {
        while (getchar() != '\n');
        printf("Valor invalido intente de nuevo: ");
        printf("Ingrese el tiempo maximo para cumplir la demanda: ");
    }

    printf("Ingrese los recursos disponibles: ");
    while (scanf("%f", recursosDisponibles) != 1 || *recursosDisponibles <= 0) {
        while (getchar() != '\n');
        printf("Valor invalido intente de nuevo ");
        printf("Ingrese los recursos disponibles: ");
    }
}

int ingresarProductos(char nombres[][50], float tiempos[], int recursos[], float tiempoMax, float recursosMax) {
    float tiempoAcumulado = 0;
    int recursosAcumulados = 0;
    int ingresados = 0;

    for (int i = 0; i < MAX_PRODUCT; i++) {
        if (tiempoAcumulado >= tiempoMax || recursosAcumulados >= recursosMax) {
            printf("\nSe ha alcanzado el limite de tiempo o recursos disponibles.\n");
            break;
        }

        printf("\nIngrese el nombre del producto %d: ", i + 1);
        scanf("%s", nombres[i]);

        float tiempo;
        int recurso;

        do {
            printf("Ingrese el tiempo que se demora en hacer el producto: ");
            while (scanf("%f", &tiempo) != 1 || tiempo < 0) {
                while (getchar() != '\n');
                printf("Valor invalido intente de nuevo ");
                printf("Ingrese el tiempo que se demora en hacer el producto: ");
            }

            if (tiempoAcumulado + tiempo > tiempoMax) {
                printf("Tiempo excede el máximo. Tiempo restante: %.2f\n", tiempoMax - tiempoAcumulado);
            }
        } while (tiempoAcumulado + tiempo > tiempoMax);

        do {
            printf("Ingrese la cantidad de recursos que ocupa el producto: ");
            while (scanf("%d", &recurso) != 1 || recurso < 0) {
                while (getchar() != '\n');
                printf("Valor invalido intente de nuevo ");
                printf("Ingrese la cantidad de recursos que ocupa el producto: ");
            }

            if (recursosAcumulados + recurso > recursosMax) {
                printf("Recursos exceden el límite. Recursos restantes: %d\n", (int)(recursosMax - recursosAcumulados));
            }
        } while (recursosAcumulados + recurso > recursosMax);

        tiempoAcumulado += tiempo;
        recursosAcumulados += recurso;

        tiempos[i] = tiempo;
        recursos[i] = recurso;
        ingresados++;
    }

    return ingresados;
}

void mostrarProductos(int cantidad, char nombres[][50]) {
    printf("\n-------Productos disponibles-------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("- %s\n", nombres[i]);
    }
}

void buscarProducto(int cantidad, char nombres[][50], float tiempos[], int recursos[]) {
    char buscar[50];
    int encontrado = 0;

    printf("\nIngrese el nombre de un producto para buscar sus datos: ");
    scanf("%s", buscar);

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
            printf("Producto encontrado: %s\n", nombres[i]);
            printf("Tiempo: %.2f\n", tiempos[i]);
            printf("Recursos: %d\n", recursos[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

// Función principal
int main() {
    char nombres[MAX_PRODUCT][50];
    float tiempos[MAX_PRODUCT] = {0};
    int recursos[MAX_PRODUCT] = {0};
    float tiempoMax, recursosMax;

    ingresarLimites(&tiempoMax, &recursosMax);
    int cantidad = ingresarProductos(nombres, tiempos, recursos, tiempoMax, recursosMax);

    if (cantidad > 0) {
        mostrarProductos(cantidad, nombres);
        buscarProducto(cantidad, nombres, tiempos, recursos);
    } else {
        printf("\nNo se ingresaron productos válidos.\n");
    }

    return 0;
}
