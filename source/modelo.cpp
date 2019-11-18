#include "modelo.h"
#include "lista.h"
#include "string.h"
#include <iostream>
#include <fstream>
using namespace std;

void crearProducto(Producto &producto)
{
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

void crearProducto(Producto &producto, int cod, double costo, char *nombre, char *desc, double precio, bool promo, char *res)
{
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
    if (producto == NULL)
        cout << "No hay productos" << endl;
    while (producto != NULL)
    {
        actual = producto->dato;
        char promocion[4];
        strcpy(promocion, "No");
        if(actual.enPromocion)
            strcpy(promocion, "Si");
        printf("Codigo: %i - Costo: %.2f$ - Inventario: X%i - Vendidos: %i - Promocion: %s - Nombre: %s\n", actual.codigo, actual.costo, actual.cantidadDisponible, actual.cantidadVendida, promocion, actual.nombre);
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
Producto *consultarProducto(TNodo<Producto> **listaProductos, int codigo)
{
    TNodo<Producto> *act;
    act = *listaProductos;
    bool encontrado = false;

    while (act != NULL && !encontrado)
    {
        if ((act->dato).codigo == codigo)
        {
            encontrado = true;
            break;
        }
        act = act->sig;
    }

    if (encontrado)
        return &(act->dato);
    else
        return NULL;
}

//TODO implementar metodo
TNodo<Producto> *darProductosMasVendidos(TNodo<Producto> *listaProductos)
{
    TNodo<Producto> *ListaRetornar;
    CrearLista(&ListaRetornar);

    TNodo<Producto> *i, *j;
    i = listaProductos;
    Producto Temp;
    while (i->sig != NULL)
    {
        j = i->sig;
        while (j != NULL)
        {
            if ((i->dato).cantidadVendida < (j->dato).cantidadVendida)
            {
                Temp = i->dato;
                i->dato = j->dato;
                j->dato = Temp;
            }
            j = j->sig;
        }
        i = i->sig;
    }
    int k = 0;
    TNodo<Producto> *aux = listaProductos;
    while (aux != NULL && k < 5)
    {
        InsertarFinal(&ListaRetornar, aux->dato);
        aux = aux->sig;
        k++;
    }
    return ListaRetornar;
}

TNodo<Producto> *darProductosMenosVendidos(TNodo<Producto> *listaProductos)
{
    TNodo<Producto> *ListaRetornar;
    CrearLista(&ListaRetornar);

    TNodo<Producto> *i, *j;
    i = listaProductos;
    Producto Temp;
    while (i->sig != NULL)
    {
        j = i->sig;
        while (j != NULL)
        {
            if ((i->dato).cantidadVendida > (j->dato).cantidadVendida)
            {
                Temp = i->dato;
                i->dato = j->dato;
                j->dato = Temp;
            }
            j = j->sig;
        }
        i = i->sig;
    }
    int k = 0;
    TNodo<Producto> *aux = listaProductos;
    while (aux != NULL && k < 5)
    {
        InsertarFinal(&ListaRetornar, aux->dato);
        aux = aux->sig;
        k++;
    }
    return ListaRetornar;
}

bool guardar(TNodo<Producto> *listaProductos)
{
    ofstream archivo("productos.dat", ios::binary);
    TNodo<Producto> *aux = listaProductos;
    if (archivo)
    {
        while (aux != NULL)
        {
            archivo.write((char *)&(aux->dato), sizeof(aux->dato));
            aux = aux->sig;
        }
        archivo.close();
        return true;
    }
    return false;
}

bool cargar(TNodo<Producto> **listaProductos, char *nombreArchivo)
{
    Producto Reg;
    ifstream arch(nombreArchivo, ios::binary);
    if (arch)
    {
        while (arch.read((char *)&Reg, sizeof(Reg)))
        {
            InsertarFinal(listaProductos, Reg);
        }
        arch.close();
        return true;
    }
    return false;
}

//--------
void mostrarCarrito(TNodo<ProductoCarrito> **carrito, TNodo<Producto> **listaProductos)
{
    system("cls");
    TNodo<ProductoCarrito> *aux = *carrito;
    if (aux == NULL)
    {
        cout << "El carrito esta vacio" << endl;
        system("pause");
        return;
    }
    cout << "Carrito de compras:" << endl;
    cout << "-cod: x#\tnombre" << endl;
    while (aux != NULL)
    {
        cout << (aux->dato).producto.codigo << ": x" << (aux->dato).cantidad << "\t" << (aux->dato).producto.nombre << endl;
        aux = aux->sig;
    }
    cout << "1. Comprar todo el carrito" << endl;
    cout << "2. Eliminar elementos del carrito" << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        comprarCarrito(carrito, listaProductos);
    }
    else if (n == 2)
    {
    }
}

void agregarCarrito(TNodo<ProductoCarrito> **carrito, Producto p)
{
    TNodo<ProductoCarrito> *act;
    act = *carrito;
    bool enCarrito = false;
    while (act != NULL)
    {
        if ((act->dato).producto.codigo == p.codigo)
        {
            enCarrito = true;
            break;
        }
        act = act->sig;
    }
    if (enCarrito)
    {
        (act->dato).cantidad++;
    }
    else
    {
        ProductoCarrito nuevo;
        nuevo.producto = p;
        nuevo.cantidad = 1;
        InsertarFinal(carrito, nuevo);
    }
    cout << "Se ha insertado el producto en el carrito" << endl;
}

int mostrarPagina(Producto *productos, int size, int numero, TNodo<ProductoCarrito> **carrito)
{
    system("cls");
    cout << "Pagina " << numero << endl;
    int i;
    cout << "#. |-cod| \t|Disponible: X#|\tNombre" << endl;
    cout << "-----------------------------------------------" << endl;
    for (i = 0; i < size; i++)
    {
        cout << i << ". |" << productos[i].codigo << "|\t|"
             << "Disponible: X" << productos[i].cantidadDisponible << "|\t" << productos[i].nombre << endl;
    }
    cout << endl;
    cout << "Ingrese el numero del producto para agregarlo al carrito o" << endl;
    cout << "Ingrese: -1 pagina anterior, o 10 pagina siguiente:" << endl;
    cout << "Ingrese un numero menor a -1 o mayor a 10 para volver" << endl;
    int n;
    while (cin >> n)
    {
        if (n >= 0 && n < size)
        {
            system("cls");
            cout << "Pagina " << numero << endl;
            agregarCarrito(carrito, productos[n]);
            for (i = 0; i < size; i++)
            {
                cout << i << ". |" << productos[i].codigo << "|\t|"
                     << "Disponible: X" << productos[i].cantidadDisponible << "|\t" << productos[i].nombre << endl;
            }
            cout << endl;
            cout << "Ingrese otro numero para agregar mas al carrito: " << endl;
            ;
            cout << "Ingrese: -1 pagina anterior, o 10 pagina siguiente:" << endl;
            cout << "Ingrese un numero menor a -1 o mayor a 10 para volver" << endl;
        }
        else
        {
            //Si quiere retroceder
            if (n == -1)
                return n;
            //Si quiere avanzar
            else if (n == 10)
                return 1;
            //Si quiere salir
            else
                return 0;
        }
    }
    return 0;
}

void mostrarCatalogo(TNodo<Producto> **lista, TNodo<ProductoCarrito> **carrito)
{
    NodoPila<Pagina> *pila1;
    CrearPila(&pila1);
    NodoPila<Pagina> *pila2;
    CrearPila(&pila2);
    TNodo<Producto> *aux = *lista;

    int i;
    int numPaginas = 0;

    while (aux != NULL)
    {
        Pagina p;
        for (i = 0; i < 10 && aux != NULL; i++)
        {
            p.productos[i] = aux->dato;
            aux = aux->sig;
        }
        p.size = i;

        push(&pila2, p);
        numPaginas++;
    }
    //Devuelve las paginas
    while (!PilaVacia(&pila2))
    {
        Pagina p;
        pop(&pila2, p);
        push(&pila1, p);
    }
    if (peek(&pila1) != NULL)
    {
        Pagina *x = peek(&pila1);
        //Numero de la pagina actual
        int i = 1;
        int pagina = mostrarPagina(x->productos, x->size, i, carrito);
        while (pagina != 0)
        {
            Pagina p;
            if (pagina == 1 && i < numPaginas)
            {
                if (pop(&pila1, p))
                {
                    push(&pila2, p);
                    i++;
                }
            }
            else if (pagina == -1 && i > 0)
            {
                if (pop(&pila2, p))
                {
                    push(&pila1, p);
                    i--;
                }
            }
            x = peek(&pila1);
            pagina = mostrarPagina(x->productos, x->size, i, carrito);
        }
    }
}

void comprarCarrito(TNodo<ProductoCarrito> **carrito, TNodo<Producto> **listaProductos)
{
    TNodo<ProductoCarrito> *aux = *carrito;
    Producto *producto;
    double total = 0;
    while (aux != NULL)
    {
        producto = consultarProducto(listaProductos, (aux->dato).producto.codigo);
        if ((aux->dato).cantidad <= producto->cantidadDisponible)
        {
            cout << "Codigo: " << producto->codigo << " - Nombre: " << producto->nombre << " - Precio c/u: " << producto->precioVenta << "$"
                 << " - X" << (aux->dato).cantidad << endl;
            producto->cantidadDisponible -= (aux->dato).cantidad;
            producto->cantidadVendida += (aux->dato).cantidad;
            int cantidad = (aux->dato).cantidad;
            total += producto->precioVenta * (aux->dato).cantidad;
            aux = aux->sig;
            for (int i = 0; i < cantidad; i++)
            {
                eliminarCarrito(carrito, producto->codigo);
            }
        }
        else
        {
            system("cls");
            cout << "Producto: '" << producto->nombre << "' No pudo ser comprado -> Cantidad disponible: " << producto->cantidadDisponible << " - Cantidad pedida: " << (aux->dato).cantidad << endl;
            aux = aux->sig;
        }
    }
    double iva = total * 0.16;
    cout << "Subtotal = " << total << endl;
    cout << "Iva: 16% = " << iva << endl;
    cout << "Total = " << total + iva << endl;
    aux = *carrito;
    if (aux != NULL)
    {
        cout << "No se pudieron comprar todos elementos del carrito ya que la cantidad disponible no era suficiente, puede eliminarlos del carrito o esperar a que se modifique el inventario" << endl;
    }
    guardar(*listaProductos);
    system("pause");
}

bool eliminarCarrito(TNodo<ProductoCarrito> **carrito, int codigo)
{
    int pos = 0;
    TNodo<ProductoCarrito> *aux = *carrito;
    while (aux != NULL)
    {
        if (aux->dato.producto.codigo == codigo)
        {
            if ((aux->dato).cantidad > 1)
            {
                (aux->dato).cantidad--;
                return true;
            }
            else
            {
                EliminarPosicion(carrito, pos);
                return true;
            }
        }
        pos++;
        aux = aux->sig;
    }
    return false;
}

TNodo<Producto> *buscarProductos(TNodo<Producto> **listaProductos, char *str)
{
    TNodo<Producto> *busqueda;
    CrearLista(&busqueda);
    TNodo<Producto> *aux = *listaProductos;
    int sz = strlen(str);
    int i;
    for (i = 0; i < sz; i++)
    {
        str[i] = (char)tolower(str[i]);
    }
    char nombre[50];
    char desc[500];
    while (aux != NULL)
    {
        strcpy(nombre, (aux->dato).nombre);
        for (i = 0; i < strlen(nombre); i++)
        {
            nombre[i] = (char)tolower(nombre[i]);
        }

        strcpy(desc, (aux->dato).descripcion);
        for (i = 0; i < strlen(desc); i++)
        {
            desc[i] = (char)tolower(desc[i]);
        }

        if (strstr(nombre, str) != NULL || strstr(desc, str) != NULL)
        {
            InsertarFinal(&busqueda, aux->dato);
        }
        aux = aux->sig;
    }
    return busqueda;
}

//se ordena la lista por referencia de mayor a menor en todos los casos
//en precio lo ordene por precioVenta y no por costo,
//ademas, analizando mejor, ordene todo menos promociones de menor a mayor, para que quedara en orden
//alfabetico en los casos de nombre y restaurante y de lo mas barato a lo mas caro por precioVenta.
void ordenarLista(TNodo<Producto> **listaProductos, int criterio)
{
    TNodo<Producto> *i, *j;
    i = *listaProductos;
    Producto Temp;
    switch (criterio)
    {
    case NOMBRE:
        while (i->sig != NULL)
        {
            j = i->sig;
            while (j != NULL)
            {
                if (strcmp((i->dato).nombre, (j->dato).nombre) == 1)
                {
                    Temp = i->dato;
                    i->dato = j->dato;
                    j->dato = Temp;
                }
                j = j->sig;
            }
            i = i->sig;
        }
        break;

    case PRECIO:
        while (i->sig != NULL)
        {
            j = i->sig;
            while (j != NULL)
            {
                if ((i->dato).precioVenta > (j->dato).precioVenta)
                {
                    Temp = i->dato;
                    i->dato = j->dato;
                    j->dato = Temp;
                }
                j = j->sig;
            }
            i = i->sig;
        }
        break;

    case RESTAURANTE:
        while (i->sig != NULL)
        {
            j = i->sig;
            while (j != NULL)
            {
                if (strcmp((i->dato).restaurante, (j->dato).restaurante) == 1)
                {
                    Temp = i->dato;
                    i->dato = j->dato;
                    j->dato = Temp;
                }
                j = j->sig;
            }
            i = i->sig;
        }
        break;
    case PROMOCIONES:
        while (i->sig != NULL)
        {
            j = i->sig;
            while (j != NULL)
            {
                if ((i->dato).enPromocion < (j->dato).enPromocion)
                {
                    Temp = i->dato;
                    i->dato = j->dato;
                    j->dato = Temp;
                }
                j = j->sig;
            }
            i = i->sig;
        }
        break;
    default:
        cout << "Criterio invalido" << endl;
        break;
    }
}