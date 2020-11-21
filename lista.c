#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l) {

     // Reservo la memoria de la lista, y compruebo que la operación se haya ralizado sin error.
    (*l) = (tLista) malloc(sizeof(struct celda));
     if ((*l) == NULL)
        exit(LST_ERROR_MEMORIA);

     // Lista vacía "centinela".
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e) {

	// Verifico que la posicion sea válida.
	if (p==NULL)
        exit(LST_POSICION_INVALIDA);

    // Reservo la memoria que ocupara la nueva posición, y cheque que la operacion no termine en error.
    tPosicion posNuevaCelda = (tPosicion) malloc(sizeof(struct celda));
    if (posNuevaCelda == NULL)
        exit(LST_ERROR_MEMORIA);

	// Se asignasn todos los valores correspondientes a la posición nueva.
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

    // Chequeo posición a eliminar sea válida
    if(p->siguiente==NULL)
          exit(LST_POSICION_INVALIDA);


    // Esta es la posición que tengo que eliminar.
    tPosicion aux= p->siguiente;

    // Cambio la referencia de la posicion anterior a la siguiente de p que eliminaré.
    p->siguiente = aux->siguiente;

    // Elimino el contenido de la posicón con fEliminar corto la referencia al siguiente y libero la memoria por último.
    fEliminar(aux->elemento);
    aux->siguiente = NULL;
    free(aux);
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la función fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    // Primera posición con elemente en caso de que exista y un auxiliar para el ciclo.
    tPosicion pos = (*l)->siguiente;
    tPosicion aux;

	// Recorro la listas mientras tenga elementos
    while(pos!= NULL){

         // Importante no perder la posición que destruiré en el próximo ciclo.
		 aux=pos->siguiente;

         // Elimino con la funacion, corto referencias y libero espacio como en eñliminar solo que ciclico.
         fEliminar(pos->elemento);
         pos->elemento=NULL;
         pos->siguiente=NULL;
         free(pos);

		 // Ahora puedo destruir la siguiente posición.
         pos=aux;
                      }

// Cuando todas la posiciones están destruidar, libero la memeria de lista y corto su referencia.
free(*l);
*l = NULL;
}

/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p) {

      // Para poder recuperar la posición tiene que ser distinta de fin.
      if(p == l_fin(l))
          exit(LST_POSICION_INVALIDA);

// Posición indirecta siempre recupera el elemento siguite al de la posición pasada por parámetros.
return (p->siguiente)->elemento;}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){

// Primera siempre es el centinela.
return l;}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p) {

     // Siguiente de fin no existe, se asume p válida.
    if(p==l_fin(l))
        exit(LST_NO_EXISTE_SIGUIENTE);

return p->siguiente;}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p) {

    // Anterior a primera no existe.
    if(p==l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion pos = l;

    // Cuando el siguiente de pos es igual a p, pos es el anterior.
    while(pos->siguiente != p)
         pos = pos->siguiente;

return pos;}

/**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l) {

    tPosicion pos = l;

    // Cuando la lista no está vacia puedo buscar ultima, sino primera=ultima=fin.
    if(l->siguiente!=NULL)

        // Cuando pos siguiente siguiente es nula, significa que estoy en la posicion que apunta a fin, en otras palabras última.
        while(((pos->siguiente)->siguiente) != NULL)
              pos = pos->siguiente;


return pos;}

/**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l) {
      // Importante pararse en primera porque si l está vacia primera=fin.
      tPosicion pos = l;

      //Cuando pos siguiente es nula estoy en fin.
      while(pos->siguiente!=NULL)
            pos = pos->siguiente;

return pos;}

/**
 Metodo que devuelve la longitud de la lista lista.
**/
int l_longitud(tLista l) {
    // Inicialmente la lista esta vacía.
    int contador = 0;

    // Si tiene elemento puedo  contarlos
    if(l_primera(l) != l_fin(l))
        {
        // Me muevo a la primera posición con elemento para no contar centinela y cuento hasta llegar a fin.
        tPosicion pos = l->siguiente;
        while(pos != NULL){
            pos = pos->siguiente;
            contador++;}
        }
return contador;}








