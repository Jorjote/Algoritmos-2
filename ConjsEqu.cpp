#include "ConjsEqu.h"
// saque ItActualizarElem(Nat n) porque era una auxiliar y me mariaba mucho,lo implemente mas facil y entendible y ya lo testie.
// falta programar dameRelacion()

        template <typename T>
		ConjsEqu<T>::ConjsEqu()
		{
            Lista<dato> Listavacia;
            this->elementos = Listavacia;
		}

        template <typename T>
		ConjsEqu<T>::~ConjsEqu()
		{
		    //dtor
		}

   
        template <typename T>
        typename ConjsEqu<T>::Iterador ConjsEqu<T>::relacionar(Nat n, T elem)// creo que OK.
        {
            //assert(elementos.Primero().id <= n);
            typename ConjsEqu<T>::Iterador it;
            if(this->valoresDefinidos().EsVacio()){
                Conj<T> nuevo;
                nuevo.AgregarRapido(elem);
                dato datoNuevo(nuevo, n);
                this->elementos.AgregarAtras(datoNuevo);
                it =  this->CrearIt();

            }
            else{
                if (elementos.Primero().id == 0) this->elementos.Primero().clase.AgregarRapido(elem);
                else{
                    Conj<T> nuvo;
                    nuvo.AgregarRapido(elem);
                    dato datoNuvo(nuvo, 0);
                    elementos.AgregarAdelante(datoNuvo);

                }
                it =  this->CrearIt();
                while(it.elementoActual() != elem){
                    it.Avanzar();
                }
                it.ItActualizarElem(n);                
            }
        return it;

        }
        template <typename T>
        Conj<T> ConjsEqu<T>::dameConjEquivalencia(Nat n)
        {
            typename Lista<ConjsEqu<T>::dato>::Iterador it = this->elementos.CrearIt();
            while( it.Siguiente().id!=n )
            {
                it.Avanzar();
            }
            return it.Siguiente().clase;
        }

        template <typename T>
        Conj<Nat> ConjsEqu<T>::valoresDefinidos()
        {
            Conj<Nat> res;
            typename Lista<ConjsEqu<T>::dato>::Iterador it = this->elementos.CrearIt();
            while( it.HaySiguiente() )
            {
                res.AgregarRapido(it.Siguiente().id);
                it.Avanzar();
            }
            return res;
        }


        template <typename T>
        void ConjsEqu<T>::eliminar(T elem)
        {
            typename Lista<ConjsEqu::dato>::Iterador it=this->elementos.CrearIt();
            while( it.HaySiguiente() )
            {
                it.Siguiente().clase.Eliminar(elem);
                it.Avanzar();
            }
        }

        template <typename T>
        Conj<T> ConjsEqu<T>::elementosDefinidos()
        {
            Conj<T> res;
            ConjsEqu<T>::Iterador it = this->CrearIt();
            while( it.HaySiguiente() )
            {
                res.AgregarRapido(it.elementoActual());
                it.Avanzar();
            }
            return res;
        }


        template <typename T>
        typename ConjsEqu<T>::Iterador ConjsEqu<T>::CrearIt()
        {
            return Iterador(*this);
        }


        /////// FUNCIONES DEL ITERADOR:

    template <typename T> // OK
    ConjsEqu<T>::Iterador::Iterador(ConjsEqu<T>& e)
    {
     this->itClaseElem = e.elementos.CrearIt(); 
     if( this->itClaseElem.HaySiguiente() ) // solo entra en el caso que el ConjsEqu tenga elementos.sino el campo ItElem queda vacio.
           {
              this->itElem = e.elementos.Primero().clase.CrearIt();
           }
    }



      template <typename T> // OK
    ConjsEqu<T>::Iterador::Iterador()  // CONSTRUCTOR ITERADOR POR DEFECTO.
    {
      Lista<ConjsEqu<T>::dato> listaVacia;
     typename Lista<ConjsEqu<T>::dato>::Iterador itListaVacia = listaVacia.CrearIt();
     this->itClaseElem = itListaVacia;
      Conj<T> conjuntoVacio;
     typename Conj<T>::Iterador itConjVacio = conjuntoVacio.CrearIt();
     this->itElem = itConjVacio;
    }


   
 
    template <typename T>
    typename ConjsEqu<T>::Iterador::tuplaIt ConjsEqu<T>::Iterador::Siguiente() // OK.
    {
        return Iterador::tuplaIt( this->itClaseElem.Siguiente().clase ,this->itElem.Siguiente(), this->itClaseElem.Siguiente().id );
        // < conjunto de eltos (clase) , elementoActual() ,valorActual() >
    }

    template <typename T> //OK.
    T ConjsEqu<T>::Iterador::elementoActual()  // retorna el elemento actual.
    {
        assert(this->itElem.HaySiguiente());
        assert(this->HaySiguiente());
        return this->itElem.Siguiente();
    }

    template <typename T> //OK.
    Conj<T> ConjsEqu<T>::Iterador::claseActual() // retorna el conjunto de los elementos del actual Nat.
    {
        assert(this->HaySiguiente());
        return this->itClaseElem.Siguiente().clase; //OK.
    }

    template <typename T> //OK.
    Nat ConjsEqu<T>::Iterador::valorActual()  // retorna el Nat actual.
    {
        assert(this->HaySiguiente());
        return this->itClaseElem.Siguiente().id;
    }

    template <typename T> // me falta revisar
    ConjsEqu<T> ConjsEqu<T>::Iterador::dameRelacion()
    {
        this->itClaseElem.SecuSubY();
    }

    template <typename T>  //OK
    void ConjsEqu<T>::Iterador::Avanzar()
    {
            assert(HaySiguiente());
            this->itElem.Avanzar(); // quizas, ya no hay otro siguiente.
                  
            if( !itElem.HaySiguiente()){
                this->itClaseElem.Avanzar();// si hay siguiente de itElem, entonces lo hay para itClaseElem.
                if( this->itClaseElem.HaySiguiente() )
                 {
                this->itElem = this->itClaseElem.Siguiente().clase.CrearIt();
                 }
            }        
    }

    
    template <typename T>
    bool ConjsEqu<T>::Iterador::HaySiguiente()   //OK
    {
        return (this->itClaseElem.HaySiguiente() && this->itElem.HaySiguiente());
    }
    
    template <typename T>
    bool ConjsEqu<T>::Iterador::HayAnterior()   //OK
    {
        return (this->itClaseElem.HayAnterior() && this->itElem.HayAnterior());
    }



    template <typename T>
    void ConjsEqu<T>::Iterador::ItActualizarElem(Nat n) // Ok
    {
        assert(this->HaySiguiente() && valorActual() <= n); // sino hay siguiente no puedo actualizar el siguiente.
        if (valorActual() == n) return;

        T elem = this->itElem.Siguiente(); //  Conj<T>::Iterador , siempre que haya siguiente hay siguiente en el campo itElem.
        this->itElem.EliminarSiguiente(); // elimino el elemento siguiente del iterador, para luego meterlo en la clase n.
        if( !this->itElem.HaySiguiente() ) // si no hay elto siguiente en el cjto entonces elimino la clase.
        {
            this->itClaseElem.EliminarSiguiente(); // Lista<dato>::Iterador
        }
        typename Lista<dato>::Iterador itClases = this->itClaseElem;
        while( itClases.HaySiguiente() && itClases.Siguiente().id<n ) // creo que esto "< n" vale porque van creciendo las sansiones.
        {
            itClases.Avanzar();
        }
        typename Conj<T>::Iterador itElemActualizado;
        if( itClases.HaySiguiente() && itClases.Siguiente().id==n )
        {
            itElemActualizado = itClases.Siguiente().clase.AgregarRapido(elem); // meto elem en la clase n.
        }
        else
        {
            Conj<T> conjNuevo; // este conjunto esta vacio.
            ConjsEqu<T>::dato claseNueva(conjNuevo,n);
            itClases.AgregarComoSiguiente(  claseNueva );
            itElemActualizado = itClases.Siguiente().clase.AgregarRapido(elem);
        }
        // actualizo el iterador, sus campos.
        this->itClaseElem = itClases; // el siguiente esta en el elemento que agregue recien.
        this->itElem = itElemActualizado; // el siguiente esta en el elemento que agregue recien.
    }

    template<typename T>
    std::ostream& ConjsEqu<T>::Mostrar(std::ostream& os) {
    os <<"[";
    typename ConjsEqu<T>::Iterador it = CrearIt();
    Nat id1 = it.Siguiente().valor + 1;
    while (it.HaySiguiente()){
        if(id1 == it.Siguiente().valor) it.Avanzar();
        else{
        id1 = it.Siguiente().valor;
        os << "<";
        os<< it.Siguiente().clase;
        os << ", "<< it.Siguiente().valor;
        os << ">";
        it.Avanzar();
        if(it.HaySiguiente()) os << ", ";

        }
    }
os << "]"<< std::endl;
return os;
}