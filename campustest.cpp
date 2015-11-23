#include "campus.cpp"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
using namespace std;


int main() {
	int ancho=2;
	int alto=3;
campus nuevoCampus(ancho,alto);
campus::Posicion pos1(0,0);
campus::Posicion pos2(0,1);
campus::Posicion pos3(1,1);
cout << "agregue obstaculo en la posicioon (0,0)" << endl;
nuevoCampus.AgregarObstaculo(pos1);
cout << "agregue obstaculo en la posicioon (0,1)" << endl;
nuevoCampus.AgregarObstaculo(pos2);
cout << "agregue obstaculo en la posicioon (1,1)" << endl;
nuevoCampus.AgregarObstaculo(pos3);

campus::Posicion p1(0,0);
campus::Posicion p2(0,1);
campus::Posicion p3(0,2);
campus::Posicion p4(1,0);
campus::Posicion p5(1,1);
campus::Posicion p6(1,2);


campus::Posicion p7(2,0);
campus::Posicion p8(3,0);
campus::Posicion p9(4,1);
campus::Posicion p10(0,3);
campus::Posicion p11(1,3);
campus::Posicion p12(2,1);
campus::Posicion p13(2,0);
campus::Posicion p14(4,5);
campus::Posicion p15(6,7);


cout << " hay obstaculo en la posicion (0,0)? : " << nuevoCampus.Posocupada(p1) << endl;
cout << " hay obstaculo en la posicion (0,1)? : " << nuevoCampus.Posocupada(p2) << endl;
cout << " hay obstaculo en la posicion (0,2)? : " << nuevoCampus.Posocupada(p3) << endl;
cout << " hay obstaculo en la posicion (1,0)? : " << nuevoCampus.Posocupada(p4) << endl;
cout << " hay obstaculo en la posicion (1,1)? : " << nuevoCampus.Posocupada(p5) << endl;
cout << " hay obstaculo en la posicion (1,2)? : " << nuevoCampus.Posocupada(p6) << endl;


cout << "Posiciones validas:" << endl;
cout << "  (0,0)? : " <<  nuevoCampus.Valida(p1) << endl;
cout << " (0,1)? : "  <<  nuevoCampus.Valida(p2) << endl;
cout << "  (0,2)? : " <<  nuevoCampus.Valida(p3) << endl;
cout << " (1,0)? : " <<  nuevoCampus.Valida(p4) << endl;
cout << "  (1,1)? : "  <<  nuevoCampus.Valida(p5) << endl;
cout << " (1,2)? : " <<  nuevoCampus.Valida(p6) << endl;
cout << "otras posiciones que no son validas: " << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p7) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p8) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p9) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p10) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p11) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p12) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p13) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p14) << endl;
cout << "  unknow? : " << nuevoCampus.Valida(p15) << endl;


/// TEST DE DISTANCIA:
campus::Posicion pt1(0,0);
campus::Posicion pt2(0,1);
campus::Posicion pt3(0,2);
campus::Posicion pt4(1,2);
cout << "La distancia entre (0,1) y (0,0) es : "<< nuevoCampus.Distancia(pt2,pt1) << endl;
cout << "La distancia entre (0,0) y (0,2) es : "<< nuevoCampus.Distancia(pt1,pt3) << endl;
cout << "La distancia entre (0,0) y (1,2) es : "<< nuevoCampus.Distancia(pt1,pt4) << endl;



/// TEST DE VECINOS:
campus::Posicion puntito(0,0);
Conj<campus::Posicion>  vecinos = nuevoCampus.Vecinos(puntito);
Conj<campus::Posicion>::Iterador itConjVecinos = vecinos.CrearIt();
cout <<"Vecinos de (0,0)"<<endl;
	while(itConjVecinos.HaySiguiente())
	{
	  cout << " ("<<itConjVecinos.Siguiente().X() <<" , "<< itConjVecinos.Siguiente().Y()<<")"<<endl;	
	  itConjVecinos.Avanzar();
	}

