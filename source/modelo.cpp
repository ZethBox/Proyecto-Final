#include "modelo.h"
#include "lista.h"
#include "string.h"
#include <iostream>

void crearProducto(Producto &producto) {
    producto.codigo = 0;
    producto.cantidadDisponible = 0;
    producto.cantidadVendida = 0;
    producto.costo = 0.0;
    strcpy(producto.descripcion, "");
    strcpy(producto.nombre, "");
    producto.precioVenta = 0.0;
    producto.enPromocion = false;
    strcpy(producto.restaurante, "");
}

void crearProducto(Producto &producto, int cod, double costo, char* nombre, char* desc, double precio, bool promo, char* res) {
    crearProducto(producto);
    producto.codigo = cod;
    producto.costo = costo;
    strcpy(producto.nombre, nombre);
    strcpy(producto.descripcion, desc);
    producto.precioVenta = precio;
    producto.enPromocion = promo;
    strcpy(producto.restaurante, res);
}

bool existe(TNodo<Producto> **listaProductos, Producto buscado)
{
    TNodo<Producto> *producto = *listaProductos;
    while (producto != NULL)
    {
        if ((producto->dato).codigo == buscado.codigo)
        {
            return true;
        }
        producto = producto->sig;
    }
    return false;
}

bool existe(TNodo<Producto> **listaProductos, int codigoBuscado)
{
    TNodo<Producto> *producto = *listaProductos;
    while (producto != NULL)
    {
        if ((producto->dato).codigo == codigoBuscado)
        {
            return true;
        }
        producto = producto->sig;
    }
    return false;
}

bool agregarProducto(TNodo<Producto> **listaProductos, Producto nuevo)
{
    if (!existe(listaProductos, nuevo))
    {
        InsertarFinal(listaProductos, nuevo);
        return true;
    }
    else
    {
        return false;
    }
}

void imprimirLista(TNodo<Producto> **listaProductos)
{
    TNodo<Producto> *producto = *listaProductos;
    Producto actual;
    while (producto != NULL)
    {
        actual = producto->dato;
        printf("Producto: %s - Codigo: %i - Costo: %.2f$ \n", actual.nombre, actual.codigo, actual.costo);
        producto = producto->sig;
    }
}

bool eliminarProducto(TNodo<Producto> **listaProductos, int codigo)
{
    int pos = 0;
    TNodo<Producto> *producto = *listaProductos;
    Producto actual;
    Producto aux;
    while (producto != NULL)
    {
        actual = producto->dato;
        if (actual.codigo == codigo)
        {
            EliminarPosicion(listaProductos, pos);
            return true;
        }
        pos++;
        producto = producto->sig;
    }
    return false;
}

//TODO implementar metodo
Producto* consultarProducto(TNodo<Producto> **listaProductos, int codigo) {
    TNodo<Producto> *act;
    act = *listaProductos;
    bool encontrado = false;
    
    while(act != NULL && !encontrado) {
        if((act->dato).codigo == codigo) {
            encontrado = true;
            break;
        }
        act = act->sig;
    }

    if(encontrado)
        return &(act->dato);
    else
        return NULL;
}

//TODO implementar metodo
bool venderProducto(TNodo<Producto> **listaProductos, int codigo) {
    return false;
}

//TODO implementar metodo
TNodo<Producto> *darProductosMasVendidos(TNodo<Producto> **listaProductos) {
    return NULL;
}