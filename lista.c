#include <stdio.h>
#include <stdlib.h>
#include "lista.h"



/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l) {
    (*l) = (tLista) malloc(sizeof(struct celda));
    if ((*l) == NULL)
        exit(LST_ERROR_MEMORIA);
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e) {

	if (p==NULL)//verifico que sea un posición válida
        exit(LST_POSICION_INVALIDA);

    tPosicion posNuevaCelda = (tPosicion) malloc(sizeof(struct celda));//reservo memoria

	if (posNuevaCelda == NULL)//verifico que se haya creado bien
        exit(LST_ERROR_MEMORIA);

	//seto los parametros, la referencia al siguiente y del anterior a el
    posNuevaCelda->elemento = e;
    posNuevaCelda->siguiente = p->siguiente;
    p->siguiente = posNuevaCelda;
}

/**
 Elimina el nodo que se encuentra en la posición P de L.
 El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {

    //Checkeo pos a eliminar
    if(p==NULL || p == l_fin(l))
        exit(LST_POSICION_INVALIDA);

    tPosicion aux;
    aux = p->siguiente;
    p->siguiente = aux->siguiente;
    aux->siguiente = NULL;
    fEliminar(aux->elemento);  //borro el elemento usando la funcion por parametro
    free(aux);
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){
    tPosicion pos = *l;
    tPosicion aux = pos;


	//recorre la lista eliminando posición por posicion y tambien el contenido de las misma
    while(pos->siguiente!= NULL){
        aux = aux->siguiente;
        fEliminar(pos->elemento);
        free(pos);
        pos = aux;
    }
    *l = NULL;
}

/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p) {
    if(p==NULL || p == l_fin(l))
        exit(LST_POSICION_INVALIDA);
    //elemento apuntado por P es siguiente de P
    return (p->siguiente)->elemento;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){
    return l;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p) {

    //chequeo que la posicion sean válida
    if(p==NULL)
        exit(LST_POSICION_INVALIDA);

    //no podes pedir siguiente a a fin
    if(p==l_fin(l))
        exit(LST_NO_EXISTE_SIGUIENTE);

    return p->siguiente;}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p) {

    if(p==NULL)
        exit(LST_POSICION_INVALIDA);

    if(p==l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion pos = l;

    while(pos->siguiente != p)
         pos = pos->siguiente;

return pos;}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l) {
    tPosicion pos = l;

    if(l->siguiente!=NULL)//la lista esta vacia, primera = ultima = fin

        while(((pos->siguiente)->siguiente) != NULL)
              pos = pos->siguiente;


    return pos;}

/**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l) {
      tPosicion pos = l;

      while(pos->siguiente!=NULL)
            pos = pos->siguiente;//recorro las poasdiciones te tienen un elemento

return pos;}

/**
 Metodo que devuelve la longitud de la lista lista.
**/
int l_longitud(tLista l) {

    int contador = 0;

    if(l_primera(l) != l_fin(l)) //si no tiene elementos

       {tPosicion pos = l->siguiente;
        while(pos != NULL){
            pos = pos->siguiente;
            contador++;}
            }
return contador;}








