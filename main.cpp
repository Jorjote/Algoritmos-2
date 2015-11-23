#include <iostream>
#include "Driver.h"
using namespace std;

int main()
{
    Driver d;
    d.crearCampus(5,5);
    Posicion p(1,2);
    d.agregarObstaculo(p);
    aed2::Dicc<Agente, Posicion> dick;
    aed2::Agente a1;
    aed2::Agente a2;
    aed2::Agente a3;
    Posicion p1(0,0);
    Posicion p2(1,0);
    Posicion p3(0,1);
    dick.Definir(a1,p1);
    dick.Definir(a2,p2);
    dick.Definir(a3,p3);
    d.comenzarRastrillaje(dick);
    Posicion pe1(0,2);
    Posicion pe2(0,3);
    d.ingresarEstudiante("pepe", pe1);
    d.ingresarEstudiante("jose", pe2);

    Posicion ph1(0,4);
    d.ingresarHippie("hippie1", ph1);
    cout << "Hello world!" << endl;
    cout << d.filas() << endl;
    cout << "cantidad estudiantes = " << d.cantEstudiantes() << endl;
    cout << "cantidad Hippies = " << d.cantHippies() << endl;
    cout << "cantidad agentes = " << d.cantAgentes() << endl;
    cout << "posicion del hippie = " << "(" <<d.posEstudianteYHippie("hippie1").x << "," << d.posEstudianteYHippie("hippie1").y << ")" <<endl;
    // REVISAR POS AGENTE QUE TIRA CUALQUIERA M4N
    cout << "posicion del agente = " << "(" <<d.posAgente(a2).x << "," << d.posAgente(a2).y << ")" <<endl;
    cout << "cantidad de sanciones = " << d.cantSanciones(a1) << endl;
    cout << "Mas Vigilante " << d.masVigilante() << endl;
    cout << "iesimo HIppie (0) = " << d.iesimoHippie(0) << endl;
    return 0;
}
