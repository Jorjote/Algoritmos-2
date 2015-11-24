#include "campusSeguro.h"
// comentarios de lo que falta:
////// FALTA actualizarMasVigilante EL ALGORITMO.

        /// FUNCIONES PUBLICAS DE CAMPUS SEGURO ///

campusSeguro::campusSeguro(campus c, Dicc<Agente,Posicion> d)
{
    campus camp = c;
    DiccPalabra<Posicion> estyHip;// creo un DiccTrie vacio.
    campusSeguro::DatosPos tup;
    tup.id = 4;
    tup.tag = "libre";
    tup.placa = 0;
    Nat cantidadFilas=c.Filas();
    Nat cantidadColumnas=c.Columnas();
    diccMatriz<campusSeguro::DatosPos> datosMatriz(cantidadFilas,cantidadColumnas,tup);
    diccHash<Agente,campusSeguro::Datos> dicc(d.CantClaves()); // creo dicchash de tamaño d.Claves().Cardinal()
    diccHash<Agente,campusSeguro::Datos>::Iterador itHashVacio = dicc.CrearIt();
    tup.datosAgente = itHashVacio;
    ConjsEqu<Agente>  equSan; // creo un EqusEqu vacio y lo guardo en la variable equSan.
    campusSeguro::DatosSanciones KSan;
    Nat i = 1;
    Nat j = 1;
      while( i <= c.Filas() )
      {
            while( j <= c.Columnas())
            {
              //Posicion pos(i,j); // creo una posicion (i,j).
                Posicion p;
                p.x = i;
                p.y = j;
                campusSeguro::DatosPos data;  // ESTA VARIABLE NO SE SI VA DENTRO DEL SCOPE DEL WHILE, xq SE BORRA.
                if( camp.Posocupada(p))
                {
                    data.id = 0;
                    data.tag = "ocupada";
                    data.placa = 0;
                    data.datosAgente = itHashVacio;
                    datosMatriz.Definir(p, data);
                }
                j++;
            }// endwhile
            i++;
      }// endwhile

    Dicc<Agente,Posicion>::Iterador it;
    it = d.CrearIt();

  while( it.HaySiguiente() )
  {
        campusSeguro::DatosPos data;  // ESTA VARIABLE NO SE SI VA DENTRO DEL SCOPE DEL WHILE, xq SE BORRA.
        campusSeguro::Datos dataH;
        Posicion pos;
        Agente plak;
        ConjsEqu<Agente>::Iterador itEqu;

        plak = it.SiguienteClave();
        pos = it.SiguienteSignificado();
        itEqu = equSan.relacionar(0, plak);
        dataH.pos = pos;
        dataH.Sanciones = 0;
        dataH.hippiesAtrapados = 0;
        dataH.claseConMismasSanciones = itEqu;
        data.id = 3;
        data.tag = "agente";
        data.placa = plak;
        data.datosAgente = dicc.Definir(plak, dataH); // definir retorna un iterador de Dicc.
        datosMatriz.Definir(pos, data);
        it.Avanzar();
  }
    Arreglo<TuplaAgYSan> nuevoArreglo(1); // creo array de 1 posicion
    KSan.arreglo = nuevoArreglo; // meto el arreglo en el campo arreglo de KSan.
    KSan.buffer = false;
    KSan.itMenosSanciones = equSan.CrearIt();

     // el masvigilante al comienzo de la instancia campusSeguro es cualquier vigilante:
    campusSeguro::DatosAgentesyAtrapados elMas;
    Dicc<Agente,Posicion>::Iterador itAgts = d.CrearIt();
    elMas.agente = itAgts.SiguienteClave();// el primer agente que encuentre.
    elMas.cantAtrapados = 0;

     // incio la instancia:
    _campus = camp;
    _estudiantes = estyHip;
    _hippies = estyHip;
    Conj<Agente> conjuntoDeAgentes; // conjunto vacio que almacenará agentes
    Dicc<Agente,Posicion>::Iterador itDiccAgentes = d.CrearIt();

    while(itDiccAgentes.HaySiguiente()) // voy llenando el conjunto con los agentes del diccionario.
    {
        conjuntoDeAgentes.AgregarRapido(itDiccAgentes.SiguienteClave());
        itDiccAgentes.Avanzar();
    }

    _agentes = conjuntoDeAgentes;
    datosAgentes = dicc;
    grilla = datosMatriz;
    _masVigilante = elMas;
    equivalenciaSanciones = equSan;
    KSanciones = KSan;
    Dicc<Agente,Posicion>::Iterador it2;
    it2 = d.CrearIt();

} // fin funcion constructora (rastrillaje).


