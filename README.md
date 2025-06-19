# Inventario de Productos para Comercio

## Descripción del Proyecto
Este programa permite gestionar el inventario de productos de un comercio utilizando el lenguaje C, ofreciendo funcionalidades como agregar, modificar, eliminar y buscar productos. 
Además, permite mostrar los productos ordenados por precio y almacenar los datos en un archivo binario.

## Integrantes del Proyecto
- **Escobar Alabert Lucas**: Developer. 
- **Cantero Juan Manuel**: Developer.

## Funcionalidades
- Agregar nuevo producto al inventario pidiendo código, nombre, precio y stock.
- Modificar producto por código.
- Eliminar producto por código.
- Buscar productos por código o nombre.
- Mostrar inventario ordenado por precio.
- Guardar y cargar datos desde un archivo binario: Los productos se cargan y guardan en un fichero ("inventarioproductos.dat")

## Instrucciones para Compilar y Ejecutar

### En Windows
1. Abre una terminal en la carpeta del proyecto.
2. Compila el programa con: gcc Inventarioaentregar.c -o Inventarioaentregar.exe
3. Ejecuta el programa con: Inventarioaentregar.exe

### En Linux
1. Abre una terminal en la carpeta del proyecto.
2. Compila el programa con: gcc Inventarioaentregar.c -o Inventarioaentregar
3. Ejecuta el programa con: ./Inventarioaentregar
