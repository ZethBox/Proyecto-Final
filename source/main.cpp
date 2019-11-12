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
    system("CLS");
    cout << "Ingrese el tipo de usuario:" << endl;
    cout << "1. Administrador \n2. Usuario" << endl;
    cin >> n;

    switch (n)
    {
    case 1:
        system("CLS");
        interfazAdministrador();
        break;
    case 2:
        system("CLS");
        interfazUsuario();
        break;
    default:
        cout << "Ingrese una de las opciones de arriba" << endl;
        break;
    }
}

void interfazAdministrador()
{
    //Variables auxiliares
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
        cout << "5. Mostrar estadisticas de ventas" << endl;
        cout << "6. Salir del programa" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            system("CLS");
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
            cout << "Ingresar nombre del restaurante:" << endl;
            cin.ignore();
            cin.getline(nuevo.restaurante, 100);
            cout << "Esta en promocion? \n1. Si\nCualquier otra letra si no" << endl;
            n = 0;
            cin >> n;
            if(n == 1) 
                nuevo.enPromocion = true;
            cout << "Ingresar cantidad disponible:" << endl;
            cin >> nuevo.cantidadDisponible;
            if (agregarProducto(&listaProductos, nuevo)) {
                system("CLS");
                cout << "Se ha agregado el producto" << endl;
                imprimirLista(&listaProductos);
            }
            else {
                system("CLS");
                cout << "Un producto con este codigo ya existe en la lista" << endl;
            }
            break;
        case 2:
            system("CLS");
            cout << "Ingresar codigo del producto a modificar: " << endl;
            codigo = 0;
            cin >> codigo;
            Producto *modificado;
            modificado = consultarProducto(&listaProductos, codigo);
            if (modificado != NULL)
            {
                cout << "Ingresar nuevo costo del producto: " << endl;
                cin >> modificado->costo;
                cout << "Ingresar nueva descripcion del producto: " << endl;
                cin.ignore();
                cin.getline(modificado->descripcion, 500);
                cout << "Ingresar nuevo precio de venta del producto: " << endl;
                cin >> modificado->precioVenta;
                cout << "Ingresar nueva cantidad disponible:" << endl;
                cin >> modificado->cantidadDisponible;
                cout << "Esta en promocion? \n1. Si\nCualquier otra letra si no" << endl;
                n = 0;
                cin >> n;
                if(n == 1)
                    modificado->enPromocion = true;
                system("CLS");
                cout << "Se ha modificado el producto" << endl;
            }
            else
            {
                cout << "El codigo ingresado no se encontro en la lista de productos!" << endl;
            }
            break;
        case 3:
            system("CLS");
            cout << "Ingresar codigo del producto a eliminar: " << endl;
            codigo = 0;
            cin >> codigo;
            if (eliminarProducto(&listaProductos, codigo)) {
                system("CLS");
                cout << "Se ha eliminado el producto. " << endl;
            }
            else{
                system("CLS");
                cout << "No se encontro el codigo en la lista de productos!" << endl;
            }
            break;
        case 4:
            system("CLS");
            cout << "Ingresar el codigo del producto buscado: " << endl;
            codigo = 0;
            cin >> codigo;
            Producto *consultado;
            consultado = consultarProducto(&listaProductos, codigo);
            if (consultado != NULL)
            {
                system("CLS");
                cout << "Codigo: " << consultado->codigo << endl;
                cout << "Nombre: " << consultado->nombre << endl;
                cout << "Costo: " << consultado->costo << endl;
                cout << "Precio de venta: " << consultado->precioVenta << endl;
                cout << "Descripcion: " << consultado->descripcion << endl;
                cout << "Promocion: ";
                if(consultado->enPromocion)
                    cout << "Si" << endl;
                else
                    cout << "No" << endl;
                cout << "Cantidad disponible: " << consultado->cantidadDisponible << endl;
                cout << "Cantidad vendida: " << consultado->cantidadVendida << endl;
            }
            else
            {
                system("CLS");
                cout << "El codigo ingresado no se encontro en la lista de productos!" << endl;
            }
            break;
        case 5:
            system("CLS");
            TNodo<Producto> *act;
            act = darProductosMasVendidos(&listaProductos);
            int puesto;
            
            break;
        case 6:
            system("CLS");
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
                system("CLS");
                cout << "Los cambios no han sido guardados" << endl;
                return;
                break;
            default:
                system("CLS");
                cout << "Opcion incorrecta" << endl;
                break;
            }
            break;
        default:
            system("CLS");
            imprimirLista(&listaProductos);
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
}