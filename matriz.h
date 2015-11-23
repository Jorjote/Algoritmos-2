#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED
#include "Modulos Basicos/aed2.h"
#include "assert.h"
#include "tipos.h"
#include <iostream>
#include <fstream>
#include <ostream>
using namespace aed2;

template <typename T>
class diccMatriz{
    public:
        diccMatriz();      //Constructor por defectou
        diccMatriz(Nat n , Nat m , T value);      //Crear()
        ~diccMatriz();
        void Definir(Posicion P, const T& elem);   //Definir(M,i,j)
        bool enRango(Posicion P) const;             //enRango(i,j,M)
        bool enRango(Nat c, Nat f) const;             //enRango(i,j,M)
        Nat Filas() const;                        //filas  (M)
        Nat Columnas() const;                        //columnas(M)
        T& Obtener(Posicion P);	//M[i][j]
        T& Obtener(Nat c, Nat f);	//M[i][j]
        diccMatriz<T>& operator=(const diccMatriz<T>&);
        // void mostrarMatriz(std::ostream&) const; // imprime la matriz

    private:

        Arreglo<Arreglo<T> > Matriz;
        Nat filas;
        Nat cols;

};







#endif // MATRIZ_H_INCLUDED
