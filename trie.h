#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

//#include "Modulos Basicos\aed2.h"
#include "Modulos Basicos/aed2.h"
using namespace aed2;

template <typename T>
class DiccPalabra {
    public:

        class itDiccP;

        DiccPalabra();         // Crear()->trie
        ~DiccPalabra();        // Destructor
        DiccPalabra(const DiccPalabra& otro);  // constructor por copia
        DiccPalabra& operator=(const DiccPalabra& otro);   // operador de igualacion

        T& Obtener(String s)  ; // Obtiene del string S, el dato asociado
        bool vacio(); // dice si está vacio el diccionario
        const T& Obtener(const String s) const; // el const
        void Definir(String s, const T& elem); // Define una nueva clave en el Trie
        bool Definido(String s) const;    //
        void Borrar(String s);
        int cantClaves() const;

        itDiccP CrearIt() const;
        itDiccP Significados();
        itDiccP Claves();

        class itDiccP
        {
            public:
                itDiccP();
                itDiccP(const DiccPalabra<T>::itDiccP& otro);
                itDiccP& operator = (const typename DiccPalabra<T>::itDiccP& otro);
                bool HaySiguiente() const;
                const T& SiguienteSignificado() const;
                const String SiguienteClave() const;
                void Avanzar();

            private:
                Lista<String>::const_Iterador it_claves_;
                typename Lista<T>::const_Iterador it_significados_;

                itDiccP(const DiccPalabra<T>* d);
                friend typename DiccPalabra<T>::itDiccP DiccPalabra<T>::CrearIt() const;
                //friend typename DiccPalabra<T>::itDiccP DiccPalabra<T>::Significados(const DiccPalabra& d);
                //friend typename DiccPalabra<T>::itDiccP DiccPalabra<T>::Claves(const DiccPalabra& d);
        };

    private:

        struct DatosTrie{
            char clave;
            Lista<DatosTrie> hijos;
            bool valido;
            T dato;
            Lista<String>::Iterador itClave;
            typename Lista<T>::Iterador itSignificado;
        };

        Lista<DatosTrie> estrTrie;
        Lista<String> claves;
        Lista<T> significados;
        bool noLleno;
};

//#include "trie.cpp"

#endif // TRIE_H_INCLUDED
