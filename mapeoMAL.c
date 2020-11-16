#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//----------------------------------------Constructor--------------------------------------------------------

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){


        // Crea la tabla vacía
        tLista lista;
        crear_lista(&lista);

        //reservo memporia del mapeo
        * m=(tMapeo)malloc(sizeof(struct mapeo));
        if(m==NULL)
            exit (MAP_ERROR_MEMORIA);


        if (ci<10)
           ci=10;

        //asigno parametros de un mapeo vacio
        (*m)->cantidad_elementos=0;
        (*m)->tabla_hash=lista;
        (*m)->longitud_tabla=0;


        funcion_hash=fHash;
        funcion_comp=fComparacion;

        if (ci<10)
           ci=10;

        //inicializo la tabla con 10 filas o más
        while ((*m)->longitud_tabla!=ci){
                (*m)->longitud_tabla++;
                tLista l;
                crear_lista(&l);
                //creo una fila nueva, vacia en la tabla, insertando una lista
                l_insertar((tLista)(*m)->tabla_hash,l_fin((tLista)(*m)->tabla_hash),l);


                                       }
}


/**
   El rehash recalcula las distrubuciones de claves en una tabla del doble de tamaño
**/
void rehash(tMapeo m){}

//----------------------------------------Funciones propias de la estructura mapeo--------------------------------------------------
tValor m_insertar(tMapeo m, tClave c, tValor v){

    tValor salida=NULL;

    //reservo espacio entradas
    tEntrada e=(tEntrada)malloc(sizeof(tEntrada));

    if(e==NULL)
      exit (MAP_ERROR_MEMORIA);


   if((float)(m->cantidad_elementos)/(float)(m->longitud_tabla)>0.9)
      rehash(m);


    //seteo clave/valor
    e->clave=c;
    e->valor=v;

    //h nos dice a que fila vamos a insertar
    int h=funcion_hash(c)%m->longitud_tabla;


   tLista tabla=(tLista)m->tabla_hash;
   tPosicion posEnTabla=l_primera(tabla);// pos aputan a la fila 0

   //busco la posicion que le corresponde en la tabla
   int cont=0;

   //camino por las filas hasta la correcta
   while(cont!=h){
        posEnTabla=l_siguiente((tLista)m->tabla_hash,posEnTabla);
        cont++;}

   tLista insertar=posEnTabla->elemento;
   tPosicion posIns=l_primera(insertar);

   if(l_longitud(insertar)==0)
      {l_insertar(insertar,posIns,e);
       m->cantidad_elementos++;}


   else{
       //recorro la fila mientra la clave nueva sea menor que el resto
       while((funcion_comp(e->clave,((tEntrada)l_recuperar(insertar,posIns))->clave)<0)&&(posIns!=l_ultima(insertar))){
              posIns=l_siguiente(insertar,posIns);}

       //inserto la nueva entrada si
       if (funcion_comp(e->clave,((tEntrada)l_recuperar(insertar,posIns))->clave)==0) //la clave ya esta debo reemplazar sin sumar entrada

           {
               salida=(((tEntrada)l_recuperar(insertar,posIns))->valor);
            posIns->elemento=e;}//se cambia el valor de la entrada

       else {
             l_insertar(insertar,posIns,e);//hay una clave mayor, inserto antes
             m->cantidad_elementos++;//ahora si incremento cantodad elementos
             }
          }


return salida;}

tValor m_recuperar(tMapeo m, tClave c){

         //no puedo recuperar de un mapeo vacio
         if(m==NULL)
         exit(MAP_ERROR_MEMORIA);

tValor salida=NULL;



   //busco la posicion que le corresponde en la tabla
   if(m->cantidad_elementos!=0)

   {
   int h=funcion_hash(c)%m->longitud_tabla;
   tLista tabla=(tLista)m->tabla_hash;
   tPosicion posTabla=l_primera(tabla);

   int cont=0;

   while(cont!=h){
        posTabla=l_siguiente(tabla,posTabla);
        cont++;}

   //buco en la fila correspondiente
   tLista buscar=posTabla->elemento;
   tPosicion posFila=l_primera(buscar)->siguiente;


     if(l_primera(buscar)!=l_fin(buscar))//la fila no está vacia
      //recorro la fila mientra la clave nueva sea menor que el resto
         {
             while ((posFila!=l_fin(buscar))&&(funcion_comp(c,((tEntrada)(posFila)->elemento)->clave)<0))
                     posFila=l_siguiente(buscar,posFila);




  if ((funcion_comp(c,((tEntrada)(posFila)->elemento)->clave)==0)) //encontre clave
        salida=((tEntrada)(posFila->elemento))->valor;}

  }

return salida;}


void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

fEliminarClave = fEliminarC;
fEliminarValor = fEliminarV;


int h=funcion_hash(c)%m->longitud_tabla;

tPosicion posTabla=(tPosicion)l_primera((tLista)m->tabla_hash);


  //busco la posicion que le corresponde en la tabla
   int cont=0;

   while(cont!=h){
        posTabla=l_siguiente((tLista)m->tabla_hash,posTabla);
        cont++;}

   //buco en la fila correspondiente
   tLista buscar=posTabla->elemento;
   tPosicion posFila=buscar;
   if (l_longitud(buscar)!=0)

    {

      //recorro la fila mientra la clave nueva sea menor que el resto
       while ((posFila!=l_ultima(buscar))&&(funcion_comp(c,((tEntrada)l_recuperar(buscar,posFila))->clave)<0))
                {posFila=l_siguiente(buscar,posFila);}

   if (funcion_comp(((tEntrada)l_recuperar(buscar,posFila))->clave,c)==0)
         {//elimino el contenido de clave/valor
          fEliminarC(((tEntrada)l_recuperar(buscar,posFila))->clave);
          fEliminarV(((tEntrada)l_recuperar(buscar,posFila))->valor);

          //elimino la entrada de la tabla
          l_eliminar(buscar,posFila,&EliminarEntrada);
          m->cantidad_elementos--;}
          }
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




















