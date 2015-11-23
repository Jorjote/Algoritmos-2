#ifndef CAMPUSSEGURO_H
#define CAMPUSSEGURO_H
#include "campus.h"
#include "diccHash.h"
#include "ConjsEqu.cpp"
#include "trie.cpp"
#include "matriz.cpp"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdlib>
#include "Tipos.h"
//typedef unsigned int Agente; // CAPAZ ES INT SOLO, PORQUE PARA EL CASO -1 CREO Q EXPLOTA (no es nat).
//typedef int Agente; // asi deberia funcionar. en vez de unsigned, esto porque hay -1's
//typedef std::string Nombre;

class campusSeguro
{
    private:
     // tuplas con informacion: (structs)
        struct Datos
        {
          Posicion pos;
          Nat Sanciones;
          Nat hippiesAtrapados;
          ConjsEqu<Agente>::Iterador claseConMismasSanciones;
            std::ostream& mostrar(std::ostream& os)
            {
                os << "[" << "(" << pos.X() << "," << pos.Y() << ")" << "," << Sanciones << "," << hippiesAtrapados <<"]"<< std::endl;

                return os;
            }
        };

        struct DatosPos
        {
            Nat id;
            Nombre tag;
            Agente placa;
            diccHash<Agente,Datos>::Iterador datosAgente;
            std::ostream& mostrarDatos(std::ostream& os)
            {
                os << "(" << id << "," << tag << "," << placa << ")";
                return os;
            }

            std::ostream& mostrarTipo(std::ostream& os)
            {
                if (id == 0){os << "O";}
                if (id == 1){os << "E";}
                if (id == 2){os << "H";}
                if (id == 3){os << "A";}
                if (id == 4){os << "-";}
                return os;
            }

        };

         struct TuplaAgYSan
         { // tupla que relaciona un conjunto de agentes con Sanciones cometidas.
         Conj<Agente> conjAgentes;
         Nat Sanciones;
         };

        struct DatosSanciones
        {
           Arreglo<TuplaAgYSan> arreglo;
           bool buffer;
           ConjsEqu<Agente>::Iterador itMenosSanciones;
        };

        struct DatosAgentesyAtrapados{
        Nat agente;
        Nat cantAtrapados;
        };

        // atributos privados de la clase:
        campus _campus;
        DiccPalabra<Posicion> _estudiantes;
        DiccPalabra<Posicion> _hippies;
        Conj<Agente> _agentes;
        diccHash<Agente,Datos> datosAgentes;//Datos
        diccMatriz<DatosPos> grilla;// DatosPos
        DatosAgentesyAtrapados _masVigilante;//TuplaAgentesYAtrapados
        ConjsEqu<Agente> equivalenciaSanciones;// falta ConjsEqu
        DatosSanciones KSanciones;//DatosSanciones

         ////// funciones privadas de clase:
         bool posConvertibleAHippie(Posicion p,campus c);
         bool posConvertibleAEstudiante(Posicion p,campus c);
         bool posCapturable(Posicion p,campus c);
         bool esHippie(Posicion p);
         bool esEstudiante(Posicion p);
         bool esAgente(Posicion p);
         void actualizarMasVigilante(diccHash<Agente,Datos>::Iterador itH,Posicion p);  // VER CREO Q NO ESTA HECHA EN EL DISEÑO.
         Nat  busquedaBinaria( Arreglo<TuplaAgYSan>,Nat posInicio,Nat posFin,Nat valorBuscado);
         void actualizarDatosAgentes(Conj<Posicion> c);
         void actualizarVecinos(Posicion p);
         void actualizarEstYHippie(Conj<Posicion> c);
         bool seRetira(Posicion p,Direccion dir);
         Posicion proxPosicion(Posicion p,DiccPalabra<Posicion>::itDiccP itPos);
         //Posicion proxPosicion(Posicion p,Conj<Posicion>::Iterador itPos); // ASI ESTABA ANTES.
         void matarHippies(Conj<Posicion> c);
         void actualizarDatosAgentes(Conj<Posicion> c, Posicion este);



        public:

            // funciones publicas de la clase:
            campusSeguro(campus c,Dicc<Agente,Posicion> d);//es comenzar rastrillaje
            ~campusSeguro(); // destructor
            void ingresarEstudiante(Nombre e,Posicion p);
            void ingresarHippie(Nombre h,Posicion p);
            void moverEstudiante(Nombre e,Direccion d);
            void moverHippie(Nombre h);
            void moverAgente(Agente a);
            campus DameCampus();
            DiccPalabra<Posicion>::itDiccP estudiantes();
            Nat cantHippies();
            Nat cantEstudiantes();
            DiccPalabra<Posicion>::itDiccP Hippies();
            Conj<Agente>::Iterador agentes();
            Posicion posEstudianteYHippie(Nombre nombre);
            Posicion posAgente(Agente a);
            Nat cantSanciones(Agente a);
            Nat cantHippiesAtrapados(Agente a);
            Agente masVigilante();
            Conj<Agente> conMismasSanciones(Agente a);
            Conj<Agente>  conKSanciones(Nat k);

        std::ostream& mostrarGrilla(std::ostream& os)
        {
            //_campus.mostrarCampus(os);
            os << "-------------------------" << std::endl;
            Nat x = 0;
            while (x < grilla.Columnas() + 1)
            {
                if (x == 0)
                {
                    os << "X" << "  ";
                }
                else
                {
                    os << x << "  ";
                }
                x++;
            }
            os << std::endl;
            Nat i = 0;
            while (i < grilla.Filas())
            {
                os << std::endl;
                Nat j = 0;
                while (j < grilla.Columnas())
                {
                    if (j == 0){os << i+1 << "  ";}
                    grilla.Obtener(i, j).mostrarTipo(os) << "  ";
                    j++;
                }
                os << std::endl;
                i++;
            }

            return os;
        }
    };

#endif // CAMPUSSEGURO_H
