#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOMBRE_MAX 50
#define NOMBRE_ARCHIVO "inventarioproductos.dat"
//Estructura Producto del inventario
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
//Funciones de la interfaz
void mostrarMenu();
void procesarOpcion(Nodo** cabeza, int opcion);
//Funciones del inventario
void agregarProducto(Nodo** cabeza);
void eliminarProducto(Nodo** cabeza);
void modificarProducto(Nodo* cabeza);
void mostrarInventario(Nodo* cabeza);
//Funciones para ordenar y buscar productos
void buscarProductoPorCodigo(Nodo* cabeza);
void buscarProductoPorNombre(Nodo* cabeza);
void mostrarProductosOrdenadosPorPrecio(Nodo* cabeza);
//Funciones para manipular archivos
void guardarInventarioEnArchivo(Nodo* cabeza);
void cargarInventarioDesdeArchivo(Nodo** cabeza);
//Funciones auxiliares
void liberarMemoria(Nodo** cabeza);
