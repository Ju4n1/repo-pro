#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"
#include "mapeo.h"

/*-------------------------------funciones necesarias para las implementaciones-----------------------------------------------------*/
int (*funcion_hash) (void *);
int (*funcion_comp)(tClave c1,tClave c2);

void (*fEliminarClave)(void *);
void (*fEliminarValor)(void *);

/**
Defino una función eliminar en base a fEliminarClave y fEliminarValor de para ultilizar
en destruir y eliminar
**/
void EliminarEntrada(tElemento e1){
     tEntrada entrada = (tEntrada) e1;
     fEliminarClave(entrada->clave);
     fEliminarValor(entrada->valor);
     entrada = NULL;
     free(entrada);}

void fNoEliminar(tElemento e){}



//------------------------------------------------------------------------------------------------

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){


        // Tabla vacía
        tLista* lista=NULL;


        if(ci<10)
            ci=10;


        //reservo memporia del mapeo
        * m=(tMapeo)malloc(sizeof(struct mapeo));
        (*m)->tabla_hash=(tLista *) malloc(ci * sizeof(tLista));

        if(m==NULL)
            exit (MAP_ERROR_MEMORIA);


         //asigno parametros iniciales del mapeo vacio
        (*m)->cantidad_elementos=0;
        (*m)->tabla_hash=lista;
        (*m)->longitud_tabla=0;

        //ceteo las funciones por parametros para poder utilizarlas más adelante
        funcion_hash=fHash;
        funcion_comp=fComparacion;




        for(int i=0; i<ci; i++) //crea un lista "filas" como capacidad máxima de la  tabla hash "arreglo"
           crear_lista(&(*m)->tabla_hash[i]);

}



/**
   El rehash recalcula las distrubuciones de claves en una tabla del doble de tamaño
**/
void rehash(tMapeo m){

m->longitud_tabla *=2; //duplico el tamaño de la tabla
tLista * tabla_anterior = m->tabla_hash;

tLista * nuevaTabla=(tLista *) malloc(sizeof(tLista)*(m->longitud_tabla)); //creo una tabla nueva

 for(int i=0;i<m->longitud_tabla;i++)
       crear_lista(&(m->tabla_hash[i])); //genero cada una de las fila vacias de la tabla


 tLista lista_actual=NULL;

 for (int i = 0; i<m->longitud_tabla/2; i++){
          lista_actual = tabla_anterior[i];

          int longitud_lista = l_longitud(lista_actual);
          for(int j=0; j<longitud_lista;j++){

                  //recorro lista recuperando entrada y eliminando de la tabla anterior pero sin borrar elemento
                  tPosicion mi_posicion_actual = l_primera(lista_actual);
                  tEntrada mi_entrada_actual = l_recuperar(lista_actual, mi_posicion_actual);
                  l_eliminar(lista_actual, mi_posicion_actual, &fNoEliminar);//elimino la posicion pero mantengo la entrada

                  //recalculo hash e inserto en nueva tabla
                  int h=fabs((m)->hash_code(mi_entrada_actual->clave));
                  l_insertar(nuevaTabla[h],l_primera(nuevaTabla[h]),mi_entrada_actual);

                                            }
                                             }

}

//----------------------------------------Funciones propias de la estructura mapeo--------------------------------------------------
tValor m_insertar(tMapeo m, tClave c, tValor v){
tValor salida=NULL;


return salida;}

tValor m_recuperar(tMapeo m, tClave c){
tValor salida=NULL;


return salida;}


void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

fEliminarClave = fEliminarC;
fEliminarValor = fEliminarV;


//int h=funcion_hash(c)%m->longitud_tabla;


}

void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
    tMapeo mapeo = (*m);
    int capacidad = mapeo->longitud_tabla;
    tLista* fila_actual;
    fEliminarClave = fEliminarC;
    fEliminarValor = fEliminarV;
    int i=0;
    while( i<capacidad) //Elimina las filas 1X1.
                      {
        fila_actual = (tLista*) *((*m)->tabla_hash+i);
        if (((tLista*) *((*m)->tabla_hash+i))!=NULL)//destruye filas que tengan elementos
            {l_destruir((tLista*) fila_actual, &EliminarEntrada);}
             free(fila_actual);
                  i++;}

    free(*m);
    (*m)=NULL;
}




















