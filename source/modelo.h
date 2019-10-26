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
 * Retorna una lista con los 5 productos mas vendidos de la lista pasada por productos
 * Entradas:
 *  listaProductos - lista de los productos
 * Salidas:
 *  Lista con los 5 productos mas vendidos
 */ 
TNodo<Producto> *darProductosMasVendidos(TNodo<Producto> **listaProductos);

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
TNodo<Producto>* buscarProducto(char* cadena);

/**
 * Ordena la lista de productos por uno de estos criterios: nombre, precio, restaurante ó promociones
 * Hay constantes que representan estos criterios definidas arriba.
 * Entradas:
 *  listaProductos - lista de los productos que será ordenada
 *  criterio - Criterio de ordenación (1, 2, 3, 4) constantes definidas arriba 
 */ 
void ordenarLista(TNodo<Producto> **listaProductos, int criterio);

/**
 * Muestra la lista de productos pasados por parametro en consola.
 * Por cada página se muestran 10 productos, de cada productos se muestra:
 * El código, nombre y el valor.
 * Se permite seleccionar un producto de la lista para añadirlo al carrito de compras.
 */ 
void mostrarLista(TNodo<Producto> **listaProductos);

/**
 * Muestra el carrito de compras pasado por parámetro en la consola.
 * Se permite al usuario borrar elementos del carrito, al hacerlo se actualiza.
 * Tambien se permite comprar el carrito, entonces para cada producto en el carrito se 
 * efectúa la venta respectiva.
 * Entradas:
 *  carrito - el carrito de compras que es una lista de productos
 */ 
void mostrarCarrito(TNodo<Producto> **carrito);

/**
 * Vende un producto con el codigo pasado por parametro.
 * Al venderlo la cantidad disponible debe disminuir y la cantidad vendida debe aumentar.
 * Si no hay suficientes productos para la venta, el producto no es vendido
 * Entradas:
 *  listaProductos - lista de los productos
 *  codigo - codigo del producto a vender
 * Salidas:
 *  true - Si se vende el producto exitosamente
 *  false - Si hay un error al vender el producto (el codigo no esta en la lista o el producto no tiene cantidad disponible)
 */ 
bool venderProducto(TNodo<Producto> **listaProductos, int codigo);


//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Funciones Auxiliares y Adicionales
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 * Imprime la lista pasada por parametro. Se imprime en el siguiente formato:
 * Por cada elemento de la lista: "Producto:" nombre "Codigo:" codigo
 */ 
void imprimirLista(TNodo<Producto> **listaProductos);

#endif