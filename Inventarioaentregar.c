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
int verificarCodigoExistente(Nodo* cabeza, int codigo);
void eliminarProducto(Nodo** cabeza);
void modificarProducto(Nodo* cabeza);
void mostrarInventario(Nodo* cabeza);

void buscarProductoPorCodigo(Nodo* cabeza);
void buscarProductoPorNombre(Nodo* cabeza);
void mostrarProductosOrdenadosPorPrecio(Nodo* cabeza);

void guardarInventarioEnArchivo(Nodo* cabeza);
void cargarInventarioDesdeArchivo(Nodo** cabeza);

void liberarMemoria(Nodo** cabeza);

int main() {
    Nodo* listaDeProductos = NULL;
    int opcion = 0;
    
    cargarInventarioDesdeArchivo(&listaDeProductos);
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        if (opcion == 0)
        {
            break;
        }
        
    /*Falta procesar opcion */
        
    } while (opcion != 0);
    printf("Programa guardado.\n");
    guardarInventarioEnArchivo(listaDeProductos);
    liberarMemoria(&listaDeProductos);
    
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
void buscarProductoPorCodigo(Nodo* cabeza) {
    int codigo;
    printf("Buscar Producto por codigo\n");
    printf("Ingrese el codigo del producto a buscar: ");
    scanf("%d", &codigo);

    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (actual->producto.codigo == codigo) {
            printf("Producto encontrado:\n");
            printf("  Codigo: %d\n", actual->producto.codigo);
            printf("  Nombre: %s\n", actual->producto.nombre);
            printf("  Precio: %.2f\n", actual->producto.precio);
            printf("  Stock: %d\n", actual->producto.stock);
            return;
        }
        actual = actual->siguiente;
    }
    printf("No se encontro ningun producto con el codigo %d.\n", codigo);
}
void buscarProductoPorNombre(Nodo* cabeza) {
    char nombreBusqueda[NOMBRE_MAX];
    int encontrados = 0;
    printf("Buscar Producto por Nombre\n");
    printf("Ingrese el nombre (o parte del nombre) del producto a buscar: ");
    scanf(" %s", nombreBusqueda);

    Nodo* actual = cabeza;
    while (actual != NULL) {
        if (strstr(actual->producto.nombre, nombreBusqueda) != NULL) {
            printf("  - Codigo: %d, Nombre: %s, Precio: %.2f, Stock: %d\n",actual->producto.codigo, actual->producto.nombre,actual->producto.precio, actual->producto.stock);
            encontrados++;
        }
        actual = actual->siguiente;
    }

    if (encontrados == 0) {
        printf("No se encontraron productos que coincidan con la busqueda.\n");
    }
}
void mostrarProductosOrdenadosPorPrecio(Nodo* cabeza) {
    printf("Inventario Completo (Ordenado por Precio)\n");
    if (cabeza == NULL) {
        printf("El inventario está vacio.\n");
        return;
    }
    int n = 0;
    Nodo* temp = cabeza;
    while (temp != NULL) {
        n++;
        temp = temp->siguiente;
    }

    Producto* arrayProductos = (Producto*)malloc(n * sizeof(Producto));
    temp = cabeza;
    for (int i = 0; i < n; i++) {
        arrayProductos[i] = temp->producto;
        temp = temp->siguiente;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrayProductos[j].precio > arrayProductos[j + 1].precio) {
                Producto tempProducto = arrayProductos[j];
                arrayProductos[j] = arrayProductos[j + 1];
                arrayProductos[j + 1] = tempProducto;
            }
        }
    }

    printf("------------------------------------------------------------------\n");
    printf("%-10s %-25s %-15s %-10s\n", "CODIGO", "NOMBRE", "PRECIO", "STOCK");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-25s $%-14.2f %-10d\n",arrayProductos[i].codigo, arrayProductos[i].nombre,arrayProductos[i].precio, arrayProductos[i].stock);
    }
    printf("------------------------------------------------------------------\n");

    free(arrayProductos);
}
void guardarInventarioEnArchivo(Nodo* cabeza) {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura");
        return;
    }
    Nodo* actual = cabeza;
    while (actual != NULL) {
        fwrite(&(actual->producto), sizeof(Producto), 1, archivo);
        actual = actual->siguiente;
    }
    fclose(archivo);
}
void cargarInventarioDesdeArchivo(Nodo** cabeza) {
    FILE* archivo = fopen(NOMBRE_ARCHIVO, "rb");
    if (archivo == NULL) {
        printf("No se encontro el archivo '%s'. Se va abrir otro inventario vacio.\n", NOMBRE_ARCHIVO);
        return;
    }

    Producto prod;
    liberarMemoria(cabeza);

    while (fread(&prod, sizeof(Producto), 1, archivo) == 1) {
        Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
        
        nuevoNodo->producto = prod;
    
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
    }
    fclose(archivo);
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
