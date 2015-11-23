#include "matriz.h"


template<class T>
diccMatriz<T>::diccMatriz()
{
    Arreglo< Arreglo<T> > vacio;
    Matriz = vacio;
    filas = 0;
    cols = 0;
}

template<typename T>
diccMatriz<T>::diccMatriz(Nat n , Nat m , T value)
{
    Arreglo<Arreglo<T> > eMatriz(n);
    for(Nat i = 0; i < m; i++)
    {
        Arreglo<T> filasM(n);
        for(Nat j = 0; j < n; j++)
        {
            filasM.Definir(j, value);
        }
        eMatriz.Definir(i, filasM);
    }

    Matriz = eMatriz;
    filas = n;
    cols = m;
}

template<typename T>
diccMatriz<T>::~diccMatriz()   //destructor
{

}

template<typename T>
void diccMatriz<T>::Definir(Posicion P, const T& elem)
{
    Matriz[P.Y()-1].Definir(P.X()-1, elem);
}


template<typename T>
diccMatriz<T>& diccMatriz<T>::operator=(const diccMatriz<T>& otra)
{
    if (this != &otra)
    {
        Matriz=otra.Matriz;
        filas=otra.filas;
        cols=otra.cols;
    }

    return *this;
}

template<typename T>
T& diccMatriz<T>::Obtener(Posicion P)
{
    assert(enRango(P));
    return (Matriz[P.Y()-1])[P.X()-1];
}

template<typename T>
T& diccMatriz<T>::Obtener(Nat c, Nat f)
{
    assert(enRango(c,f));
    return (Matriz[c])[f];
}

template<typename T>
Nat diccMatriz<T>::Filas() const{
    return filas;
}

template<typename T>
Nat diccMatriz<T>::Columnas() const{
    return cols;
}

template<typename T>
bool diccMatriz<T>::enRango(Nat c, Nat f) const
{
    return (0<=f && f<filas &&  0<=c && c<cols);
}

template<typename T>
bool diccMatriz<T>::enRango(Posicion P) const
{
    return (1<=P.Y() && P.Y()<=filas &&  1<=P.X() && P.X()<=cols);
}

/////////LAS 3 OPERACIONES RESTANTES SON DE STREAM///////////////////////
// FALTA DEFINIR EL STREAM DE LA SECUENCIA PARA QUE ANDE
// template <typename T>
// void diccMatriz<T>::mostrarMatriz(std::ostream& os)const{
//      os << " | Inicio matriz | " << std::endl;
//      Nat i=0;
//      Nat j=0;
//      while( i<this->Dimension()){
//        j=0;
//        while( j<this->Dimension() ){
//         if(  this->enRango(i,j) ){
//           os << "["<< i << "] ["<< j << "] = ";
//           (this->Obtener(i,j)).Mostrar(os);
//           os << std::endl;
//         }else{
//           os << "["<< i << "] ["<< j << "] = "<< "no esta en rango" <<std::endl;
//         }
//        j++;
//     }
//         i++;
//      }
//      os << " | Fin matriz | " << std::endl;
// }

// template<typename T> // redefino <<, osea lo sobrecargo
// std::ostream& operator<<(std::ostream& out, const diccMatriz<T>& m) {
//      return m.mostrarMatriz(out);
// }
