#include "trie.h"

using namespace aed2;
template <class T>
DiccPalabra<T>::DiccPalabra() //constructor por defecto
{
    Lista<DatosTrie> l;
    estrTrie = l;
    Lista<String> c;
    claves = c;
    noLleno = true;
}

template <class T>
DiccPalabra<T>::~DiccPalabra()   //destructor
{

}

template <class T>
DiccPalabra<T>::DiccPalabra(const DiccPalabra& otro) //constructor por copia
    :estrTrie(otro.estrTrie), claves(otro.claves), significados(otro.significados), noLleno(otro.noLleno)//uso lista de inicializacion.
{
}

template <class T>
DiccPalabra<T>& DiccPalabra<T>::operator=(const DiccPalabra<T>& otro)
{
    if(this != &otro)
    {
        estrTrie = otro.estrTrie;
        claves = otro.claves;
        significados = otro.significados;
        noLleno = otro.noLleno;
    }
    return *this;
}

template <class T>
bool DiccPalabra<T>::vacio()
{
    return noLleno;
}

template <class T>
void DiccPalabra<T>::Definir(String s, const T& elem)
{
    String l = s;
     if (s.size() > 0)  // si el tamaño es mayor a cero...
    {
        typename Lista<DatosTrie>::Iterador itl = estrTrie.CrearIt(); // me creo un iterador a mi estructura(lista)
        Nat i = 0;

        if (!itl.HaySiguiente())    // si no hay siguiente, es decir si es vacio mi Trie.
        {
             Lista<DatosTrie> l;     // l = vacia()  lo voy a usar para los hijos de este nodo
            DatosTrie tmp;          // me creo un nodo
            tmp.clave = s[i];
            tmp.hijos = l;
            tmp.valido = false;     // le pongo false a la primer char que agrego
            itl.AgregarComoSiguiente(tmp);      // agrego el nodo a mi estructura
        }

        while(itl.HaySiguiente() && i < s.size() - 1)   // mientras haya mas nodos para recorrer y no haya llegado al final del string que quiero agregar...
        {
            if(itl.Siguiente().clave == s[i]) // si donde estoy parado es igual al char actual que estoy mirando...
            {
                i++;                            // avanzo uno en s, por que ya lo encontre en el trie
                itl = itl.Siguiente().hijos.CrearIt();  // sigo buscando en los hijos de ese char.
            }
            else
            {
                itl.Avanzar();      // avanzo porque no era ese el char que buscaba
            }

            if (!itl.HaySiguiente()) // si llegue al final y no encontre nada, es decir la palabra que quiero agregar es un poco mas larga, ejemplo, tengo camio y quiero agregar camioneta.
            { // me creo el nodo que necesito
                 Lista<DatosTrie> l;     // l = vacia()
                DatosTrie tmp;
                tmp.clave = s[i];
                tmp.hijos = l;
                tmp.valido = false;
                itl.AgregarComoSiguiente(tmp);  //
            }
        }

        while(itl.HaySiguiente() && (itl.Siguiente().clave != s[s.size() - 1])) // mientras haya siguiente y no haya llegado a la ultima clave del s
        {
            itl.Avanzar();
        }

        if (!itl.HaySiguiente()) // cuando llego al final agrego el ultimo char que me falta y pongo su campo valido en true.
        {
            Lista<DatosTrie> l;     // l = vacia()
            DatosTrie tmp;
            tmp.clave = s[s.size() - 1];
            tmp.hijos = l;
            tmp.valido = false;
            itl.AgregarComoSiguiente(tmp);
        }

        itl.Siguiente().valido = true;
        itl.Siguiente().dato = elem;
        noLleno = false;
        itl.Siguiente().itClave = claves.AgregarAtras(l);
        itl.Siguiente().itSignificado = significados.AgregarAtras(elem);
    }
}

template <class T>
T& DiccPalabra<T>::Obtener(String s)
{
    assert(Definido(s));
    typename Lista<DatosTrie>::Iterador itl = estrTrie.CrearIt();
    Nat i = 0;
    while(i < s.size()-1 && itl.HaySiguiente())
    {
        if((itl.Siguiente()).clave == s[i])
        {
            i++;
            itl = (itl.Siguiente()).hijos.CrearIt();
        }
        else
        {
            itl.Avanzar();
        }
    }
    while(itl.HaySiguiente() && (itl.Siguiente().clave != s[i]))
    {
        itl.Avanzar();
    }

    return (itl.Siguiente()).dato;
}

