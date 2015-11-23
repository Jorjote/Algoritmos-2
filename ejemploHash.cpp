#include "diccHash.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
using namespace std;


int main() {

///// Diccionario de Nat y Conjunto de Strings.
Nat claven1 =1;
Nat claven2 =2;
Nat claven3 =3;
Nat claven4 =4;
Conj<String> conj1;
Conj<String> conj2;
Conj<String> conj3;
Conj<String> conj4;
Conj<String> conj2Bis;
conj1.Agregar("hola");
conj2.Agregar("elto1");conj2.Agregar("elto2");
conj3.Agregar("que");conj3.Agregar("onda");conj3.Agregar("maestruli ?");
conj4.Agregar("tres");conj4.Agregar("tristes");conj4.Agregar("tigres");conj4.Agregar("comen trigo del trigal");
conj2Bis.Agregar("lalalla");conj2Bis.Agregar("nubeee");
// ACA SE CREA EL DICCIONARIO Y SE DEFINEN LAS CLAVES
diccHash<Nat,Conj<String> > diccCardinal(4); // creo el dicc con capacidad para 4 claves y significados
diccCardinal.Definir(claven1,conj1);  // retorna iterador con siguiente en claven1
diccCardinal.Definir(claven2,conj2);  // retorna iterador con siguiente en claven1
diccCardinal.Definir(claven3,conj3); // retorna iterador con siguiente en claven1
diccCardinal.Definir(claven4,conj4); // retorna iterador con siguiente en claven1
diccCardinal.Definir(claven2,conj2Bis); // redefino claven2
// ACA SE CREA EL ITERADOR
diccHash<Nat,Conj<String> >::Iterador itNuevoCardinal = diccCardinal.CrearIt(claven3);

// ACA SE ITERAN LOS ELEMENTOS EN UN WHILE
while(itNuevoCardinal.HaySiguiente())
{
cout << "sig. clave: " << itNuevoCardinal.SiguienteClave() << endl;
cout << "sig. significado: " << itNuevoCardinal.SiguienteSignificado() << endl;
itNuevoCardinal.Avanzar(); cout << "se avanzo"<< endl;
}



////////////////////////////// otras operaciones

Nat claven10 = 11;
cout << "esta definida la clave11? :" << diccCardinal.EstaDefinida(claven10) << endl;
cout << "esta definida la clave4? :" << diccCardinal.EstaDefinida(claven4) << endl << endl;
diccCardinal.Obtener(claven4);


diccHash<Nat,Conj<String> >::Iterador it;// test para ver si funciona bien el constructor por defecto del iterador.

  return 0;
}



