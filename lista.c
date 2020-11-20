#include <stdio.h>
#include <stdlib.h>
#include "lista.h"



/**
 Inicializa una lista vac�a.
 Una referencia a la lista creada es referenciada en *L.
**/
void crear_lista(tLista * l) {

    (*l) = (tLista) malloc(sizeof(struct celda));// reservo la memoria para l

    if ((*l) == NULL) //chequeo que la operaci�n anterior haya sido exitosa
        exit(LST_ERROR_MEMORIA);

     // lista vac�a
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Inserta el elemento E, en la posici�n P, en L.
 Con L = A,B,C,D y la posici�n P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e) {

	if (p==NULL) //verifico que tanto la posici�n sea v�lida, obs se asume que la lista si va a ser v�lida
        exit(LST_POSICION_INVALIDA);

    tPosicion posNuevaCelda = (tPosicion) malloc(sizeof(struct celda)); //reservo la memoria que va a ocupar la nueva posicion

	if (posNuevaCelda == NULL)//verifico que se haya reservado la memoria
        exit(LST_ERROR_MEMORIA);

	//seteo todos los par�metros de la nueva posicion incluyendo la referencia al siguiente y la del anterior hacia a el
    posNuevaCelda->elemento = e;
    posNuevaCelda->siguiente = p->siguiente;
    p->siguiente = posNuevaCelda;
}

/**
 Elimina el nodo que se encuentra en la posici�n P de L.
 El elemento almacenado en la posici�n P es eliminado mediante la funci�n fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)) {

    //Chequeo pos a eliminar sea v�lida
    if(p->siguiente==NULL)
          exit(LST_POSICION_INVALIDA);


    tPosicion aux= p->siguiente; //variable auxiliar para guardar pos a eliminar

    p->siguiente = aux->siguiente; //actualizo el puntero anterior para que apunte al nuevo siguiente

    fEliminar(aux->elemento); //uso la funci�n fEliminar para eliminar el contenido de la posicion

    //una vez eliminada la posicion, no debe quedar nada referenciando la misma, ya sea un elemento o una posicion siguiente, por lo que hago nulo los punteros
    aux->elemento=NULL;
    aux->siguiente = NULL;


    free(aux);// libero el espacio que ocupa la posici�n eliminada
}

/**
 Destruye la lista L, elimininando cada una de sus posiciones. Los elementos almacenados en las posiciones son eliminados mediante la funci�n fEliminar parametrizada.
**/
void l_destruir(tLista * l, void (*fEliminar)(tElemento)){

    //Me paro en la posicion que deberia tener elementos en caso de tener
    tPosicion pos = (*l)->siguiente;
    tPosicion aux;

	//recorro la listas mientras tenga elementos
    while(pos!= NULL){
         
		 aux=pos->siguiente;//salvo siguiete para la proxima vuelta del ciclo
         
		 //elimino elemento en posicion con la funci�n pasada por par�metros, y hago que sus punteros no apunten a nada
         fEliminar(pos->elemento);
         pos->elemento=NULL;
         pos->siguiente=NULL;
         
		 free(pos);//lebero la memoria que ocupa pos
         
		 
         pos=aux;//actualizo el valor de posicion al siguiente
         }


free(*l); //libero es espacio que ocupa el puntero a lista
*l = NULL; //elimino el puntero a lista
}

/**
 Recupera y retorna el elemento en la posici�n P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p) {

      if(p==NULL || p == l_fin(l))// chequeo que la posicion sea v�lida, y controlo que esta no sea fin
          exit(LST_POSICION_INVALIDA);

//retorno elemento apuntado por p
return (p->siguiente)->elemento;}

/**
 Recupera y retorna la primera posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){
//primera retorna el centinela
return l;}

/**
 Recupera y retorna la posici�n siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p) {


    if(p->siguiente==NULL) //esto se cumple cuando p es fin 
        exit(LST_NO_EXISTE_SIGUIENTE);

return p->siguiente;}

/**
 Recupera y retorna la posici�n anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p) {

    if(p==l_primera(l))//no existe una posici�n anterior a primera, se asume que la posicion pasada es v�lida
        exit(LST_NO_EXISTE_ANTERIOR);

    tPosicion pos = l;

    // cuando el siguiente de pos coincide con p significa que estoy parado en el anterior a p, de los contrario debo seguir avanzando.
    while(pos->siguiente != p)
         pos = pos->siguiente;

return pos;}

/**
 Recupera y retorna la �ltima posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l) {

    tPosicion pos = l;
    if(l->siguiente!=NULL)//la lista esta vac�a, primera = ultima = fin

        //crecorro hasta estar parado en la posici�n que apunta a fin, es decir cuando el siguiente del siguiente de pos, sea nulo
        while(((pos->siguiente)->siguiente) != NULL)
              pos = pos->siguiente;


    return pos;}

/**
 Recupera y retorna la posici�n fin de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l) {

      tPosicion pos = l; //pos es primera.
      while(pos->siguiente!=NULL) //cuando el siguiente de pos es un nulo, es porque pos coincide con fin
            pos = pos->siguiente;

return pos;}

/**
 Metodo que devuelve la longitud de la lista lista.
**/
int l_longitud(tLista l) {

    int contador = 0; // inicialmente la lista se encuentra vacia

    if(l_primera(l) != l_fin(l)) //si la lista tiene elementos los cuento

       {
        tPosicion pos = l->siguiente;//me paro en el primer elemento en caso de tenerlo porque el centinela no se cuenta
        while(pos != NULL){
            pos = pos->siguiente;
            contador++;}
        }
return contador;}








