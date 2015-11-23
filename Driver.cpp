#include "Driver.h"

namespace aed2 {

Driver::Driver()
{
    // TODO
    campo = NULL;
    camposeguro = NULL;
	//assert(false);
}

Driver::~Driver()
{
    // TODO
    delete campo;
    delete camposeguro;
	//assert(false);
}


/// Generadores del Campus

void Driver::crearCampus(Nat ancho, Nat alto)
{
    // TODO
    campus* iniciar = new campus(ancho, alto);
    campo = iniciar;
	//assert(false);
}

void Driver::agregarObstaculo(Posicion p)
{
    // TODO
    campo->AgregarObstaculo(p);
	//assert(false);
}


/// Observadores del Campus

Nat Driver::filas() const
{
    // TODO
    return campo->Filas();
	//assert(false);
}

Nat Driver::columnas() const
{
    // TODO
    //return campo.Columnas();
	assert(false);
}

bool Driver::ocupada(Posicion p) const
{
    // TODO
    return campo->Posocupada(p);
	//assert(false);
}


/// Generadores de CampusSeguro
void  Driver::comenzarRastrillaje(const Dicc<Agente,Posicion>& d) {
    // TODO
    campusSeguro* iniciar = new campusSeguro(*campo, d);
    camposeguro = iniciar;
    cantidadAgentes = d.CantClaves();
	//assert(false);
}

void Driver::ingresarEstudiante(Nombre n, Posicion p)
{
    // TODO
    camposeguro->ingresarEstudiante(n, p);
	//assert(false);
}

void Driver::ingresarHippie(Nombre n, Posicion p)
{
    // TODO
    camposeguro->ingresarHippie(n, p);
	//assert(false);
}

void Driver::moverEstudiante(Nombre n, Direccion d)
{
    // TODO
    camposeguro->moverEstudiante(n, d);
	//assert(false);
}

void Driver::moverHippie(Nombre n)
{
    // TODO
    camposeguro->moverHippie(n);
	//assert(false);
}

void Driver::moverAgente(Agente pl)
{
    // TODO
    camposeguro->moverAgente(pl);
	//assert(false);
}


/// Observadores de CampusSeguro

Nombre Driver::iesimoEstudiante(Nat i) const
{
    assert(i < camposeguro->cantEstudiantes());
    Nombre res = "";
    DiccPalabra<Posicion>::itDiccP itH = camposeguro->estudiantes();
    Nat j = 0;
    while (itH.HaySiguiente())
    {
        if (j == i)
        {
            res = itH.SiguienteClave();
        }
        j++;
        itH.Avanzar();
    }

    return res;
}

Nombre Driver::iesimoHippie(Nat i) const
{
    assert(i < camposeguro->cantHippies());
    Nombre res = "";
    DiccPalabra<Posicion>::itDiccP itH = camposeguro->Hippies();
    Nat j = 0;
    while (itH.HaySiguiente())
    {
        if (j == i)
        {
            res = itH.SiguienteClave();
        }
        j++;
        itH.Avanzar();
    }

    return res;
}

Nat Driver::iesimoAgente(Nat i) const
{
    assert(i < camposeguro->cantEstudiantes());

    Nat res = 0;
    Conj<Agente>::Iterador itA = camposeguro->agentes();
    Nat j = 0;
    while (itA.HaySiguiente())
    {
        if (j == i)
        {
            res = itA.Siguiente();
        }
        j++;
        itA.Avanzar();
    }

    return res;
}

Nat Driver::cantEstudiantes() const {
    // TODO
    return camposeguro->cantEstudiantes();
	//assert(false);

}

Nat Driver::cantHippies() const
{    // TODO
    return camposeguro->cantHippies();
	//assert(false);
}

Nat Driver::cantAgentes() const
{
    // TODO
    return cantidadAgentes;
	assert(false);
}

Posicion Driver::posEstudianteYHippie(Nombre n) const
{
    // TODO
    return camposeguro->posEstudianteYHippie(n);
	assert(false);
}

Posicion Driver::posAgente(Agente pl) const
{
    // TODO
    return camposeguro->posAgente(pl);
	//assert(false);
}

Nat Driver::cantSanciones(Agente pl) const
{
    // TODO
    return camposeguro->cantSansiones(pl);
	//assert(false);
}

Nat Driver::cantHippiesAtrapados(Agente pl) const
{
    // TODO
    return camposeguro->cantHippiesAtrapados(pl);
	//assert(false);
}


/// Otras operaciones de CampusSeguro

Agente Driver::masVigilante() const
{
    // TODO
    return camposeguro->masVigilante();
	//assert(false);
}

const Conj<Agente> Driver::conMismasSanciones(Agente a) const
{
    // TODO
    return camposeguro->conMismasSansiones(a);
	//assert(false);
}

const Conj<Agente> Driver::conKSanciones(Nat k)
{
    // TODO
    return camposeguro->conKSansiones(k);
	//assert(false);
}


} // namespace aed2