template <class T>
const T& DiccPalabra<T>::Obtener(const String s) const
{
    assert(Definido(s));
    typename Lista<DatosTrie>::const_Iterador itl = estrTrie.CrearIt();
    Nat i = 0;
    while(i < s.size()-1 && itl.HaySiguiente())
    {
        if((itl.Siguiente()).clave == s[i])
        {
            i++;
            itl = (itl.Siguiente()).hijos.CrearIt();
        }
        else
        {
            itl.Avanzar();
        }
    }
    while(itl.HaySiguiente() && (itl.Siguiente().clave != s[i]))
    {
        itl.Avanzar();
    }

    return (itl.Siguiente()).dato;
}

template <class T>
bool DiccPalabra<T>::Definido(String s) const
{
    if(noLleno){return false;}
    bool res = false;
    if (s.size() > 0)
    {
        typename Lista<DatosTrie>::const_Iterador itl = estrTrie.CrearIt();
        Nat i = 0;
        while(itl.HaySiguiente() && i < s.size() - 1)
        {
            if(itl.Siguiente().clave == s[i])
            {
                i++;
                itl = itl.Siguiente().hijos.CrearIt();
            }
            else
            {
                itl.Avanzar();
            }
        }

        while(itl.HaySiguiente() && (itl.Siguiente().clave != s[s.size() - 1]))
        {
            itl.Avanzar();
        }
        res = ((i == s.size() - 1) && itl.HaySiguiente() && itl.Siguiente().valido);
    }
    return res;
}

template <class T>
void DiccPalabra<T>::Borrar(String s)
{
    assert(Definido(s));
    bool res = false;
    if (s.size() > 0)
    {
        typename Lista<DatosTrie>::Iterador itl = estrTrie.CrearIt();
        Nat i = 0;
        while(itl.HaySiguiente() && i < s.size() - 1)
        {
            if(itl.Siguiente().clave == s[i])
            {
                i++;
                itl = itl.Siguiente().hijos.CrearIt();
            }
            else
            {
                itl.Avanzar();
            }
        }

        while(itl.HaySiguiente() && (itl.Siguiente().clave != s[s.size() - 1]))
        {
            itl.Avanzar();
        }
        res = ((i == s.size() - 1) && itl.HaySiguiente() && itl.Siguiente().valido);

        if (res)
        {
            itl.Siguiente().valido = false;
            itl.Siguiente().itClave.EliminarSiguiente();
            itl.Siguiente().itSignificado.EliminarSiguiente();
            // eliminar el siguiente con el iterador de las claves.
            // eliminar el siguiente con el iterador de significados.
        }
    }

}
/*
template <class T>
 const Lista<String>& DiccPalabra<T>::Claves() const
{
    return claves;
}
*/
template <class T>
int DiccPalabra<T>::cantClaves() const
{
    return claves.Longitud();
}
template <class T>
typename DiccPalabra<T>::itDiccP DiccPalabra<T>::CrearIt() const
{
    return itDiccP(this);
}

template <class T>
typename DiccPalabra<T>::itDiccP DiccPalabra<T>::Significados()
{
    return CrearIt();
}

template <class T>
typename DiccPalabra<T>::itDiccP DiccPalabra<T>::Claves()
{

    return CrearIt();
}

/*********************************************************************************
***********************FUNCIONES DEL ITERADOR*************************************
**********************************************************************************/


template <class T>
DiccPalabra<T>::itDiccP::itDiccP()
//: it_claves_(NULL), it_significados_(NULL)
{

}

template <class T>
DiccPalabra<T>::itDiccP::itDiccP(const DiccPalabra<T>* d)
{
    it_claves_ = d->claves.CrearIt();
    it_significados_ =  d->significados.CrearIt();
}

template <class T>
DiccPalabra<T>::itDiccP::itDiccP(const typename DiccPalabra<T>::itDiccP& otro)
: it_claves_(otro.it_claves_), it_significados_(otro.it_significados_)
{}

template <class T>
bool DiccPalabra<T>::itDiccP::HaySiguiente() const
{
    return it_claves_.HaySiguiente() && it_significados_.HaySiguiente();
}

template <class T>
const T& DiccPalabra<T>::itDiccP::SiguienteSignificado() const
{
    return it_significados_.Siguiente();
}

template <class T>
const String DiccPalabra<T>::itDiccP::SiguienteClave() const
{
    return it_claves_.Siguiente();
}

template <class T>
void DiccPalabra<T>::itDiccP::Avanzar()
{
    it_claves_.Avanzar();
    it_significados_.Avanzar();
}
