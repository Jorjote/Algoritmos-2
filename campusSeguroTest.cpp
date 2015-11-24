#include <iostream>
#include "campusSeguro.h"
#include "mini_test.h"
using namespace std;


void test_Ingresos()
{
    campus camp(5,5);

    aed2::Dicc<Agente, Posicion> dick;
    //camp.mostrarCampus(cout);
    Posicion p0(1,3);
    camp.AgregarObstaculo(p0);
    if (camp.Posocupada(p0))camp.mostrarCampus(cout);

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

    //

    aed2::Posicion p3(2,1);
    hola.ingresarHippie("hippie1", p3);
    //hola.mostrarGrilla(cout);
    //hola.ingresarEstudiante("estudiante1", p3);

    hola.mostrarGrilla(cout);

    Posicion p6(3,2);
    //hola.ingresarHippie("hippie2", p6);
    hola.ingresarEstudiante("estudiante2", p6);

    hola.mostrarGrilla(cout);
    Posicion p8(4,2);
    //hola.ingresarHippie("hippie1", p8);
    hola.ingresarEstudiante("estudiante3", p8);
    hola.mostrarGrilla(cout);
    cout << "el mas vigilante " << hola.masVigilante() << endl;
    cout << "Las sanciones de los agentes :" << endl;

    Conj<Agente>::Iterador itA = hola.agentes();

    while (itA.HaySiguiente())
    {
        Posicion P = hola.posAgente(itA.Siguiente());
        P.mostrar(cout);
        cout << hola.cantSanciones(itA.Siguiente()) << endl;
        cout << hola.cantHippiesAtrapados(itA.Siguiente()) << endl;
        itA.Avanzar();
    }


    Posicion p10(1,2);
    cout << "ingreso el estudiante a la pos " << p10.X() << "," << p10.Y() << endl;
    hola.ingresarEstudiante("estudiantes4", p10);
    hola.mostrarGrilla(cout);

    cout << "el mas vigilante " << hola.masVigilante() << endl;
    cout << "Las sanciones de los agentes :" << endl;

    itA = hola.agentes();

    while (itA.HaySiguiente())
    {
        Posicion P = hola.posAgente(itA.Siguiente());
        P.mostrar(cout);
        cout << hola.cantSanciones(itA.Siguiente()) << endl;
        cout << hola.cantHippiesAtrapados(itA.Siguiente()) << endl;
        itA.Avanzar();
    }

    cout << "ingreso el estudiante a la pos " << p3.X() << "," << p3.Y() << endl;
    hola.ingresarEstudiante("estudiantes5", p3);
    hola.mostrarGrilla(cout);

    cout << "el mas vigilante " << hola.masVigilante() << endl;
    cout << "Las sanciones de los agentes :" << endl;

    itA = hola.agentes();

    while (itA.HaySiguiente())
    {
        Posicion P = hola.posAgente(itA.Siguiente());
        P.mostrar(cout);
        cout << hola.cantSanciones(itA.Siguiente()) << endl;
        cout << hola.cantHippiesAtrapados(itA.Siguiente()) << endl;
        itA.Avanzar();
    }

        // HAY QUE MIRAR LAS SANCIONES A VER QUE ONDIS.

}

void test_Ingresos_HippiesYEstudiantes()
{

    campus camp(5,5);
    Dicc<Agente, Posicion> dick;
    Posicion p0(1,3);
    camp.AgregarObstaculo(p0);
    Agente a1(10);
    Posicion p1(5,5);
    dick.Definir(a1, p1);
    campusSeguro hola(camp, dick);

    Posicion p2(1,1);
    Posicion p3(2,1);

    hola.ingresarHippie("hippie1", p2);
    hola.ingresarHippie("hippie2", p3);
    hola.mostrarGrilla(cout);
    Posicion p4(1,2);
    hola.ingresarEstudiante("estudiante1", p4);
    hola.mostrarGrilla(cout);

    cout << "cantidad de hippies = " << hola.cantHippies() << endl;
    cout << "cantidad de estudiantes = " << hola.cantEstudiantes() << endl;

    Posicion p5(2,3);
    Posicion p6(3,4);
    Posicion p7(1,4);
    Posicion p8(2,5);
    Posicion p9(3,1);
    Posicion p10(2,1);
    hola.ingresarEstudiante("estudiante2", p9);

    hola.moverEstudiante("estudiante2", abajo);
    hola.mostrarGrilla(cout);
    hola.ingresarHippie("hippie3", p9);
    hola.mostrarGrilla(cout);
    cout << "cantidad de hippies = " << hola.cantHippies() << endl;
    cout << "cantidad de estudiantes = " << hola.cantEstudiantes() << endl;
    hola.moverHippie("hippie2");
    hola.mostrarGrilla(cout);

    DiccPalabra<Posicion>::itDiccP itH = hola.Hippies();
    while(itH.HaySiguiente())
    {
        Posicion p = itH.SiguienteSignificado();
        cout << "estos son las posiciones de los hippies " << p.X() << "," << p.Y()  << endl;
        itH.Avanzar();
    }

    DiccPalabra<Posicion>::itDiccP itE = hola.estudiantes();
    while(itE.HaySiguiente())
    {
        Posicion p = itE.SiguienteSignificado();
        cout << "estos son las posiciones de los estudiantes " << p.X() << "," << p.Y()  << endl;
        itE.Avanzar();
    }
    cout << "cantidad de hippies = " << hola.cantHippies() << endl;
    cout << "cantidad de estudiantes = " << hola.cantEstudiantes() << endl;

}

void test_MovimientoAgentes()
{
    campus camp(5,5);
    Dicc<Agente, Posicion> dick;
    Posicion p0(1,3);
    camp.AgregarObstaculo(p0);
    Agente a1(10);
    Posicion p1(5,5);
    dick.Definir(a1, p1);
    campusSeguro hola(camp, dick);
}

int main()
{
    test_Ingresos();
    test_Ingresos_HippiesYEstudiantes();
    test_MovimientoAgentes();
        // HAY QUE MIRAR LAS SANCIONES A VER QUE ONDIS.
    return 0;

}
