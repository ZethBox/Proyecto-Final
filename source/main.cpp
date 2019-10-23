#include <iostream>
#include "lista.cpp"
#include "modelo.cpp"
#include "string.h"

using namespace std;

/**
 * Lista total de los productos
 */ 
TNodo<Producto> *listaProductos;

/**
 * Lista de productos a comprar
 */ 
TNodo<Producto> *carritoCompras;

void interfazAdministrador();
void interfazUsuario();

int main()
{
    int n;

    CrearLista(&listaProductos);

    cout << "Ingrese el tipo de usuario:" << endl;
    cout << "1. Administrador \n2. Usuario" << endl;
    cin >> n;

    switch (n)
    {
    case 1:
        interfazAdministrador();
        break;
    case 2:
        interfazUsuario();
        break;
    default:
        cout << "Ingrese una de las opciones de arriba" << endl;
        break;
    }
}

void interfazAdministrador()
{
    int n;
    int codigo;
    while (true)
    {
        cout << endl;
        cout << "--Administrador--" << endl;
        cout << "1. Agregar un producto" << endl;
        cout << "2. Modificar un producto" << endl;
        cout << "3. Borrar un producto" << endl;
        cout << "4. Consultar un producto" << endl;
        cout << "5. Mostrar los 5 productos mas vendidos" << endl;
        cout << "6. Salir del programa" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            Producto nuevo;
            crearProducto(nuevo);
            cout << "Ingresar codigo: " << endl;
            cin >> nuevo.codigo;
            cout << "Ingresar costo: " << endl;
            cin >> nuevo.costo;
            cout << "Ingresar nombre: " << endl;
            cin.ignore();
            cin.getline(nuevo.nombre, 50);
            cout << "Ingresar descripcion: " << endl;
            cin.getline(nuevo.descripcion, 500);
            cout << "Ingresar precio de venta: " << endl;
            cin >> nuevo.precioVenta;
            cout << "Ingresar nombre del restaurante" << endl;
            cin.ignore();
            cin.getline(nuevo.restaurante, 100);
            agregarProducto(&listaProductos, nuevo);
            imprimirLista(&listaProductos);
            break;
        case 2:
            cout << "Ingresar codigo del producto a modificar: " << endl;
            codigo = 0;
            cin >> codigo;
            Producto *modificado;
            modificado = consultarProducto(codigo);
            if (modificado != NULL)
            {
                cout << "Ingresar nuevo costo del producto: " << endl;
                cin >> modificado->costo;
                cout << "Ingresar nueva descripcion del producto: " << endl;
                cin.ignore();
                cin.getline(modificado->descripcion, 500);
                cout << "Ingresar nuevo precio de venta del producto: " << endl;
                cin >> modificado->precioVenta;
            }
            else
            {
                cout << "El codigo ingresado no se encontro en la lista de productos!" << endl;
            }
            break;
        case 3:
            cout << "Ingresar codigo del producto a eliminar: " << endl;
            codigo = 0;
            cin >> codigo;
            if (eliminarProducto(&listaProductos, codigo))
                cout << "Se ha eliminado el producto. " << endl;
            else
                cout << "No se encontro el codigo en la lista de productos!" << endl;
            break;
        case 4:
            cout << "Ingresar el codigo del producto buscado: " << endl;
            codigo = 0;
            cin >> codigo;
            Producto *consultado;
            consultado = consultarProducto(codigo);
            if (consultado != NULL)
            {
                cout << "Codigo: " << consultado->codigo << endl;
                cout << "Nombre: " << consultado->nombre << endl;
                cout << "Precio de venta: " << consultado->precioVenta << endl;
            }
            else
            {
                cout << "El codigo ingresado no se encontro en la lista de productos!" << endl;
            }
            break;
        case 5:
            TNodo<Producto> *act;
            act = darProductosMasVendidos(&listaProductos);
            int puesto;
            puesto = 1;
            if(act == NULL) {
                cout << "La lista esta vacia" << endl;
            }
            while(act != NULL) {
                cout << puesto++ << " ";
                cout << "Producto: " << (act->dato).nombre << endl;
                cout << "Codigo: " << (act->dato).codigo << endl;
                act = act->sig;
            }
            break;
        case 6:
            cout << "Desea guardar los cambios antes de salir?" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            int aux;
            cin >> aux;
            switch (aux)
            {
            case 1:
                cout << "Se han guardado los cambios" << endl;
                //TODO agregar codigo para guardar los cambios
                return;
                break;
            case 2:
                cout << "Los cambios no han sido guardados" << endl;
                return;
                break;
            default:
                cout << "Opcion incorrecta" << endl;
                break;
            }
            break;
        default:
            break;
        }
    }
}

//TODO implementar la interfaz de usuario
void interfazUsuario()
{
    cout << endl;
    cout << "--Cliente--" << endl;
    cout << "1. Buscar un producto" << endl;
    cout << "2. Ordenar lista" << endl;
    cout << "3. Mostrar catálogo" << endl;
    cout << "4. Mostrar carrito" << endl;
    cout << "6. Salir del programa" << endl;
    cout << endl;
    cout << "Ingrese el texto para filtrar la lista" << endl;
    cout << endl;
    cout << "Ingrese el criterio por el cual ordenar la lista" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Precio" << endl;
    cout << "3. Restaurante" << endl;
    cout << "4. Promociones" << endl;
    cout << endl;
    cout << "1. 1000\tCoca Cola\t2.99" << endl;
    cout << "2. 1010\tSprite\t2.99" << endl;
    cout << "3. 1020\tPepsi\t2.99" << endl;
    cout << "Puede ingresar el numero respectivo del producto para agregarlo al carrito, o 0 para volver" << endl;
    cout << endl;
    cout << "--Carrito de Compras--" << endl;
    cout << "1. 1000\tCoca Cola\t2.99" << endl;
    cout << "2. 1010\tSprite\t2.99" << endl;
    cout << "Puede ingresar el numero respectivo del producto para quitarlo o incrementar la cantidad que se desea comprar del producto" << endl;
    cout << endl;
    cout << "Ingresar nuevo costo del producto: " << endl;
    cout << "Ingresar nueva descripcion del producto: " << endl;
    cout << "Ingresar nuevo precio de venta del producto: " << endl;
    cout << "Ingresar 1. Si el producto esta en promocion, 2. Si no esta en promocion" << endl;
    cout << endl;
}