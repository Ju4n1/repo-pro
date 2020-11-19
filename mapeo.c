#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

int (*funcion_hash) (void *);
int (*funcion_comp)(tClave c1,tClave c2);
void (*fEliminar_clave)(void *);
void (*fEliminar_valor)(void *);

/**
 Este eliminar parese redundante, pero se usa en el reHash para poder recurrir al eliminar de lista
 con la tabla hash, destruyendo las celdas pero no su contenido, el cual es reinsertado en la nueva tabla
 de dimensiones apropiadas al factor de escala
**/
void fNoEliminar(tElemento e){}

/** Elimina el valor y la clave de una entrada dada, mediante las funciones fEliminar_clave y fEliminar_valor
**/

void fEliminarEntrada(tElemento e){
    tEntrada entrada= (tEntrada)e;

    fEliminar_clave(entrada->clave);
    fEliminar_valor (entrada->valor);

    free (entrada);
    entrada= NULL;
    }

    /**
    Dado dos volores enteros retorna el mayor.
    **/

    static int max(int x, int y){
    return (x>y) ? x : y;}

/**
 Inicializa un mapeo vac�o, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves ser� computado mediante la funci�n fHash.
 A todo efecto, la comparaci�n de claves se realizar� mediante la funci�n fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){

        int maximo= max(10, ci);

        //reservo memporia del mapeo y chequeo la misma
        *m =(tMapeo)malloc(sizeof(struct mapeo));
        if(*m==NULL)
            exit (MAP_ERROR_MEMORIA);

         //creo la tabla y la incializo con filas vacias
         tLista *buckets = (tLista*) malloc(sizeof(tLista) * maximo);
         for(int i=0;i<maximo;i++)
               crear_lista(&(buckets[i]));

           //asigno valores iniciales al mapeo
          (*m)->tabla_hash= buckets;
          (*m)->cantidad_elementos=0;
          (*m)->longitud_tabla= maximo;
          (*m)->comparador= fComparacion;
          (*m)->hash_code= fHash;


        }


/**
   El rehash recalcula las distrubuciones de claves en una tabla del doble de tamaño
**/
void reHash(tMapeo m){

    int long_nueva=m->longitud_tabla*2;

    //creo nueva tabla y chequeo reserva memoria
    tLista * nueva_tabla=(tLista*) malloc(sizeof(tLista) * long_nueva);
    if(nueva_tabla==NULL)
       exit(MAP_ERROR_MEMORIA);

    for(int i=0;i<long_nueva;i++)
       crear_lista(&nueva_tabla[i]);//inicializo la tabla vacia


    //preparo para recorrer tabla original
    tLista* tabla_original=m->tabla_hash;
    tLista lista_actual;

    for(int j=0;j<m->longitud_tabla;j++){ //para cada fila hago

             lista_actual=tabla_original[j];
             tPosicion pos_original=l_primera(lista_actual);
             tPosicion fin=l_fin(lista_actual);

             while(pos_original!=fin){ //copio todas los elementos de la fila en la fila correspondiente de la tabla nueva
                   tEntrada entrada=(tEntrada)l_recuperar(lista_actual,pos_original);
                   int h=(m->hash_code(entrada->clave))% long_nueva;
                   l_insertar(nueva_tabla[h],l_primera(nueva_tabla[h]),entrada);
                   pos_original=l_siguiente(lista_actual,pos_original);
                                     }
            l_destruir(&lista_actual,&fNoEliminar);//destruyo la fila copiada



    }

m->longitud_tabla*=2; //altualizo la longitud
free(m->tabla_hash); //libero espacio ocupado por tabla anterior
m->tabla_hash=nueva_tabla; //asigno la nueva tabla

}


/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no exist�a en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