campusSeguro::~campusSeguro()
{

} // destructor


void campusSeguro::ingresarEstudiante(Nombre e, Posicion p)
{
    if( posConvertibleAHippie(p, _campus) )
    {
        _hippies.Definir(e, p);
        grilla.Obtener(p).id  = 2  ;
        grilla.Obtener(p).tag  = e  ;
        grilla.Obtener(p).placa  =  0 ;
        //grilla.Obtener(p).datosAgente  = grilla.Obtener(p).datosAgente;// esta demas, pero lo pongo asi es mas claro.
    }
    else
    {
        _estudiantes.Definir(e,p);
        grilla.Obtener(p).id  = 1  ;
        grilla.Obtener(p).tag  = e  ;
        grilla.Obtener(p).placa  =  0 ;
        //grilla.Obtener(p).datosAgente  = grilla.Obtener(p).datosAgente;// esta demas, pero lo pongo asi es mas claro.

    }

    actualizarVecinos(p);
}


void campusSeguro::ingresarHippie(Nombre h,Posicion p)
{
    if( posConvertibleAEstudiante(p,_campus) )
    {
        _estudiantes.Definir(h,p);
        grilla.Obtener(p).id  = 1  ;
        grilla.Obtener(p).tag  = h  ;
        grilla.Obtener(p).placa  =  0 ;
        actualizarVecinos(p);
        //grilla.Obtener(p).datosAgente  = grilla.Obtener(p).datosAgente;// esta demas, pero lo pongo asi es mas claro.
    }
    else
    {
        if( posCapturable(p,_campus) )
        {
            /// agrego los datos del hippie a la grilla
            grilla.Obtener(p).id  = 2  ;
            //grilla.Obtener(p).tag  = h  ;
            grilla.Obtener(p).placa  =  0 ;
            /// ahora si actualizo los vecinos y despues seteo como libre en la grilla.
            actualizarVecinos(p);
            grilla.Obtener(p).id  = 4  ;
        }
        else
        {
            _hippies.Definir(h,p);
            grilla.Obtener(p).id  = 2  ;
            grilla.Obtener(p).tag  = h  ;
            grilla.Obtener(p).placa  =  0 ;
            actualizarVecinos(p);
            //grilla.Obtener(p).datosAgente  = grilla.Obtener(p).datosAgente;// esta demas, pero lo pongo asi es mas claro.
        }
    }
}


void campusSeguro::moverEstudiante(Nombre e,Direccion dir)
{
    Posicion posActual = _estudiantes.Obtener(e);
    if( seRetira(posActual,dir) )
    {
        _estudiantes.Borrar(e);
        grilla.Obtener(posActual ).id = 4;
        grilla.Obtener(posActual ).tag = "libre";
        grilla.Obtener(posActual ).placa = 0;
        //diccHash<Agente,Datos> d(0);// dicchash vacio.
        //diccHash<Agente,Datos>::Iterador itNulo = d.CrearIt();// creo un iterador vacio.
        //grilla.Obtener(posActual).datosAgente = itNulo;
    }
    else
    {
        Posicion nuevaPos = _campus.ProximaPos(posActual,dir);
        if(!(posActual==nuevaPos))
        {
          grilla.Obtener( posActual ).id  = 4;
          grilla.Obtener( posActual ).tag  = "libre";
          grilla.Obtener( posActual ).placa  = 0;
          //diccHash<Agente,Datos> d(0);// dicchash vacio.
          //diccHash<Agente,Datos>::Iterador itNulo = d.CrearIt();// creo un iterador vacio.
          //grilla.Obtener(posActual).datosAgente = itNulo;

            if( posConvertibleAHippie(nuevaPos,_campus) )
            {
                _hippies.Definir(e,nuevaPos);
                grilla.Obtener( nuevaPos ).id = 2;
                grilla.Obtener( nuevaPos ).tag  = e;
                grilla.Obtener( nuevaPos ).placa  = 0;
                _estudiantes.Borrar(e);
                //grilla.Obtener( nuevaPos ).datosAgente  = grilla.Obtener( nuevaPos ).datosAgente;
            }
            else
            {
                _estudiantes.Borrar(e);
                _estudiantes.Definir(e,nuevaPos);
                grilla.Obtener( nuevaPos ).id = 1;
                grilla.Obtener( nuevaPos ).tag  = e;
                grilla.Obtener( nuevaPos ).placa  = 0;
                //grilla.Obtener( nuevaPos ).datosAgente  = grilla.Obtener( nuevaPos ).datosAgente;
            }

        actualizarEstYHippie(_campus.Vecinos(nuevaPos));
        actualizarVecinos(nuevaPos);

        }
    }

}

