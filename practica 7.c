#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

// Prototipos
struct Nodo* crearNodo(int dato);
void insertarFinal(struct Nodo** cabeza, int dato);
void insertarOrdenado(struct Nodo** cabeza, int dato);
void mostrarLista(struct Nodo* cabeza);
void liberarLista(struct Nodo** cabeza);

// Prototipos
int totalValores(struct Nodo* cabeza);
double calcularMedia(struct Nodo* cabeza);
double calcularMediana(struct Nodo* cabeza);
int calcularModa(struct Nodo* cabeza);
double calcularVarianza(struct Nodo* cabeza, double media);
double calcularDesviacionEstandar(double varianza);

int main() {
    struct Nodo* cabeza = NULL;  // Lista original
    struct Nodo* listaOrdenada = NULL;  // Lista ordenada para c�lculos estad�sticos
    int valor;

    // Llenar la lista desde la consola
    printf("Ingrese valores para la lista (0 para terminar):\n");
    while (1) {
        printf("Valor: ");
        scanf("%d", &valor);

        if (valor == 0) break;

        insertarFinal(&cabeza, valor);
        insertarOrdenado(&listaOrdenada, valor);
    }

    printf("Lista ingresada:\n");
    mostrarLista(cabeza);

    int total = totalValores(listaOrdenada);
    double media = calcularMedia(listaOrdenada);
    double mediana = calcularMediana(listaOrdenada);
    int moda = calcularModa(listaOrdenada);
    double varianza = calcularVarianza(listaOrdenada, media);
    double desviacionEstandar = calcularDesviacionEstandar(varianza);

    printf("\nMedidas estad�sticas:\n");
    printf("Total de valores: %d\n", total);
    printf("Media: %.2f\n", media);
    printf("Mediana: %.2f\n", mediana);
    printf("Moda: %d\n", moda);
    printf("Varianza: %.2f\n", varianza);
    printf("Desviaci�n est�ndar: %.2f\n", desviacionEstandar);

    liberarLista(&cabeza);
    liberarLista(&listaOrdenada);

    return 0;
}


struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (!nuevoNodo) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}


void insertarFinal(struct Nodo** cabeza, int dato) {
    struct Nodo* nuevoNodo = crearNodo(dato);
    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        struct Nodo* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Funci�n para insertar en orden ascendente
void insertarOrdenado(struct Nodo** cabeza, int dato) {
    struct Nodo* nuevoNodo = crearNodo(dato);
    if (*cabeza == NULL || (*cabeza)->dato >= dato) {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
    } else {
        struct Nodo* actual = *cabeza;
        while (actual->siguiente != NULL && actual->siguiente->dato < dato) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

// impresion de la lista
void mostrarLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}


void liberarLista(struct Nodo** cabeza) {
    struct Nodo* actual = *cabeza;
    while (actual != NULL) {
        struct Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}


int totalValores(struct Nodo* cabeza) {
    int contador = 0;
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Media
double calcularMedia(struct Nodo* cabeza) {
    int suma = 0;
    int contador = 0;
    struct Nodo* actual = cabeza;

    while (actual != NULL) {
        suma += actual->dato;
        contador++;
        actual = actual->siguiente;
    }

    return contador > 0 ? (double)suma / contador : 0;
}

// Mediana
double calcularMediana(struct Nodo* cabeza) {
    int total = totalValores(cabeza);
    struct Nodo* actual = cabeza;

    for (int i = 0; i < (total - 1) / 2; i++) {
        actual = actual->siguiente;
    }

    if (total % 2 == 0) {
        return (actual->dato + actual->siguiente->dato) / 2.0;
    } else {
        return actual->dato;
    }
}

// Moda
int calcularModa(struct Nodo* cabeza) {
    int moda = 0, maxFrecuencia = 0;
    struct Nodo* actual = cabeza;

    while (actual != NULL) {
        int frecuencia = 1;
        struct Nodo* temp = actual->siguiente;

        while (temp != NULL) {
            if (temp->dato == actual->dato) {
                frecuencia++;
            }
            temp = temp->siguiente;
        }

        if (frecuencia > maxFrecuencia) {
            maxFrecuencia = frecuencia;
            moda = actual->dato;
        }
        actual = actual->siguiente;
    }

    return moda;
}

// Varianza
double calcularVarianza(struct Nodo* cabeza, double media) {
    double suma = 0;
    int contador = 0;
    struct Nodo* actual = cabeza;

    while (actual != NULL) {
        suma += pow(actual->dato - media, 2);
        contador++;
        actual = actual->siguiente;
    }

    return contador > 1 ? suma / contador : 0;
}

// Desviaci�n est�ndar
double calcularDesviacionEstandar(double varianza) {
    return sqrt(varianza);
}