tValor m_insertar(tMapeo m, tClave c, tValor v){
    tEntrada entrada;
    tValor valorRet=NULL;
    tPosicion posActual, posFin;
    int encontre=0;

    //calculo la fila donde voy a insertar
    int i =m->hash_code(c)%(m->longitud_tabla);
    tLista lista= m->tabla_hash[i];

    posActual= l_primera(lista);
    posFin= l_fin(lista);

    while(!encontre&& posActual!= posFin){
            entrada= l_recuperar(lista, posActual);

            if ( m->comparador(c, entrada->clave) == 0 )
                {//encontre, modifico el valor existente sin incrementar cantidad de elementos porque reemplacé un valor
                 encontre=1;
                 valorRet= entrada->valor;
                 entrada->valor= v;}
            else
                posActual= l_siguiente(lista, posActual);

                }
            if (!encontre){

                 //creo y verifico entrada
                 entrada= (tEntrada)malloc(sizeof(struct entrada));
                 if (entrada == NULL)
                     exit(MAP_ERROR_MEMORIA);

                 entrada->clave= c;
                 entrada->valor= v;
                 //inserto la entrada en la tabla y en este caso debo incrementar cantidad de elementos
                 l_insertar(lista,l_primera(lista), entrada);
                 m->cantidad_elementos++;

                 if(((float)m->cantidad_elementos/(float)m->longitud_tabla) >= 0.75)//de ser necesario agrando la tabla
                   reHash(m);

            }


return valorRet;}





/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    int i =m->hash_code(c)%(m->longitud_tabla);//calculo la fila en la que voy a eliminar
    tLista lista = m->tabla_hash[i];
    tPosicion posActual, posFin;
    tEntrada entrada;
    int encontre = 0;

    posActual= l_primera(lista);
    posFin= l_fin(lista);

    fEliminar_clave = fEliminarC;
    fEliminar_valor= fEliminarV;

    if(l_longitud(lista)!=0)//si la fila está vacia no puedo recuperar

         while(!encontre&& posActual!= posFin){
              entrada = (tEntrada) l_recuperar(lista, posActual);

              if (m->comparador (c, entrada->clave )== 0)

                 {l_eliminar(lista, posActual, &fEliminarEntrada);//elimino de la tabla

                  //elimino punteros
                  entrada->clave=NULL;
                  entrada->valor=NULL;


                  m->cantidad_elementos--;
                  encontre=1;} //salgo del ciclo con encontre

              else
                  posActual= l_siguiente(lista, posActual);}

}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo *m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    fEliminar_clave = fEliminarC;
    fEliminar_valor = fEliminarV;
    tLista bucket;

    for (int i = 0; i < ((*m)->longitud_tabla); i++){
        bucket = ((*m)->tabla_hash[i]);
        l_destruir(&bucket, &fEliminarEntrada);} //destruyo una a una las filas de la tabla

    free(((*m)->tabla_hash));//libero la memoria donde se amlacena la tabla

    //Elimino todos los punteros
    (*m)->tabla_hash = NULL;
    (*m)->hash_code=NULL;
    (*m)->comparador=NULL;
    (*m)->longitud_tabla=NULL;
    (*m)->cantidad_elementos=NULL;

    free(*m);//libero memoria que ocupa mapeo
    *m = NULL;//elimuno el puntero a mapeo
}


/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/

tValor m_recuperar(tMapeo m, tClave c){

    tValor valorRet=NULL;

    //determina la fila en la que corresponde buscar
    int i = m->hash_code(c)%(m->longitud_tabla);
    tLista lista = m->tabla_hash[i];

    tPosicion posActual, posFin;
    tEntrada entrada=NULL;
    int encontre=0;

   if(l_longitud(lista)!=0)//si la fila está vacia no puedo recuperar

    {
     posActual=l_primera(lista);
     posFin=l_fin(lista);

     while(posActual!= posFin&&!encontre){ //recorro hasta encontrar o llegar al final de la fila

          entrada=(tEntrada)l_recuperar(lista,posActual);

          if  (m->comparador(c, entrada->clave)==0)
                 {valorRet= entrada->valor;//si encuentro recupero valor
                  encontre=1;} //uso encontre para salir del ciclo
            else
                 posActual= l_siguiente(lista, posActual);} //no encontre sigo buscando.
     }

return valorRet;}



