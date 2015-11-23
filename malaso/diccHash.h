#ifndef diccHash_H_
#define diccHash_H_
#include "Modulos Basicos/aed2.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "assert.h"
#include <cassert>

template<typename A,typename B>
class diccHash { // REQUIERE QUE A SEA COMPATIBLE CON LA OPERACION % (RESTO).


 private:
  		 struct tupla // tupla que almacena clave y significado en sus campos
        {
        	// constructores de Tupla
        	//:clave(0), significado(0)
             tupla(){A c; clave = c; B s; significado = s;}
             tupla(A c, B s):clave(c){ significado = s;}
             A clave;
             B significado;
        };

	Nat FuncionDeHash(const A& clave) const
	{
		Nat res;
		res = clave % ((this->tabla).Tamanho());
		return res;
	}

 // campo tabla
    Arreglo<Lista<tupla > > tabla;
    Nat cardinal;





  public:
  	class Iterador;



  	diccHash(Nat capacidadMaxima); // crear DiccHash
    diccHash(); // constructor por defecto
	//~diccHash();
	Iterador Definir(const A clave,const B significado);
	const B& Obtener(const A& clave) const;
	B& Obtener(const A& clave);
	void Borrar(const A& clave);
	bool EstaDefinida(const A& clave) const;
	//Iterador CrearIt(const A& clave); // funcion publica de diccHash y privada friend de itDicchash. retorna iterador y se llama crearIt
	//Iterador CrearIt(); // sin parametros.
  //void mostrardiccHash(std::ostream&) const;

	 /**********************************
   * Iterador de DiccHash Modificable *
   **********************************/
   // EL ITERADOR NO SIRVE SI UN ELEMENTO DEL DICC SE BORRO.
  class Iterador
  {
  public:
  	  // Iterador( diccHash<A,B>& d); // iterador desde una clave cualquiera
      // Iterador( diccHash<A,B>& d,const A& clave); // iterador desde la clave clave
      Iterador(typename Lista<diccHash<A,B>::tupla>::Iterador); 
      Iterador(); // iterador por defecto.
      bool HaySiguiente() const;
      A& SiguienteClave();
      B& SiguienteSignificado(); // retorna siguiente significado
      void Avanzar();
      Iterador& operator = (typename diccHash<A,B>::Iterador otro);
      //Iterador(const typename diccHash<A>::Iterador& otro); //  constructor por copia.
      //Iterador& operator = (const typename diccHash::Iterador& otro);
      //bool HayAnterior() const;
      //T& Anterior();
      //const T& Anterior() const;
      //void Retroceder();
      //void AgregarComoAnterior(const T& elem);
      //void AgregarComoSiguiente(const T& elem);
      //void EliminarAnterior();
      //void EliminarSiguiente();
      //bool operator == (const typename diccHash::Iterador& otro) const;
  private:
  	typename Lista< typename diccHash<A,B>::tupla >::Iterador listaActual; //el campo listaActual del itDiccHash es un iterador modificable de Lista.
   // Nat posicionActual;
    // Arreglo<Lista< typename diccHash<A,B>::tupla > > *arr; //el campo arr del itDiccHash es un arreglo de listas de tuplas(A,B).
    //Nat contador;
   // friend typename diccHash<A,B>::Iterador diccHash<A,B>::CrearIt(const A& clave); // retorna iterador y se llama crearIt y pertenece a diccHash,no a iterador,osea el this es de diccHash.
    //friend typename diccHash<A,B>::Iterador diccHash<A,B>::CrearIt(); // sin parametros.
    //friend class diccHash::const_Iterador; // por ahora no hace falta const_iterador.
  };// FIN SUB CLASE PUBLICA ITERADOR

}; // FIN DE LA CLASE


template <typename A,typename B>
diccHash<A,B>::diccHash(Nat capacidadMaxima) // :tabla(??),capacidadMaxima(0) lista deinicializadion
{
	Arreglo<Lista<tupla > > arrAux(capacidadMaxima);
	Nat i=0;
		while(i<capacidadMaxima)
		{
			Lista<tupla> vacia;
			arrAux.Definir(i,vacia);
			i++;
	    }
	this -> tabla = arrAux;
  this->cardinal = 0; // 0 elementos. SE AGREGO RESPECTO AL DISEÑO
}



template <typename A,typename B>
diccHash<A,B>::diccHash() // constructor por defecto.
{
  Nat MinimoTamanio = 1; // un arr que puede almacenar elemento tiene como minimo tamanio 1.
  Arreglo<Lista<tupla > > arrAux(MinimoTamanio);
  Lista<tupla> ListaVacia;
  Nat pos=0;
  arrAux.Definir(pos,ListaVacia);
  this -> tabla = arrAux;
  this->cardinal = 0; // 0 elementos. SE AGREGO RESPECTO AL DISEÑO
}