void campusSeguro::moverHippie(Nombre h)
{
    Posicion posActual = _hippies.Obtener(h);
    DiccPalabra<Posicion>::itDiccP itPos = _estudiantes.Claves();
    Posicion nuevaPos = proxPosicion(posActual, itPos );

    if(!(posActual == nuevaPos))
    {
        grilla.Obtener(posActual).id = 4;
        grilla.Obtener(posActual).tag = "libre";
        grilla.Obtener(posActual).placa = 0;
        //ingresarHippie(h, nuevaPos);

        //diccHash<Agente,Datos> d(0);// dicchash vacio.
        //diccHash<Agente,Datos>::Iterador itNulo = d.CrearIt();// creo un iterador vacio.
        //grilla.Obtener(posActual).datosAgente = itNulo;

        _hippies.Borrar(h);
        _hippies.Definir(h,nuevaPos);
        grilla.Obtener(nuevaPos).id = 2;
        grilla.Obtener(nuevaPos).tag = h;
        grilla.Obtener(nuevaPos).placa = 0;
        //grilla.Obtener(nuevaPos).datosAgente = grilla.Obtener(nuevaPos).datosAgente;
        actualizarEstYHippie(_campus.Vecinos(nuevaPos));
        actualizarVecinos(nuevaPos);
    }
}// fin funcion


/*
void campusSeguro::moverHippie(Nombre h)
{
  Posicion posActual = _hippies.Obtener(h);
  DiccPalabra<Posicion>::itDiccP itPos = _estudiantes.Claves();
  Posicion nuevaPos = proxPosicion(posActual, itPos );
  if( !(posActual == nuevaPos) )
  {
    grilla.Obtener(posActual).id = 4;
    grilla.Obtener(posActual).tag = h;
    grilla.Obtener(posActual).placa = 0;
    diccHash<Agente,Datos> d(0);// dicchash vacio.
    diccHash<Agente,Datos>::Iterador itNulo = d.CrearIt();// creo un iterador vacio.
    grilla.Obtener(posActual).datosAgente = itNulo;
    if( posConvertibleAEstudiante(nuevaPos,_campus)  )
      {
        _estudiantes.Definir(h,nuevaPos);
        grilla.Obtener(nuevaPos).id = 1;
        grilla.Obtener(nuevaPos).tag = h;
        grilla.Obtener(nuevaPos).placa = 0;
        grilla.Obtener(nuevaPos).datosAgente = grilla.Obtener(nuevaPos).datosAgente;
        actualizarVecinos(nuevaPos);
      }
      else
      {
        _hippies.Definir(h,nuevaPos);
        grilla.Obtener(nuevaPos).id = 2;
        grilla.Obtener(nuevaPos).tag = h;
        actualizarVecinos(nuevaPos);

        if( posCapturable(nuevaPos,_campus) )
        {
            grilla.Obtener(nuevaPos).id = 4;
        }
      }
  }// fin 1er If
}// fin funcion

*/
void campusSeguro::moverAgente(Agente a)
{
    Posicion posActual = posAgente(a);
    //Conj<campus::Posicion>::Iterador itPos = _hippies.Claves();
    DiccPalabra<Posicion>::itDiccP itPos = _hippies.Claves();
    Posicion nuevaPos = proxPosicion(posActual, itPos );

    if( !(posActual == nuevaPos) )
    {
        grilla.Obtener( nuevaPos ).tag =  grilla.Obtener( posActual ).tag;
        grilla.Obtener( nuevaPos ).id =   grilla.Obtener( posActual ).id;
        grilla.Obtener( posActual).id =  4;
        grilla.Obtener( nuevaPos ).placa =  grilla.Obtener( posActual ).placa;
        grilla.Obtener( nuevaPos ).datosAgente =  grilla.Obtener( posActual ).datosAgente;
        Conj<Posicion> c;
        c.Agregar(nuevaPos);
        actualizarDatosAgentes(c);
        actualizarEstYHippie(_campus.Vecinos(nuevaPos));// en el diseño aca hay un Siguiente(itVecinos) que esta demas.
        actualizarVecinos(nuevaPos);
    }
}


