#include "pila.h"

template <class T>
void CrearPila(NodoPila<T> **cab)
{
    *cab = NULL;
}

template <class T>
void DestruirPila(NodoPila<T> **cab)
{
    NodoPila<T> *aux;
    aux = *cab;
    while (aux != NULL)
    {
        *cab = (*cab)->sig;
        delete (aux);
        aux = *cab;
    }
}

template <class T>
NodoPila<T> *CrearNodo(T dato)
{
    NodoPila<T> *nuevo = new NodoPila<T>();

    nuevo->sig = NULL;
    nuevo->dato = dato;
    return nuevo;
}

template <class T>
void push(NodoPila<T> **cab, T dato)
{
    NodoPila<T> *nuevo = CrearNodo(dato);

    nuevo->sig = *cab;
    *cab = nuevo;
}

template <class T>
bool pop(NodoPila<T> **cab, T &dato)
{
    NodoPila<T> *aux, *aux1;

    if (*cab != NULL)
    {
        aux = *cab;
        *cab = (*cab)->sig;
        dato = aux->dato;
        delete (aux);
        return true;
    }
    return false;
}

template <class T>
T peek(NodoPila<T> **cab) {
    if(*cab == NULL) {
        return NULL;
    }
    return (*cab)->dato;
}

template <class T>
bool PilaVacia(NodoPila<T> **cab)
{
    return *cab == NULL;
}