#ifndef __PILA_H
  #define __PILA_H

  #include <stdlib.h>
  #include <conio.h>

  template <class T>
  struct NodoPila
  {
	 T dato;
	 struct NodoPila<T> *sig;

  };

  template <class T>
  void CrearPila(NodoPila<T> **cab);

  template <class T>
  void DestruirPila(NodoPila<T> **cab);

  template <class T>
  NodoPila<T> *CrearNodo(T dato);

  template <class T>
  void push(NodoPila<T> **cab, T dato);

  template <class T>
  bool pop(NodoPila<T> **cab, T &dato);

  /**
   * Retorna el primer elemento de la pila
  */ 
  template <class T>
  T peek(NodoPila<T> **cab);

  template <class T>
  bool PilaVacia(NodoPila<T> **cab);

#endif