campus campusSeguro::DameCampus()
{
    return _campus;
}


DiccPalabra<Posicion>::itDiccP campusSeguro::estudiantes()
{
    return _estudiantes.CrearIt();
}


Nat campusSeguro::cantHippies()
{
    return _hippies.cantClaves();
}


Nat campusSeguro::cantEstudiantes()
{
    return _estudiantes.cantClaves();
}

DiccPalabra<Posicion>::itDiccP campusSeguro::Hippies()
{
    return _hippies.CrearIt();
}


Conj<Agente>::Iterador campusSeguro::agentes()
{
    return _agentes.CrearIt();
}


Posicion campusSeguro::posEstudianteYHippie(Nombre n)
{
    Posicion res;
    if(  _estudiantes.Definido(n) )
    {
        res = _estudiantes.Obtener(n);
    }
    else
    {
        res = _hippies.Obtener(n);
    }

    return res;
}



Posicion campusSeguro::posAgente(Agente a)
{
    return datosAgentes.Obtener(a).pos;
}




Nat campusSeguro::cantSanciones(Agente a) // de esta forma anda( HAY QUE VER QUE ONDA CON EL ITERADOR DEL HASH PORQUE NO MODIFICA SI LO DEFINO DIRECTAMENTE EN EL HASH TODO BIEN; PERO SI MODIFICO EL ITERADOR NO SE MODIFCA EL HASH ES RARO)
{
    /*
    Posicion P = datosAgentes.Obtener(a).pos;
    return grilla.Obtener(P).datosAgente.SiguienteSignificado().Sanciones;
    */
    return datosAgentes.Obtener(a).Sanciones;
}



Nat campusSeguro::cantHippiesAtrapados(Agente a)
{
    return datosAgentes.Obtener(a).hippiesAtrapados;
}


Agente campusSeguro::masVigilante()
{
    return _masVigilante.agente;
}


Conj<Agente> campusSeguro::conMismasSanciones(Agente a)
{
    ConjsEqu<Agente>::Iterador it = datosAgentes.Obtener(a).claseConMismasSanciones;
    return it.claseActual();
}


