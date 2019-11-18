#include <iostream>
#include "lista.cpp"
#include "pila.cpp"
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
TNodo<ProductoCarrito> *carritoCompras;

void interfazAdministrador();
void interfazUsuario();

char archivo[50];

/**
 * Caso de prueba agregando 15 productos a la lista
 */
void setup1()
{
    for (int i = 0; i < 15; i++)
    {
        Producto p;
        crearProducto(p);
        p.codigo = 1000 + i;
        strcpy(p.nombre, "producto");
        InsertarFinal(&listaProductos, p);
    }
}

int main()
{
    strcpy(archivo, "productos.dat");
    int n;

    int a;
    CrearLista(&listaProductos);
    cout << "Desea cargar la informacion reciente?" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    cin >> n;
    if (n == 1)
    {
        if (cargar(&listaProductos, archivo))
        {
            cout << "Se ha cargado el archivo "
                 << "productos.dat"
                 << " con exito" << endl;
        }
        else
            cout << "No se ha logrado cargar el archivo" << endl;
        ;
        system("pause");
    }
    while (true)
    {
        system("CLS");
        cout << "Ingrese el tipo de usuario:" << endl;
        cout << "1. Administrador \n2. Usuario \n3. Salir del programa" << endl;
        cin >> n;

        switch (n)
        {
        case 1:
            system("CLS");
            ordenarLista(&listaProductos, NOMBRE);
            interfazAdministrador();
            break;
        case 2:
            system("CLS");
            interfazUsuario();
            break;
        case 3:
            return 0;
        default:
            cout << "Ingrese una de las opciones de arriba" << endl;
            break;
        }
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
        cout << "6. Listar productos" << endl;
        cout << "7. Volver al menu" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            system("CLS");
            Producto nuevo;
            crearProducto(nuevo);
            cout << "Ingresar codigo (Solo numeros): " << endl;
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
            cout << "Esta en promocion? \n1. Si\n2. No" << endl;
            n = 0;
            cin >> n;
            if (n == 1)
                nuevo.enPromocion = true;
            cout << "Ingresar cantidad disponible:" << endl;
            cin >> nuevo.cantidadDisponible;
            if (agregarProducto(&listaProductos, nuevo))
            {
                system("CLS");
                cout << "Se ha agregado el producto" << endl;
                imprimirLista(&listaProductos);
            }
            else
            {
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
                cout << "Esta en promocion? \n1. Si\n2. No" << endl;
                n = 0;
                cin >> n;
                if (n == 1)
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
            if (eliminarProducto(&listaProductos, codigo))
            {
                system("CLS");
                cout << "Se ha eliminado el producto. " << endl;
            }
            else
            {
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
                cout << "Promocion?: ";
                if (consultado->enPromocion)
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
            act = darProductosMasVendidos(listaProductos);
            cout << "Productos mas vendidos: " << endl;
            while (act != NULL)
            {
                cout << (act->dato).nombre;
                for (int i = 0; (i < (act->dato).cantidadVendida); i++)
                {
                    cout << " *";
                }
                cout << endl;
                act = act->sig;
            }
            cout << endl;
            cout << "Productos menos vendidos: " << endl;
            act = darProductosMenosVendidos(listaProductos);
            while (act != NULL)
            {
                cout << (act->dato).nombre;
                for (int i = 0; i < (act->dato).cantidadVendida; i++)
                {
                    cout << " *";
                }
                cout << endl;
                act = act->sig;
            }

            break;
        case 6:
            system("CLS");
            imprimirLista(&listaProductos);
            break;
        case 7:
            system("CLS");
            cout << "Desea guardar los cambios antes de volver al menu?" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            int aux;
            cin >> aux;
            switch (aux)
            {
            case 1:
                if (guardar(listaProductos))
                {
                    cout << "Se han guardado los cambios" << endl;
                    system("pause");
                }
                //TODO agregar codigo para guardar los cambios
                return;
                break;
            case 2:
                system("CLS");
                cout << "Los cambios no han sido guardados" << endl;
                CrearLista(&listaProductos);
                cargar(&listaProductos, archivo);
                return;
                break;
            default:
                system("cls");
                cout << "Opcion incorrecta" << endl;
                system("pause");
                break;
            }
        }
    }
}

//TODO implementar la interfaz de usuario
void interfazUsuario()
{
    int n;
    int codigo;

    while (true)
    {
        cout << endl;
        cout << "--Cliente--" << endl;
        cout << "1. Buscar un producto" << endl;
        cout << "2. Ordenar lista" << endl;
        cout << "3. Mostrar catalogo" << endl;
        cout << "4. Mostrar carrito" << endl;
        cout << "5. Volver al menu" << endl;
        cin >> n;
        switch (n)
        {
        case 1:
            char cadena[100];
            system("cls");
            cout << "Ingrese una cadena para buscar (maximo 100 caracteres):" << endl;
            cin.ignore();
            cin.getline(cadena, sizeof(cadena));
            TNodo<Producto> *busqueda;
            CrearLista(&busqueda);
            busqueda = buscarProductos(&listaProductos, cadena);
            TNodo<Producto> *act;
            act = busqueda;
            if(act == NULL) 
            {
                cout << "No se encontraron resultados para la busqueda" << endl;
            }
            cout << endl;
            while(act != NULL) 
            {
                printf("Codigo: %i - Nombre: %s - Descripcion: %s ", (act->dato).codigo, (act->dato).nombre, (act->dato).descripcion);
                cout << endl;
                act = act->sig;
            }
            system("pause");
            break;
        case 2:
            system("cls");
            int c;
            cout << "Ingrese el criterio por el cual desesa ordenar la lista:" << endl;
            cout << "1. NOMBRE\n2. PRECIO\n3. RESTAURANTES\n4. PROMOCIONES" << endl;
            cin >> c;
            ordenarLista(&listaProductos, c);
            imprimirLista(&listaProductos);
            break;
        case 3:
            mostrarCatalogo(&listaProductos, &carritoCompras);
            break;
        case 4:
            mostrarCarrito(&carritoCompras, &listaProductos);
            break;
        case 5:
            return;
        default:
            break;
        }
    }
}