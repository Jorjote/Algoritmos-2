#include "ConjsEqu.cpp"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
using namespace std;


int main()
{
	ConjsEqu<String> c;

	Nat a1 =2;
	String b1 = "Leon";
	ConjsEqu<String>::Iterador it1 = c.relacionar(a1, b1);
    cout << "id del recien agregado: "<< it1.valorActual() << " Elemento recien agregado: "<< it1.elementoActual()<< endl;


    Nat a2 =2;
	String b2 = "Gato";
	ConjsEqu<String>::Iterador it2 = c.relacionar(a2, b2);
    cout << "id del recien agregado: "<< it2.valorActual() << " Elemento recien agregado: "<< it2.elementoActual()<< endl;


    Nat a3 =1;
	String b3= "arania";
	ConjsEqu<String>::Iterador it3 = c.relacionar(a3, b3);
    cout << "id del recien agregado: "<< it3.valorActual() << " Elemento recien agregado: "<< it3.elementoActual()<< endl;


    Nat a4 =2;
	String b4 = "tigre";
	ConjsEqu<String>::Iterador it4 = c.relacionar(a4, b4);
    cout << "id del recien agregado: "<< it4.valorActual() << " Elemento recien agregado: "<< it4.elementoActual()<< endl;

    Nat a5 =1;
	String b5 = "escarabajo";
	ConjsEqu<String>::Iterador it5 = c.relacionar(a5, b5);
    cout << "id del recien agregado: "<< it5.valorActual() << " Elemento recien agregado: "<< it5.elementoActual()<< endl;


    cout << "el id representa insectos, y el id 2 representa felinos" << endl;
    cout << endl<<"clase con id 2:" << endl;  c.dameConjEquivalencia(a1).Mostrar(cout);
    cout << endl<<"clase con id 1:" << endl;  c.dameConjEquivalencia(a3).Mostrar(cout);


    cout << endl << endl << "valores definidos: " << endl; c.valoresDefinidos().Mostrar(cout);  cout << endl;

   // cout << endl << "acabo de eliminar el tigre" << endl; c.eliminar(b4);
    cout << endl<<"clase con id 2:" << endl;  c.dameConjEquivalencia(a1).Mostrar(cout);
    cout << endl<<"clase con id 1:" << endl;  c.dameConjEquivalencia(a3).Mostrar(cout);


    cout << "elementos Definidos:"<< endl;
    c.elementosDefinidos().Mostrar(cout);

    cout << endl << endl;

    ConjsEqu<String>::Iterador itNuevo = c.CrearIt();
    cout << "el primer elemento es: " << itNuevo.elementoActual() << " este elemento lo voy a mandar a la clase 2"  << endl;
    Nat LaClase = 2;
    itNuevo.ItActualizarElem(LaClase);
    cout << endl<<"clase con id 2:" << endl;  c.dameConjEquivalencia(a1).Mostrar(cout);
    cout << endl<<"clase con id 1:" << endl;  c.dameConjEquivalencia(a3).Mostrar(cout);
    cout << endl;
    c.Mostrar(cout);

    Nat js1 =15;
    String j1 = "Jirafa";
    ConjsEqu<String>::Iterador itJ = c.relacionar(js1, j1);
    cout << "id del recien agregado: "<< itJ.valorActual() << " Elemento recien agregado: "<< itJ.elementoActual()<< endl;
    c.Mostrar(cout);
    itJ.ItActualizarElem(19);
    c.Mostrar(cout);

    Nat zs1 = 15;
    String z1 = "zebra";
   ConjsEqu<String>::Iterador itZ=  c.relacionar(zs1, z1);
        itZ.ItActualizarElem(16);

    Nat os1 = 19;
    String o1 = "oso";
    c.relacionar(os1, o1);
    c.Mostrar(cout);
    int j = c.elementosDefinidos().Cardinal();
    while (j >0){
        ConjsEqu<String>::Iterador mod = c.CrearIt();
        mod.ItActualizarElem(j+50);
        j--;
    }
    cout << endl;
    cout << c;
 return 0;
}