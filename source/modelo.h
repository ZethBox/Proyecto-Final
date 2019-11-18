#ifndef MODELO_H
#define MODELO_H
#include "lista.h"

//Constantes de ordenamiento
const int NOMBRE = 1;
const int PRECIO = 2;
const int RESTAURANTE = 3;
const int PROMOCIONES = 4;

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Estructuras
//--------------------------------------------------------------------------------------------------------------------------------------------------------

struct Producto {
    int codigo;
    char nombre[50];
    double costo;
    double precioVenta;
    char descripcion[500];
    bool enPromocion;
    int cantidadDisponible;
    int cantidadVendida;
    char restaurante[100];
};

struct Pagina {
    Producto productos[10];
    int size;
};

struct ProductoCarrito {
    Producto producto;
    int cantidad;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Funciones de Administrador
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * Verifica si un producto existe en la lista total de productos. Los productos son identificados
 * por un codigo que es diferente para cada producto.
 * Entradas:
 *  listaProductos - Lista de los productos
 *  buscado - Producto que se quiere encontrar en la lista
 * Salidas:
 *  true - Si el producto se encuentra en la lista
 *  false - Se el producto no se encuentra en la lista
 */ 
bool existe(TNodo<Producto> **listaProductos, Producto buscado);

/**
 * Agrega un producto a la lista de Productos pasada como parametro. Solo lo agrega si el producto
 * no existe en la lista, los productos son diferenciados por su codigo.
 * Entradas:
 *  listaProductos - Lista de los productos
 *  nuevo - Producto que se quiere agreagar a la lista
 * Salidas:
 *  true - Si el producto es agregado con exito
 *  false - Si el producto no es agregado a la lista
 */ 
bool agregarProducto(TNodo<Producto> **listaProductos, Producto nuevo);

/**
 * Elimina un producto de la lista
 * Entradas:
 *  listaProdutos - Lista de los productos
 *  codigo - codigo del producto a eliminar
 * Salidas:
 *  true - Si el producto es eliminado de la lista
 *  false - Si el producto no es eliminado de la lista
 */
bool eliminarProducto(TNodo<Producto> **listaProductos, int codigo);

/**
 * Busca en la lista de productos un producto cuyo codigo sea igual al pasado por parametro y devuelve el apuntador a dicho producto
 * Entradas:
 *  listaProductos - Lista de los productos
 *  codigo - codigo del producto a consultar
 * Salidas:
 *  apuntador al producto - si se encuentra el producto con dicho codigo
 *  NULL - si no se encuentra el codigo del producto
 */ 
Producto* consultarProducto(TNodo<Producto> **listaProductos, int codigo);

/**
 * Retorna una lista con los 5 productos mas vendidos de la lista pasada por parametro
 * Entradas:
 *  listaProductos - lista de los productos
 * Salidas:
 *  Lista con los 5 productos mas vendidos
 */ 
TNodo<Producto> *darProductosMasVendidos(TNodo<Producto> *listaProductos);

/**
 * Retorna una lista con los 5 productos menos vendidos de la lista pasada por parametro
 * Entradas:
 *  listaProductos - lista de los productos
 * Salidas:
 *  Lista con los 5 productos menos vendidos
 */ 
TNodo<Producto> *darProductosMenosVendidos(TNodo<Producto> *listaProductos);

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Funciones de Cliente
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * Busca en la lista de productos todos los productos cuyo nombre o descripción contengan
 * la cadena pasada como parámetro.
 * Entradas:
 *  cadena - cadena de caracteres que se quiere usar para filtrar los productos
 * Salidas:
 *  Lista - con productos que contengan la cadena en el nombre o descripcion
 *  NULL - si no hay productos que cumplan con este criterio
 */ 
TNodo<Producto> *buscarProductos(TNodo<Producto> **listaProductos, char *str);

/**
 * Ordena la lista de productos por uno de estos criterios: nombre, precio, restaurante ó promociones
 * Hay constantes que representan estos criterios definidas arriba.
 * Entradas:
 *  listaProductos - lista de los productos que será ordenada
 *  criterio - Criterio de ordenación (1, 2, 3, 4) constantes definidas arriba 
 */ 
void ordenarLista(TNodo<Producto> **listaProductos, int criterio);

/**
 * Muestra el carrito de compras pasado por parámetro en la consola.
 * Se permite al usuario borrar elementos del carrito, al hacerlo se actualiza.
 * Tambien se permite comprar el carrito, entonces para cada producto en el carrito se 
 * efectúa la venta respectiva.
 * Entradas:
 *  carrito - el carrito de compras que es una lista de productos
 */ 
void mostrarCarrito(TNodo<Producto> **carrito);

//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Funciones Auxiliares y Adicionales
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * Imprime la lista pasada por parametro. Se imprime en el siguiente formato:
 * Por cada elemento de la lista: "Producto:" nombre "Codigo:" codigo
 */ 
void imprimirLista(TNodo<Producto> **listaProductos);

/**
 * Muestra el catalogo de todos los productos al cliente
 */ 
void mostrarCatalogo(TNodo<Producto> **lista, TNodo<ProductoCarrito> **carrito);

/**
 * Muestra la pagina generafa de un arreglo de productos
 */ 
int mostrarPagina(Producto *productos, int size, int numero, TNodo<ProductoCarrito> **carrito);

/**
 * Muestra el carrito de compras y da la opcion de comprar el carrito o eliminar elementos del carrito
 */ 
void mostrarCarrito(TNodo<ProductoCarrito> **carrito);

/**
 * Intenta comprar todo el carrito de mercado, muestra al usuario si hay problemas de disponibilidad al intentar comprar los productos
 */ 
void comprarCarrito(TNodo<ProductoCarrito> **carrito, TNodo<Producto> **listaProductos);

/**
 * Intenta eliminar un producto del carrito. Si el producto no existe en el carrito retorna false, si existe lo elimina o disminuye la cantidad y retorna true
 */ 
bool eliminarCarrito(TNodo<ProductoCarrito> **carrito, int codigo);

#endif