#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOMBRE_MAX 50
#define NOMBRE_ARCHIVO "inventarioproductos.dat"

typedef struct {
    int codigo;
    char nombre[NOMBRE_MAX];
    float precio;
    int stock;
} Producto;
typedef struct Nodo {
    Producto producto;
    struct Nodo* siguiente;
} Nodo;

void mostrarMenu();
void procesarOpcion(Nodo** cabeza, int opcion);

void agregarProducto(Nodo** cabeza);
void eliminarProducto(Nodo** cabeza);
void modificarProducto(Nodo* cabeza);
void mostrarInventario(Nodo* cabeza);


void liberarMemoria(Nodo** cabeza);

int main() {
    Nodo* listaDeProductos = NULL;
    int opcion = 0;
    return 0;



}

void mostrarMenu() {
    printf("\nINVENTARIO DE PRODUCTOS DE UN COMERCIO\n");
    printf("1. Agregar nuevo producto\n");
    printf("2. Modificar producto por codigo\n");
    printf("3. Eliminar producto por codigo\n");
    printf("4. Buscar producto por codigo\n");
    printf("5. Buscar producto por nombre\n");
    printf("6. Mostrar todos los productos (ordenados por precio)\n");
    printf("0. Guardar y Salir\n");
}
void agregarProducto(Nodo** cabeza) {
    int codigo;
    printf("Agregar Nuevo Producto\n");
    printf("Ingrese el codigo del producto: ");
    scanf("%d", &codigo);
    
    if (verificarCodigoExistente(*cabeza, codigo)) {
        printf("ERROR: Ya existe un producto con el codigo %d.\n", codigo);
        return;
    }

    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevoNodo) {
        printf("Error de memoria: no se pudo agregar el producto.\n");
        return;
    }
    
    nuevoNodo->producto.codigo = codigo;
    printf("Ingrese el nombre del producto: ");
    scanf(" %s", nuevoNodo->producto.nombre); 
    printf("Ingrese el precio del producto: ");
    scanf("%f", &nuevoNodo->producto.precio);
    printf("Ingrese el stock: ");
    scanf("%d", &nuevoNodo->producto.stock);

    nuevoNodo->siguiente = *cabeza;
    *cabeza = nuevoNodo;

    printf("Producto agregado.\n");
}
int verificarCodigoExistente(Nodo* cabeza, int codigo) {
    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->producto.codigo == codigo) {
            return 1; 
        }
        actual = actual->siguiente;
    }
    return 0;
}
void modificarProducto(Nodo* cabeza) {
    int codigo;
    printf("Modificar Producto\n");
    printf("Ingrese el codigo del producto a modificar: ");
    scanf("%d", &codigo);

    Nodo* actual = cabeza;
    while (actual != NULL && actual->producto.codigo != codigo) {
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("No se encontro ningun producto con el codigo %d.\n", codigo);
    } else {
        printf("Producto encontrado: %s (Precio: %.2f, Stock: %d)\n", actual->producto.nombre, actual->producto.precio, actual->producto.stock);
        printf("Ingrese el nuevo nombre: ");
        scanf(" %s", actual->producto.nombre);
        printf("Ingrese el nuevo precio: ");
        scanf("%f", &actual->producto.precio);
        printf("Ingrese el nuevo stock: ");
        scanf("%d", &actual->producto.stock);
        printf("Producto modificado.\n");
    }
}
void eliminarProducto(Nodo** cabeza) {
    int codigo;
    printf("Eliminar Producto\n");
    printf("Ingrese el codigo del producto a eliminar: ");
    scanf("%d", &codigo);

    Nodo* actual = *cabeza;
    Nodo* anterior = NULL;

    while (actual != NULL && actual->producto.codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("No se encontro ningun producto con el codigo %d.\n", codigo);
        return;
    }
    
    if (anterior == NULL) {
        *cabeza = actual->siguiente;
    } else { 
        anterior->siguiente = actual->siguiente;
    }
    free(actual); 
    printf("Producto con el codigo: %d eliminado.\n", codigo);
}
void liberarMemoria(Nodo** cabeza) {
    Nodo* actual = *cabeza;
    Nodo* siguiente;
    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    *cabeza = NULL;
}
