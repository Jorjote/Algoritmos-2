#include <iostream>
#include "campusSeguro.h"
using namespace std;

int main()
{
    campus camp(5,5);

    aed2::Dicc<Agente, Posicion> dick;
    //camp.mostrarCampus(cout);

    aed2::Agente a1(10);
    aed2::Posicion p1(1,1);
    dick.Definir(a1, p1);

    aed2::Agente a2(20);

    aed2::Posicion p2(2,2);
    dick.Definir(a2, p2);

    aed2::Posicion p4(3,3);
    aed2::Agente a4(30);

    aed2::Posicion p5(4,4);
    aed2::Agente a5(40);

    Posicion p7(3,1);
    Agente a7(50);

    dick.Definir(a4, p4);
    dick.Definir(a5, p5);
    dick.Definir(a7, p7);

    campusSeguro hola(camp, dick);

    //hola.mostrarGrilla(cout);

    aed2::Posicion p3(2,1);
    hola.ingresarEstudiante("estudiante1", p3);
    hola.mostrarGrilla(cout);

    Posicion p6(3,2);
    hola.ingresarEstudiante("estudiante2", p6);

    hola.mostrarGrilla(cout);
    Posicion p8(4,2);
    hola.ingresarHippie("hippie1", p8);
    //hola.ingresarEstudiante("estudiante3", p8);
    hola.mostrarGrilla(cout);

    //Conj<Agente> prueba = hola.conMismasSanciones(a4);
    //Conj<Agente>::const_Iterador itM = prueba.CrearIt();

    //while(itM.HaySiguiente())
    //{
        //Agente a = itM.Siguiente();
        //cout << a << endl;
        //itM.Avanzar();
    //}

    cout << "el mas vigilante " << hola.masVigilante() << endl;
    cout << "Las sanciones de los agentes :" << endl;

    Conj<Agente>::Iterador itA = hola.agentes();

    while (itA.HaySiguiente())
    {
        Posicion P = hola.posAgente(itA.Siguiente());
        P.mostrar(cout);
        cout << hola.cantSanciones(itA.Siguiente()) << endl;
        itA.Avanzar();
    }

        // HAY QUE MIRAR LAS SANCIONES A VER QUE ONDIS.
    return 0;
}
