#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

// Funciones que recibo por parámetros y uso en fEliminarEntrada.
void (*fEliminar_clave)(void *);
void (*fEliminar_valor)(void *);

/**
 Este eliminar parese redundante, pero se usa en el reHash para poder recurrir al eliminar de lista
 con la tabla hash, destruyendo las celdas pero no su contenido, el cual es reinsertado en la nueva tabla
 de dimensiones apropiadas al factor de escala.
**/
void fNoEliminar(tElemento e){}

/**
 Elimina el valor y la clave de una entrada dada, mediante las funciones fEliminar_clave y fEliminar_valor.
 Libera la memoria que ocupa tanto clave como valor.
**/

void fEliminarEntrada(tElemento e){
    tEntrada entrada= (tEntrada)e;

    fEliminar_clave(entrada->clave);
    fEliminar_valor (entrada->valor);

    free (entrada);
    entrada= NULL;
    }

/**
 Funación max retorna el entero mayor de los dos pasados por parámetros.
 Se usa en crear mapeo, para determinar el tamaño inicial de la tabla.
**/

    static int max(int x, int y){
    return (x>y) ? x : y;}

/**
 Inicializa un mapeo vacío, con capacidad inicial igual al MAX(10, CI).
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

         //Reservo memoria para la tabla, chequeo que se reserve sin error, y la inicializo
         tLista *buckets = (tLista*) malloc(sizeof(tLista) * maximo);
         if(buckets==NULL)
             exit (MAP_ERROR_MEMORIA);

         for(int i=0;i<maximo;i++)
               crear_lista(&(buckets[i]));

           // Asigno tanto los valores iniciales de mapeo como sus funciones comparar y hash.
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

    // Reservo la memoria para la tabla, chequeo  dicha reserva y la inicializo la tabla.
    tLista * nueva_tabla=(tLista*) malloc(sizeof(tLista) * long_nueva);
    if(nueva_tabla==NULL)
       exit(MAP_ERROR_MEMORIA);

    for(int i=0;i<long_nueva;i++)
       crear_lista(&nueva_tabla[i]);//inicializo la tabla vacia


    // Recorro tabla original moviendo las entradas a una tabla nueva.
    tLista* tabla_original=m->tabla_hash;
    tLista lista_actual;

    for(int j=0;j<m->longitud_tabla;j++){

             lista_actual=tabla_original[j];
             tPosicion pos_original=l_primera(lista_actual);
             tPosicion fin=l_fin(lista_actual);
             tEntrada entrada;

             // Copio una fila completa a la tabla nueva y luego destruyo la fila de la tabla original.
             while(pos_original!=fin){
                     entrada=(tEntrada)l_recuperar(lista_actual,pos_original);
                     int h=(m->hash_code(entrada->clave))% long_nueva;
                     l_insertar(nueva_tabla[h],l_primera(nueva_tabla[h]),entrada);
                     pos_original=l_siguiente(lista_actual,pos_original);
                                     }
            l_destruir(&lista_actual,&fNoEliminar);//Destruyo fila, pero no las entradas que contie.



    }
// Elimino la tabla original que no tiene filas y asigno la nueva tabla y su longitud nueva.
m->longitud_tabla=long_nueva;
free(m->tabla_hash);
m->tabla_hash=nueva_tabla;

}


/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no exist�a en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

tValor m_insertar(tMapeo m, tClave c, tValor v){

    // Variables de recorrido.
    tEntrada entrada;
    tValor valorRet=NULL;
    tPosicion posActual, posFin;
    int encontre=0;

    // Calculo la fila donde voy a insertar, la recupero.
    int i =m->hash_code(c)%(m->longitud_tabla);
    tLista lista= m->tabla_hash[i];

    posActual= l_primera(lista);
    posFin= l_fin(lista);

    // Busco en la fila correspondiente.
    while(!encontre&& posActual!= posFin){

            entrada= l_recuperar(lista, posActual);

            // Encontre entrada asi que modifico solo su valor.
            if ( m->comparador(c, entrada->clave) == 0 )
                {
                 encontre=1;
                 valorRet= entrada->valor;
                 entrada->valor= v;}
            else
                posActual= l_siguiente(lista, posActual);
    }

            if (!encontre){

                 // Reservo la memoria para la nueva entrada, chequeo la operación, seteo clave valor e inserto en tabla incrementando cantiodad elementos.
                 entrada= (tEntrada)malloc(sizeof(struct entrada));
                 if (entrada == NULL)
                     exit(MAP_ERROR_MEMORIA);

                 entrada->clave= c;
                 entrada->valor= v;

                 l_insertar(lista,l_primera(lista), entrada);
                 m->cantidad_elementos++;

                 // Verifico el factor de carga, el cual indica si debo agrandar la tabla para que la distribución de entradas por fila sea óptima.
                 if(((float)m->cantidad_elementos/(float)m->longitud_tabla) >= 0.75)
                   reHash(m);

            }


return valorRet;}



/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    // Calculo la fila de la tabla y preparo variables de recorrido.
    int i =m->hash_code(c)%(m->longitud_tabla);
    tLista lista = m->tabla_hash[i];
    tPosicion posActual, posFin;
    tEntrada entrada;
    int encontre = 0;

    posActual= l_primera(lista);
    posFin= l_fin(lista);

    // Con esta operación unifico los fEliminarC y fEliminarV en un fEliminarEntrada
    fEliminar_clave = fEliminarC;
    fEliminar_valor= fEliminarV;

    // No es necesario eliminar de una fila vacía.
    if(l_longitud(lista)!=0)

         //Recorro hasta encontrar o finalizar fila
         while(!encontre&& posActual!= posFin){
              entrada = (tEntrada) l_recuperar(lista, posActual);

              if (m->comparador (c, entrada->clave )== 0)

                   // Encontre la entrada, la elimino con la funacion fEliminarEntrada, corto la referencias de punteros, decremento cantidad elemento y salgo del bucle.
                  {l_eliminar(lista, posActual, &fEliminarEntrada);
                   entrada->clave=NULL;
                   entrada->valor=NULL;
                   m->cantidad_elementos--;
                   encontre=1;}

              else
                  posActual= l_siguiente(lista, posActual);}

}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo *m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    // Unifico los fEliminarC y fEliminarV en un fEliminarEntrada
    fEliminar_clave = fEliminarC;
    fEliminar_valor = fEliminarV;

    tLista bucket;

    // Recorro la tabla destruyendo fila por fila y libero el espacio de memoria que esta ocupa.
    for (int i = 0; i < ((*m)->longitud_tabla); i++){
        bucket = ((*m)->tabla_hash[i]);
        l_destruir(&bucket, &fEliminarEntrada);}

    free(((*m)->tabla_hash));

    // Corto las referencia de los punteroas de mapeo, libero la memoria que este ocupa, y elimino su puntero.
    (*m)->tabla_hash = NULL;
    (*m)->hash_code=NULL;
    (*m)->comparador=NULL;
    free(*m);
    *m = NULL;
}


/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/

tValor m_recuperar(tMapeo m, tClave c){

    tValor valorRet=NULL;

    // Determino la fila en la que corresponde buscar y la recupero.
    int i = m->hash_code(c)%(m->longitud_tabla);
    tLista lista = m->tabla_hash[i];

    tPosicion posActual, posFin;
    tEntrada entrada=NULL;
    int encontre=0;

   // No es necesario recuperar de fila vacía.
   if(l_longitud(lista)!=0)
        {
         posActual=l_primera(lista);
         posFin=l_fin(lista);

         // Busco hasta encontrar o agotar elemento de la fila.
         while(posActual!= posFin&&!encontre){

                entrada=(tEntrada)l_recuperar(lista,posActual);
                if(m->comparador(c, entrada->clave)==0)
                      {valorRet= entrada->valor;
                       encontre=1;}
                else
                    posActual= l_siguiente(lista, posActual);} //no encontre sigo buscando.
          }

return valorRet;}


