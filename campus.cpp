#include "campus.h"
#include <iostream>
using namespace std;

campus::campus(Nat an , Nat al)
{
	Ancho = an;
	Alto = al;
	//Obstaculos;//NO HACE FALTA PORQUE ES UN CONJUNTO VACIO
}

campus::campus() // constructor por defecto.
{
    Ancho=0;
    Alto=0;
}

/*
campus::~campus()
{
    //destructor,si no hay news no hay que hacer nada
}
*/

void campus::AgregarObstaculo(Posicion p)
{   // Pre: la posicion p ingresada, no esta agregada en el campus.
	Obstaculos.AgregarRapido(p);
}

Nat campus::Filas()
{
	return Alto;
}

Nat campus::Columnas()
{
	return Ancho;
}



bool campus::Posocupada(Posicion p)
{
return Obstaculos.Pertenece(p);
}

bool campus::Valida(Posicion p)
{
return (( 1<= p.x && p.x <= Ancho) && (1<= p.y && p.y <= Alto));
}

bool campus::EsIngreso(Posicion p)
{
return (p.y==1 || p.y==Alto)&&(Valida(p));
}

bool campus::IngresoInferior(Posicion p)
{
    return (p.y==Alto)&&(Valida(p));
}

bool campus::IngresoSuperior(Posicion p)
{
    return (p.y==1)&&(Valida(p));
}


Conj<Posicion> campus::Vecinos(Posicion p)
{// retorna vecinos validos dentro dela grilla,no importa si estan ocupados.
    Posicion posArriba;//( p.x ,p.y-1);
    posArriba.x = p.x;
    posArriba.y = p.y-1;

    Posicion posAbajo;//( p.x,p.y+1);
    posAbajo.x = p.x;
    posAbajo.y = p.y+1;

    Posicion posDer;//(p.x+1,p.y);
    posDer.x = p.x+1;
    posDer.y = p.y;

    Posicion posIzq;//(p.x-1,p.y);
    posIzq.x = p.x-1;
    posIzq.y = p.y;

    Conj<Posicion> res;
    // Agrego las posiciones validas:
    if (Valida(posArriba)){  res.AgregarRapido(posArriba); }
    if (Valida(posAbajo)) {  res.AgregarRapido(posAbajo);  }
    if (Valida(posDer))   {  res.AgregarRapido(posDer);    }
    if (Valida(posIzq))   {  res.AgregarRapido(posIzq);    }
    return res;
}

Nat campus::Distancia(Posicion p1,Posicion p2)
{
Nat a=0; Nat b=0;
if(p1.x>p2.x){a=p1.x-p2.x;}else{a=p2.x-p1.x;} // esto es porque como Nat es entero positivo, no existen los negativos.
if(p1.y>p2.y){b=p1.y-p2.y;}else{b=p2.y-p1.y;} // lo mismo que antes. Nat= unisigned integer. por lo tanto existe a-b, pero no b-a, salvo que a sea igual a b.
return a+b;
}



Posicion campus::ProximaPos(Posicion p, Direccion dir)
{
    Posicion p1;
    p1.x = p.x;
    p1.y = p.y;

    if(dir==arriba){p1.y = p.y-1;}
    if(dir==abajo){p1.y = p.y+1;}
    if(dir==izq){p1.x = p.x-1;}
    if(dir==der){p1.x = p.x+1;}

    return p1;
}

Conj<Posicion> campus::IngresosCercanos(Posicion p)
{
Conj<Posicion> res;
Posicion posIngresoFilaUno;//(p.x,0); // ACA LA PRIMER FILA ES LA 0 (CAPAZ HAY QUE MODIFICARLO)
posIngresoFilaUno.x = p.x;
posIngresoFilaUno.y = 0;

Posicion posIngresoUltimaFila;//(p.x,Filas()-1); // LA ULTIMA FILA ES LA CANTIDAD DE FILAS - 1 (CAPAZ HAY QUE MODIFICARLO)
posIngresoUltimaFila.x = p.x;
posIngresoUltimaFila.y = Filas()-1;
if( Distancia(p,posIngresoFilaUno) < Distancia(p,posIngresoUltimaFila) ) // caso <
{
    res.AgregarRapido(posIngresoFilaUno);
}
else
{
    if(  Distancia(p,posIngresoFilaUno) > Distancia(p,posIngresoUltimaFila)  ) // caso >
    {
       res.AgregarRapido(posIngresoUltimaFila);
    }
    else
    {//caso ==
        res.AgregarRapido(posIngresoFilaUno);
        res.AgregarRapido(posIngresoUltimaFila);
    }
}
return res;
}


ostream& campus::mostrarCampus(ostream& os)
{
    Nat i=1;
    Nat j=1;
   cout << "--comienzo del Stream del campus--"<< endl;
   cout << "campus por posiciones: " << endl;
   while( j<=Alto )
    {
        i=1;
        while(i<= Ancho)
        {
        Posicion aux;//(i,j);
        aux.x = i;
        aux.y = j;
         os << " (" << aux.x << "," << aux.y << ") " ;
         i++;
        }
        os<< endl;
    j++;
    }

   cout << "campus por ocupacion: O=ocupado, D=desocupado" << endl;
   i=1;j=1;
    while( j<=Alto )
    {
        i=1;
        while(i<= Ancho)
        {
            Posicion aux;//(i,j);
            aux.x = i;
            aux.y = j;
            if( Posocupada(aux) ){  os<<" O "; }else{  os<<" D "; }
            i++;
        }
        os<< endl;
    j++;
    }
cout << "--Fin del Stream del campus--"<< endl;
return os;
}


ostream& operator<<(ostream& out,  campus& a)
{
    return a.mostrarCampus(out);
}
