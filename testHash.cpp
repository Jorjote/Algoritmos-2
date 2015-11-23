#include "diccHash.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
using namespace std;


int main() {

//defino el diccHash con capacidad para 10 claves.
diccHash<Nat,String> dicc1(10);


// defino 3 claves
Nat clave1=7;
Nat clave2=8;
Nat clave3=9;

// defino 3 significados Strings
String significado1 = "axel";
String significado2 = "es";
String significado3 = "capo";


// defino y testeo las operaciones Definir y Obtener.
cout << "se definio (clave1:7, significado:'axel')" << endl;
dicc1.Definir(clave1,significado1);
cout << "significado asociado a la clave1:" << dicc1.Obtener(clave1) << endl;

cout << "se definio (clave2:8, significado:'es')" << endl;
dicc1.Definir(clave2,significado2);
cout << "significado asociado a la clave2:" << dicc1.Obtener(clave2) << endl;

cout << "se definio (clave3:9, significado:'capo')" << endl;
dicc1.Definir(clave3,significado3);
cout << "significado asociado a la clave3:" << dicc1.Obtener(clave3) << endl;



// Test de iterador
cout << endl<<endl<<endl<<endl<<"se creo iterador desde la primer clave en el hash:"<< endl;
diccHash<Nat,String>::Iterador it3 = dicc1.CrearIt();
while(it3.HaySiguiente())
{
cout << "siguiente clave devuelto por el itHash: " << it3.SiguienteClave() << endl;
cout << "siguiente significado devuelto por el itHash: " << it3.SiguienteSignificado() << endl;
it3.Avanzar();
cout << "se avanzo el itDiccHash" << endl;
}



cout << endl<<endl<<endl<<endl<<"se creo OTRO iterador desde la clave2 en el hash:"<< endl;
diccHash<Nat,String>::Iterador it4 = dicc1.CrearIt(clave2);
while(it4.HaySiguiente())
{
cout << it4.SiguienteSignificado() << endl;
it4.Avanzar();
}


/////////////////////// vacio:
cout << endl << "se creo iterador de un diccionario vacio y luego se muestran los elementos : " <<endl;
diccHash<Nat,Nat> dicc2(2);
diccHash<Nat,Nat>::Iterador itVacio = dicc2.CrearIt();
cout << "hay siguiente?: " << itVacio.HaySiguiente() << endl;
while(itVacio.HaySiguiente())
{
cout << itVacio.SiguienteSignificado() << endl << endl;
itVacio.Avanzar();
}


////// ver si el definir retorna el iterador y en siguiente esta el recien agregado.
Nat clave4=99;
String significado4 = "OH SI";
cout << "Se agrego OH SI en clave 4: "<< dicc1.Definir(clave4,significado4).SiguienteSignificado() << endl;
Nat clave5 = 30;
String significado5 = "CLARO q Si";
diccHash<Nat,String>::Iterador itNuevo = dicc1.Definir(clave5,significado5);
while(itNuevo.HaySiguiente())
{
cout << "siguiente clave devuelto por el itHash: " << itNuevo.SiguienteClave() << endl;
cout << "siguiente significado devuelto por el itHash: " << itNuevo.SiguienteSignificado() << endl;
itNuevo.Avanzar();
cout << "se avanzo el itDiccHash" << endl;
}


////////////////////////// ver si al modificar el iterador tambien se modifica el diccionario:
cout << "test de ALIASING con el iterador, voy a modificar AXEL por MARADONA" << endl;
diccHash<Nat,String>::Iterador itNuevo2 = dicc1.CrearIt(clave1);
cout << "siguiente significado devuelto por el itHash: " << itNuevo2.SiguienteSignificado() << endl;
itNuevo2.SiguienteSignificado() =  "MARADONA"; // COMO ES UNA REFERENCIA, ES COMO USAR EL OBJETO EN SI, LA = ES LA ASIGNACION.
cout << "siguiente significado luego de modificar, devuelto por el itHash: " << itNuevo2.SiguienteSignificado() << endl;
cout << "significado de la clave 1: " << dicc1.Obtener(clave1)  << endl << endl;


//////borrado y creacion de iterador
dicc1.Borrar(clave5);
diccHash<Nat,String>::Iterador it10 = dicc1.CrearIt(clave4);
while(it10.HaySiguiente())
{
cout << it10.SiguienteSignificado() << endl;
it10.Avanzar();
}

// test de definicion
Nat clave10 = 11;
cout << "esta definida la clave11? :" << dicc1.EstaDefinida(clave10) << endl;
cout << "esta definida la clave4? :" << dicc1.EstaDefinida(clave4) << endl << endl;

///////////////////////////////////////// test para ver si guarda otras estructuras:
Nat claven1 =1;
Nat claven2 =2;
Nat claven3 =3;
Nat claven4 =4;
Conj<String> conj1;
Conj<String> conj2;
Conj<String> conj3;
Conj<String> conj4;
conj1.Agregar("hola");
conj2.Agregar("elto1");conj2.Agregar("elto2");
conj3.Agregar("que");conj3.Agregar("onda");conj3.Agregar("maestruli ?");
conj4.Agregar("tres");conj4.Agregar("tristes");conj4.Agregar("tigres");conj4.Agregar("comen trigo del trigal");
diccHash<Nat,Conj<String> > diccCardinal(4);
diccCardinal.Definir(claven1,conj1);
diccCardinal.Definir(claven2,conj2);
diccCardinal.Definir(claven3,conj3);
diccCardinal.Definir(claven4,conj4);
diccHash<Nat,Conj<String> >::Iterador itNuevoCardinal = diccCardinal.CrearIt(claven3);
while(itNuevoCardinal.HaySiguiente())
{
cout << "sig. clave: " << itNuevoCardinal.SiguienteClave() << endl;
cout << "sig. significado: " << itNuevoCardinal.SiguienteSignificado() << endl;
itNuevoCardinal.Avanzar(); cout << "se avanzo"<< endl;
}


  return 0;
}

