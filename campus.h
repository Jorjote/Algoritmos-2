#ifndef CAMPUS_H
#define CAMPUS_H
#include "Modulos Basicos/aed2.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include "assert.h"
#include <cassert>
#include "Tipos.h"

typedef unsigned int Nat;
//enum Direccion{arriba,abajo,izq,der};// fuera de la clase, ya que se usa desde afuera en otros modulos.(no es propio de campus,sino externo)
class campus
{
    public:
        campus(Nat an , Nat al);
        campus(); // constructor por defecto de campus.
        //~campus();
        void AgregarObstaculo(Posicion p);
        Nat Filas();
        Nat Columnas();
        bool Posocupada(Posicion p);
        bool Valida(Posicion p);
        bool EsIngreso(Posicion p);
        bool IngresoInferior(Posicion p);
        bool IngresoSuperior(Posicion p);
        Conj<Posicion> Vecinos(Posicion p);
        Nat Distancia(Posicion p1,Posicion p2);
        Posicion ProximaPos(Posicion p, Direccion dir);
        Conj<Posicion> IngresosCercanos(Posicion p);
        std::ostream& mostrarCampus(std::ostream& os);

    private:

        Nat Ancho;
        Nat Alto;
        Conj<Posicion> Obstaculos;
 };
#endif // CAMPUS_H