Conj<Agente>  campusSeguro::conKSanciones(Nat k)
{
    Conj<Agente> res;
    Nat posK;
    if(KSanciones.buffer) // .buffer es el .pi2
    {
        posK = busquedaBinaria(KSanciones.arreglo,0,KSanciones.arreglo.Tamanho()-1,k);
        res = KSanciones.arreglo[posK].conjAgentes; // pi1=.arreglo y el otro .pi1=conjAgentes
    }
    else
    {
        ConjsEqu<Agente>::Iterador it  =  KSanciones.itMenosSanciones;
        //Arreglo<campusSeguro::TuplaAgYSan> arreglo = Arreglo(agentes.Cardinal());
        Arreglo<campusSeguro::TuplaAgYSan> arreglo(_agentes.Cardinal());
        Nat indice = 0;
        Nat valAct = -1;

        while( it.HaySiguiente() )
        {
            if( it.valorActual() != valAct )
            {
               valAct = it.valorActual();
               campusSeguro::TuplaAgYSan clase;
               clase.conjAgentes = it.claseActual();
               clase.Sanciones = it.valorActual();
               arreglo[indice] = clase;
               indice++;
            }// fin if

            it.Avanzar();
        }// fin 1er while

        while( indice < arreglo.Tamanho() )
        {
            campusSeguro::TuplaAgYSan claseVac;
            Conj<Agente> conjvacio; // creo un conjunto vacio, sin elementos.
            claseVac.conjAgentes = conjvacio;
            claseVac.Sanciones   = valAct+1;
            arreglo[indice]=claseVac;
            indice++;
        }// fin 2do while

        KSanciones.arreglo = arreglo;
        KSanciones.buffer = true;
        KSanciones.itMenosSanciones = KSanciones.itMenosSanciones; // esta demas,pero lo pongo asi queda clara la idea.
    }   // fin else

    return res;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         // FUNCIONES PRIVADAS DE CAMPUSSEGURO





bool campusSeguro::posConvertibleAHippie(Posicion p,campus c)
{
Conj<Posicion> vecinos = c.Vecinos(p);
Conj<Posicion>::Iterador it = vecinos.CrearIt();
Nat cantHippies = 0;
while(  it.HaySiguiente() )
{
   Posicion posVec = it.Siguiente();
   if( (grilla.Obtener(posVec)).id==2  ) {cantHippies=cantHippies+1;}
   it.Avanzar();
}
return cantHippies>=2;
}



bool campusSeguro::posConvertibleAEstudiante(Posicion p,campus c)
{
    Conj<Posicion> vecinos = c.Vecinos(p);
    Conj<Posicion>::Iterador it = vecinos.CrearIt();
    Nat cantEstudiantes = 0;
    while(  it.HaySiguiente() )
    {
       Posicion posVec = it.Siguiente();
       if( (grilla.Obtener(posVec)).id==1  ) {cantEstudiantes=cantEstudiantes+1;}
       it.Avanzar();
    }
    return cantEstudiantes==4;
}



bool campusSeguro::posCapturable(Posicion p,campus c)
{
    Conj<Posicion> vecinos = c.Vecinos(p);
    Conj<Posicion>::Iterador it = vecinos.CrearIt();
    Nat cantOcupados = 0;
    Nat cantAgentes = 0;
    while(  it.HaySiguiente() )
    {
       Posicion posVec = it.Siguiente();
       if( (grilla.Obtener(posVec)).id != 4  ){cantOcupados=cantOcupados + 1;}
       if( (grilla.Obtener(posVec)).id == 3  ){cantAgentes=cantAgentes + 1;}
       it.Avanzar();
    }
    return (cantAgentes > 0  &&  cantOcupados == vecinos.Cardinal());
}




bool campusSeguro::esHippie(Posicion p)
{
    return (grilla.Obtener(p)).id == 2;
}


bool campusSeguro::esEstudiante(Posicion p)
{
    return (grilla.Obtener(p)).id==1;
}


bool campusSeguro::esAgente(Posicion p)
{
    return (grilla.Obtener(p)).id==3;
}

Nat campusSeguro::busquedaBinaria( Arreglo<TuplaAgYSan> arr,Nat posInicio,Nat posFin,Nat valorBuscado)
{
    Nat pivote=(posFin-posInicio)/2; // division de enteros es entera en c++.
    if( arr[pivote].Sanciones>valorBuscado )
    {
        busquedaBinaria(arr,posInicio,pivote,valorBuscado);
    }
    else
    {
        if( arr[pivote].Sanciones < valorBuscado )
        {
            busquedaBinaria(arr, pivote, posFin, valorBuscado);
        }
        else
        {
            if( arr[pivote].Sanciones == valorBuscado )
            {
                return pivote;
            }
        }
    }
    return pivote;
}



bool campusSeguro::seRetira(Posicion p,Direccion dir)
{
bool res=false;
if( _campus.IngresoSuperior(p) ){ if(dir==arriba){res=true;}  }
if( _campus.IngresoInferior(p) ){ if(dir==abajo) {res=true;}  }
return res;
}

// FALTA EL ALGORITMO
void campusSeguro::actualizarMasVigilante(diccHash<Agente,Datos>::Iterador itH,Posicion p)
{

}


void campusSeguro::actualizarDatosAgentes(Conj<Posicion> c, Posicion este)
{
    Posicion posActual;
    Conj<Posicion>::Iterador it = c.CrearIt();
    while( it.HaySiguiente() )
    {
        posActual = it.Siguiente();
        if( posCapturable(este,_campus) )
        {
            Posicion vecActual = este;
            if( esAgente(posActual) && esHippie(vecActual) )
            {
                diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(posActual).datosAgente;
                //datosVec.SiguienteSignificado().hippiesAtrapados++;
                //Nat cantAtrapadosVec = datosVec.SiguienteSignificado().hippiesAtrapados;
                Agente ac = grilla.Obtener(posActual).placa;
                datosAgentes.Obtener(ac).hippiesAtrapados++;
                Nat cantAtrapadosVec = datosAgentes.Obtener(ac).hippiesAtrapados;

                if(cantAtrapadosVec > _masVigilante.cantAtrapados  )
                {
                    //(_masVigilante).agente = datosVec.SiguienteClave();
                    _masVigilante.agente = ac;
                    (_masVigilante).cantAtrapados = cantAtrapadosVec;
                }

                if( (cantAtrapadosVec == (_masVigilante).cantAtrapados) && ( datosVec.SiguienteClave()< (_masVigilante).agente) )
                {
                    //(_masVigilante).agente = datosVec.SiguienteClave();
                    _masVigilante.agente = ac;
                    (_masVigilante).cantAtrapados = cantAtrapadosVec;
                }
            }

            if( esAgente(posActual) && esEstudiante(vecActual) )
            {
                diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(posActual).datosAgente;
                //datosVec.SiguienteSignificado().Sanciones++;
                //grilla.Obtener(posActual).datosAgente.SiguienteSignificado().Sanciones++;
                Agente ac = grilla.Obtener(posActual).placa;
                datosAgentes.Obtener(ac).Sanciones++;
                //Nat vecSancionesActual = datosAgentes.Obtener(ac).Sanciones;
                //datosVec.SiguienteSignificado().claseConMismasSanciones.ItActualizarElem(vecSancionesActual);  // CREOOO QUE ES DE CONJEQU
                KSanciones.buffer = false;
            }
        }
        it.Avanzar();
    }
}

/*
void campusSeguro::actualizarDatosAgentes(Conj<Posicion> c, Posicion este)
{
    Posicion posActual;
    Conj<Posicion>::Iterador it = c.CrearIt();
    while( it.HaySiguiente() )
    {
        posActual = it.Siguiente();
        if( posCapturable(este,_campus) )
        {
            Conj<Posicion> vecinosDePosActual = _campus.Vecinos(posActual);
            Conj<Posicion>::Iterador itVec = vecinosDePosActual.CrearIt();
            while( itVec.HaySiguiente())
            {
                Posicion vecActual = itVec.Siguiente();
                if( esAgente(posActual) && esHippie(vecActual) )
                {
                    diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(posActual).datosAgente;
                    //datosVec.SiguienteSignificado().hippiesAtrapados++;
                    //Nat cantAtrapadosVec = datosVec.SiguienteSignificado().hippiesAtrapados;
                    Agente ac = grilla.Obtener(posActual).placa;
                    datosAgentes.Obtener(ac).hippiesAtrapados++;
                    Nat cantAtrapadosVec = datosAgentes.Obtener(ac).hippiesAtrapados;

                    if(cantAtrapadosVec > _masVigilante.cantAtrapados  )
                    {
                        //(_masVigilante).agente = datosVec.SiguienteClave();
                        _masVigilante.agente = ac;
                        (_masVigilante).cantAtrapados = cantAtrapadosVec;
                    }

                    if( (cantAtrapadosVec == (_masVigilante).cantAtrapados) && ( datosVec.SiguienteClave()< (_masVigilante).agente) )
                    {
                        //(_masVigilante).agente = datosVec.SiguienteClave();
                        _masVigilante.agente = ac;
                        (_masVigilante).cantAtrapados = cantAtrapadosVec;
                    }
                }

                if( esAgente(posActual) && esEstudiante(vecActual) )
                {
                    diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(posActual).datosAgente;
                    //datosVec.SiguienteSignificado().Sanciones++;
                    //grilla.Obtener(posActual).datosAgente.SiguienteSignificado().Sanciones++;
                    Agente ac = grilla.Obtener(posActual).placa;
                    datosAgentes.Obtener(ac).Sanciones++;
                    //Nat vecSancionesActual = datosAgentes.Obtener(ac).Sanciones;
                    //datosVec.SiguienteSignificado().claseConMismasSanciones.ItActualizarElem(vecSancionesActual);  // CREOOO QUE ES DE CONJEQU
                    KSanciones.buffer = false;
                }

                itVec.Avanzar();
            }
        }
        it.Avanzar();
    }
}
*/

void campusSeguro::actualizarDatosAgentes(Conj<Posicion> c)
{
    Posicion posActual;
    Conj<Posicion>::Iterador it = c.CrearIt();
    while( it.HaySiguiente() )
    {
        posActual=it.Siguiente();
        if( posCapturable(posActual,_campus) )
        {
            Conj<Posicion> vecinosDePosActual = _campus.Vecinos(posActual);
            Conj<Posicion>::Iterador itVec = vecinosDePosActual.CrearIt();
            while( itVec.HaySiguiente())
            {
                Posicion vecActual = itVec.Siguiente();
                if( esAgente(vecActual) && esHippie(posActual) )
                {
                    diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(vecActual).datosAgente;
                    datosVec.SiguienteSignificado().hippiesAtrapados++;
                    Nat cantAtrapadosVec = datosVec.SiguienteSignificado().hippiesAtrapados;

                if(cantAtrapadosVec > _masVigilante.cantAtrapados  )
                {
                    (_masVigilante).agente = datosVec.SiguienteClave();
                    (_masVigilante).cantAtrapados = cantAtrapadosVec;
                }

                if( (cantAtrapadosVec == (_masVigilante).cantAtrapados) && ( datosVec.SiguienteClave()< (_masVigilante).agente) )
                {
                    (_masVigilante).agente = datosVec.SiguienteClave();
                    (_masVigilante).cantAtrapados = cantAtrapadosVec;
                }
                }

                if( esAgente(vecActual) && esEstudiante(posActual) )
                {
                    //diccHash<Agente,Datos>::Iterador datosVec = grilla.Obtener(vecActual).datosAgente;
                    //datosVec.SiguienteSignificado().Sanciones++;
                    //Nat vecSancionesActual = datosVec.SiguienteSignificado().Sanciones;

                    Agente ac = grilla.Obtener(posActual).placa;
                    datosAgentes.Obtener(ac).Sanciones ++;

                    //Nat vecSancionesActual = datosAgentes.Obtener(ac).Sanciones;
                    //datosAgentes.Obtener(ac).claseConMismasSanciones.ItActualizarElem(vecSancionesActual);

                    //datosVec.SiguienteSignificado().claseConMismasSanciones.ItActualizarElem(vecSancionesActual);  // CREOOO QUE ES DE CONJEQU
                    (KSanciones).buffer = false;
                }

            itVec.Avanzar();
            }
        }
        it.Avanzar();
    }
}


void campusSeguro::actualizarVecinos(Posicion p)
{
 Conj<Posicion> vec = _campus.Vecinos(p);
 Conj<Posicion>::Iterador itVecinos = vec.CrearIt();
 actualizarDatosAgentes(vec, p);
 while( itVecinos.HaySiguiente() )
 {
    Posicion vec1 = itVecinos.Siguiente();
  /*  Conj<Posicion> vecinosDeVecino = DameCampus().Vecinos(vec1);
    Conj<Posicion>::const_Iterador itVecinosVec = vecinosDeVecino.CrearIt();
    while( itVecinosVec.HaySiguiente() )
    {
*/
        if( posConvertibleAEstudiante(vec1,_campus) && esHippie(vec1) )
        {
            Nombre name = grilla.Obtener(vec1).tag ;
            (_estudiantes).Definir(name,vec1 );
            (_hippies).Borrar( name );
        }
        else
        {
          if( posCapturable(vec1,_campus) && esHippie(vec1)  )
          {
             Nombre name = grilla.Obtener(vec1).tag ;
             (_hippies).Borrar( name );
             grilla.Obtener(vec1).id = 4;
             grilla.Obtener(vec1).tag = "";
             grilla.Obtener(vec1).placa = 0 ;
             diccHash<Agente,Datos>::Iterador itVacioHash;
             grilla.Obtener(vec1).datosAgente =itVacioHash;
             Conj<Posicion>::Iterador itVecVec = (_campus.Vecinos(vec1)).CrearIt() ;
             while( itVecVec.HaySiguiente() )
             {
                 Posicion posVec= itVecVec.Siguiente();
                 if( esAgente(posVec) )
                 {
                     diccHash<Agente,Datos>::Iterador itH = grilla.Obtener(posVec).datosAgente;
                     itH.SiguienteSignificado().hippiesAtrapados++;
                     actualizarMasVigilante(itH,posVec);
                 }
               itVecVec.Avanzar();
             }
          }
          else
          {
            if( posCapturable(vec1,_campus) && esEstudiante(vec1)  )
            {
              Nombre name = grilla.Obtener(vec1).tag ;
              Conj<Posicion> VecinosDe_vecinosDeVecino = DameCampus().Vecinos(vec1);
              Conj<Posicion>::Iterador itVecVec = VecinosDe_vecinosDeVecino.CrearIt();
              while( itVecVec.HaySiguiente() )
              {
                 Posicion posVec = itVecVec.Siguiente();
                 if( esAgente(posVec) )
                 {
                    //diccHash<Agente,Datos>::Iterador itH = grilla.Obtener(posVec).datosAgente;
                    //itH.SiguienteSignificado().Sanciones++;
                    Agente ac = grilla.Obtener(posVec).placa;
                    datosAgentes.Obtener(ac).Sanciones ++;
                    //Nat san = itH.SiguienteSignificado().Sanciones;
                    //ConjsEqu<Agente>::Iterador itMSanciones =  itH.SiguienteSignificado().claseConMismasSanciones;
                    //itMSanciones.ItActualizarElem(san);
                 }
                 itVecVec.Avanzar();
              }
            }
          }
        }
        /*
        itVecinosVec.Avanzar();
    }
    */
   itVecinos.Avanzar();
 }
}

/*
//Que es esta porquería?:
 void campusSeguro::actualizarVecinos(Posicion p){
    //actualizarEstYHippie(_campus.Vecinos(p));
    actualizarDatosAgentes(_campus.Vecinos(p));
    Conj<Posicion> paux;
    paux.AgregarRapido(p);
    matarHippies(paux);
    matarHippies(_campus.Vecinos(p));
 }
*/

void campusSeguro::actualizarEstYHippie(Conj<Posicion> c)
{
    Posicion posActual;
    Conj<Posicion>::Iterador it = c.CrearIt();
    while( it.HaySiguiente() )
    {
        posActual = it.Siguiente();
        if( posConvertibleAHippie(posActual,_campus) && esEstudiante(posActual) )
        {
            grilla.Obtener(posActual).id = 2;
            (_estudiantes).Borrar( grilla.Obtener(posActual).tag );
            (_hippies).Definir( grilla.Obtener(posActual).tag, posActual );
        }
        else
        {
            if( posConvertibleAEstudiante(posActual,_campus) && esHippie(posActual) )
            {
                grilla.Obtener(posActual).id = 1;
                (_hippies).Borrar( grilla.Obtener(posActual).tag );
                (_estudiantes).Definir( grilla.Obtener(posActual).tag , posActual );
            }
        }

        it.Avanzar();
    }

}


void campusSeguro::matarHippies(Conj<Posicion> c)
{
Posicion posActual;
Conj<Posicion>::Iterador it = c.CrearIt();
while( it.HaySiguiente() )
{
    posActual = it.Siguiente();
    if( posCapturable(posActual,_campus) && esHippie(posActual) )
    {
      grilla.Obtener(posActual).id = 4;
      (_hippies).Borrar( grilla.Obtener(posActual).tag );
      }
    it.Avanzar();
    }
}

//Posicion campusSeguro::proxPosicion(Posicion p,Conj<Posicion>::Iterador itPos)
Posicion campusSeguro::proxPosicion(Posicion p,DiccPalabra<Posicion>::itDiccP itPos)
{
    Posicion posMasCerca=itPos.SiguienteSignificado();
    Nat distActual = _campus.Distancia(p,posMasCerca);
    while( itPos.HaySiguiente() )
    {
        if( _campus.Distancia(p,itPos.SiguienteSignificado()) < distActual )
        {
            posMasCerca=itPos.SiguienteSignificado();
            distActual=_campus.Distancia(p,posMasCerca);
        }
    itPos.Avanzar();
    }
    Conj<Posicion> vecinos = _campus.Vecinos(p);
    Conj<Posicion>::Iterador itVecinos = vecinos.CrearIt();

    Posicion sigPos = p;
    while( itVecinos.HaySiguiente() )
    {
        Posicion vec = itVecinos.Siguiente();
        if( _campus.Distancia(vec,posMasCerca) < _campus.Distancia(p,posMasCerca) && (grilla.Obtener(vec)).id==4  ) // la grilla el campo id es de DatosPos
        {
            sigPos=vec;
        }
        itVecinos.Avanzar();
    }

    return sigPos;
}