// test de proxima posicion
	cout << endl << "plano del campus: " << endl;
	cout<<"(0,0)(1,0)"<<endl;
	cout<<"(0,1)(1,1)"<<endl;
	cout<<"(0,2)(1,2)"<<endl;
	campus::Posicion posInicial(0,1);
	cout << "posicion actual: (0,1) y me movere arriba"<< endl;
	Direccion dir = arriba;
	cout << "siguiente Posicion: (" << nuevoCampus.ProximaPos(posInicial,dir).X()<<","<<nuevoCampus.ProximaPos(posInicial,dir).Y() << ")"<<endl;
    posInicial=nuevoCampus.ProximaPos(posInicial,dir);
    dir= der;
    cout << "me muevo derecha: "<<endl;
    cout << " (" << nuevoCampus.ProximaPos(posInicial,dir).X()<<","<<nuevoCampus.ProximaPos(posInicial,dir).Y() << ")"<<endl;
     //
     posInicial=nuevoCampus.ProximaPos(posInicial,dir);
     dir= abajo;
     cout << "me muevo abajo: "<<endl;
     cout << " (" << nuevoCampus.ProximaPos(posInicial,dir).X()<<","<<nuevoCampus.ProximaPos(posInicial,dir).Y() << ")"<<endl;
     //
     posInicial=nuevoCampus.ProximaPos(posInicial,dir);
     dir= izq;
     cout << "me muevo izquierda: "<<endl;
     cout << " (" << nuevoCampus.ProximaPos(posInicial,dir).X()<<","<<nuevoCampus.ProximaPos(posInicial,dir).Y() << ")"<<endl;
      //
     posInicial=nuevoCampus.ProximaPos(posInicial,dir);
     dir= arriba;
     cout << "me muevo arriba: "<<endl;
     cout << " (" << nuevoCampus.ProximaPos(posInicial,dir).X()<<","<<nuevoCampus.ProximaPos(posInicial,dir).Y() << ")"<<endl;


///////////////test ingresos cercanos:
     campus::Posicion posActual(0,1);
     Conj<campus::Posicion> ingreCerc = nuevoCampus.IngresosCercanos(posActual);
     cout << "cuales son los ingresos mas cercanos a (0,1)?: " << endl;
    Conj<campus::Posicion>::Iterador itConjIngresos = ingreCerc.CrearIt();
	while(itConjIngresos.HaySiguiente())
	{
	  cout << " ("<<itConjIngresos.Siguiente().X() <<" , "<< itConjIngresos.Siguiente().Y()<<")"<<endl;	
	  itConjIngresos.Avanzar();
	}


 campus::Posicion posActual2(1,1);
	     Conj<campus::Posicion> ingreCerc2 = nuevoCampus.IngresosCercanos(posActual2);
     cout << "cuales son los ingresos mas cercanos a (1,1)?: " << endl;
    Conj<campus::Posicion>::Iterador itConjIngresos2 = ingreCerc2.CrearIt();
	while(itConjIngresos2.HaySiguiente())
	{
	  cout << " ("<<itConjIngresos2.Siguiente().X() <<" , "<< itConjIngresos2.Siguiente().Y()<<")"<<endl;	
	  itConjIngresos2.Avanzar();
	}


 campus::Posicion posActual3(0,0);
	     Conj<campus::Posicion> ingreCerc3 = nuevoCampus.IngresosCercanos(posActual3);
     cout << "cuales son los ingresos mas cercanos a (0,0)?: " << endl;
    Conj<campus::Posicion>::Iterador itConjIngresos3 = ingreCerc3.CrearIt();
	while(itConjIngresos3.HaySiguiente())
	{
	  cout << " ("<<itConjIngresos3.Siguiente().X() <<" , "<< itConjIngresos3.Siguiente().Y()<<")"<<endl;	
	  itConjIngresos3.Avanzar();
	}




 campus::Posicion posActual4(1,2);
	     Conj<campus::Posicion> ingreCerc4 = nuevoCampus.IngresosCercanos(posActual4);
     cout << "cuales son los ingresos mas cercanos a (1,2)?: " << endl;
    Conj<campus::Posicion>::Iterador itConjIngresos4 = ingreCerc4.CrearIt();
	while(itConjIngresos4.HaySiguiente())
	{
	  cout << " ("<<itConjIngresos4.Siguiente().X() <<" , "<< itConjIngresos4.Siguiente().Y()<<")"<<endl;	
	  itConjIngresos4.Avanzar();
	}


//// test stream
cout << endl << endl;
nuevoCampus.mostrarCampus(cout);

return 0;
}