template <typename A,typename B>
typename diccHash<A,B>::Iterador diccHash<A,B>::Definir(const A clave,const B significado)
{
    Nat posicionAsignada = this->FuncionDeHash(clave);
    tupla dato(clave,significado);
    //this->tabla[posicionAsignada].AgregarAdelante(dato);	// ESTO HABRIA QUE CAMBIARLO, SINO QUEDAN VARIAS CLAVES.
    // ESTE WHILE, PARA QUE NO SE AGREGUEN CLAVES VARIAS VECES, SINO MODIFICAR LA MISMA:
    typename Lista<diccHash<A,B>::tupla>::Iterador itLista =  this->tabla[posicionAsignada].CrearIt();
    while(itLista.HaySiguiente() && itLista.Siguiente().clave!= clave)
    {
        
        itLista.Avanzar();
    }
    if(itLista.HaySiguiente()){
      itLista.Siguiente().significado = significado;
    }
    else{
      itLista.AgregarComoSiguiente(dato);    
    this->cardinal = this->cardinal+1; // SE AGREGO RESPECTO AL DISEÑO.
    }
    return Iterador(itLista);//retorno iterador referencia.
}



template <typename A,typename B>
const B& diccHash<A,B>::Obtener(const A& clave) const
{
	Nat posicionAsignada = this->FuncionDeHash(clave);
	typename Lista<tupla>::const_Iterador itLista = this->tabla[posicionAsignada].CrearIt(); //iterador const (no modificable).
	while(clave != itLista.Siguiente().clave)
	{
        itLista.Avanzar();
	}

    return itLista.Siguiente().significado;
}

template <typename A,typename B>
B& diccHash<A,B>::Obtener(const A& clave)
{
	Nat posicionAsignada = this->FuncionDeHash(clave);
	typename Lista<tupla>::Iterador itLista = this->tabla[posicionAsignada].CrearIt(); //iterador const (no modificable).
	while(clave != itLista.Siguiente().clave)
	{
        itLista.Avanzar();
	}

    return itLista.Siguiente().significado;
}

template <typename A,typename B>
void diccHash<A,B>::Borrar(const A& clave)
{
Nat posicionAsignada = this->FuncionDeHash(clave);
typename Lista<tupla>::Iterador itLista = this->tabla[posicionAsignada].CrearIt(); //iterador modificable.
 while(itLista.HaySiguiente())
 {
     if(itLista.Siguiente().clave==clave)
     {
     	itLista.EliminarSiguiente();
       this->cardinal = this->cardinal-1; // SE AGREGO RESPECTO AL DISEÑO.
        itLista = this->tabla[posicionAsignada].CrearIt(); // VUELVO A CREAR EL ITERADOR, ESTO LO AGREGUE DEL TP
     }else{itLista.Avanzar();} //  ESTO LO AGREGUE DEL TP
 }
}



template <typename A,typename B>
bool diccHash<A,B>::EstaDefinida(const A& clave) const
{
Nat posicionAsignada = this->FuncionDeHash(clave);
typename Lista<tupla>::const_Iterador itLista = this->tabla[posicionAsignada].CrearIt(); //iterador no-modificable.
bool res=false;
while(itLista.HaySiguiente())
	{
		if(itLista.Siguiente().clave==clave){res=true;}
     itLista.Avanzar();
	}
return res;

}



/*template <typename A,typename B>
typename diccHash<A,B>::Iterador diccHash<A,B>::CrearIt(const A& clave) // con parametros.
{
return Iterador(*this,clave); // 2 parametros, referencia a la  instancia y la clave.
}*/

template <typename A,typename B>
diccHash<A,B>::Iterador::Iterador(typename Lista< diccHash<A,B>::tupla>::Iterador lst) // sin parametros.
{
listaActual = lst; // 1 solo parametro.
}

template <typename A,typename B>
diccHash<A,B>::Iterador::Iterador() // sin parametros.
{
Lista<diccHash<A,B>::tupla> vacia;
typename Lista<diccHash<A,B>::tupla>::Iterador itVacia = vacia.CrearIt();
listaActual = itVacia; // 1 solo parametro.
}
/*

// no deterministico
template <typename A,typename B>
diccHash<A,B>::Iterador::Iterador(diccHash<A,B>& d)//:listaActual(), posicionActual(), arr() ,contador()  // constructor del iterador.
{
this->arr = &(d.tabla);
this->posicionActual = 0;
this->contador = d.cardinal;
Lista<tupla> listaVacia;
this->listaActual= listaVacia.CrearIt();
  while(  (this->posicionActual<this->arr->Tamanho()) && (*arr)[this->posicionActual].EsVacia()   )
  {
  this->posicionActual= this->posicionActual+1;
  }
  if(this->posicionActual<this->arr->Tamanho())
  {
  this->listaActual=  ((*arr)[this->posicionActual]).CrearIt();
  }else
  {
    this->posicionActual=0;
  }
}*/




template <typename A,typename B>
A& diccHash<A,B>::Iterador::SiguienteClave()
{
return (this->listaActual).Siguiente().clave;
}



template <typename A,typename B>
B& diccHash<A,B>::Iterador::SiguienteSignificado()
{
  return (this->listaActual).Siguiente().significado;
}





template <typename A,typename B>
typename diccHash<A,B>::Iterador& diccHash<A,B>::Iterador::operator = (typename diccHash<A,B>::Iterador otro)
{
      listaActual = otro.listaActual; //el campo listaActual del itDiccHash es un iterador modificable de Lista.
     
      return *this;
}



#endif //diccHash_H_
