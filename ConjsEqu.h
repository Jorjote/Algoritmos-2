#ifndef ConjsEqu_H
#define ConjsEqu_H
#include "Modulos Basicos/aed2.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>

template<typename T>
class ConjsEqu
{
        private:         
         struct dato
        {          
          dato(Conj<T> a,Nat b):clase(a),id(b){ clase=a;id=b;}
          dato(){Conj<T> conjVacio;Nat b=0; clase=conjVacio;id=b;} // constructor de dato por defecto. b=0 por defecto.
          Conj<T> clase;
          Nat id;
        };
        Lista<dato> elementos;// es el campo que almacena todo.
   

   public:


  class Iterador  
  {
  private:
    typename Lista<dato>::Iterador itClaseElem;
    typename Conj<T>::Iterador itElem;
    friend typename ConjsEqu<T>::Iterador ConjsEqu<T>::CrearIt();

    struct tuplaIt{
        tuplaIt(Conj<T> a,T b,Nat c):clase(a),elemento(b),valor(c){ clase=a;elemento=b;valor=c;}
        Conj<T> clase;
        T elemento;
        Nat valor;
    };

  public:
    Iterador(ConjsEqu<T>& e);// OK
    Iterador(); // constructor por defecto. OK.
    Iterador::tuplaIt Siguiente();  // OK  
    T elementoActual(); // OK
    Conj<T> claseActual();  // OK
    Nat valorActual();  // OK
    ConjsEqu<T> dameRelacion();  // FALTAAAAAA   PROGRAMAR ESTOOOOOO.
    void Avanzar();  // OK
    bool HaySiguiente();  // OK
    bool HayAnterior(); // OK
    void ItActualizarElem(Nat n);  // OK

  };// FIN SUB CLASE PUBLICA ITERADOR

        public:
        ConjsEqu();// constructor por defecto.
         ~ConjsEqu();
        Iterador relacionar(Nat n, T elem); // OK
        Conj<T> dameConjEquivalencia(Nat n); // OK
        Conj<Nat> valoresDefinidos(); // OK
        void eliminar(T elem);// OK
        Conj<T> elementosDefinidos();  // OK
        Iterador CrearIt(); // Crear el iterador.  // OK
        std::ostream& Mostrar(std::ostream& os) ;



};

template <typename T>
std::ostream& operator<<(std::ostream& os, ConjsEqu<T>& CEQ)
{
  return CEQ.Mostrar(os);
}


//funcion a revisar: ClaseActual;

#endif // CONJEQ_H
