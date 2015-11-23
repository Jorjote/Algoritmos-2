#ifndef AED2_TIPOS_H_
#define AED2_TIPOS_H_

#include "Modulos Basicos/aed2/TiposBasicos.h"

namespace aed2{

      struct Posicion
    {
        Posicion(Nat coordX, Nat coordY):x(coordX),y(coordY){}
        Posicion(){x=0;y=0;}; // constructor por defecto de Posicion.
        Nat x;
        Nat y;
        Nat X()const{Nat res=0;res=this->x;return res;}
        Nat Y()const{Nat res=0;res=this->y;return res;}
        bool operator == (Posicion p)const {return (this->X()==p.X()) && (this->Y()==p.Y());}

        std::ostream& mostrar(std::ostream& os)
        {
            os << "(" << x << "," << y << ")";
            return os;
        }
    };
	typedef enum {izq,der,arriba,abajo} Direccion;
	typedef Nat Agente;
	typedef String Nombre;

} // namespace aed2

#endif // AED2_TIPOS_H_
