#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

void fEliminar(tElemento e){
    e=NULL;
    free(e);}

//la lista debe existir para mostrarla
void mostrar(tLista l){

    if(l_longitud(l)==0)
       printf("la lista esta vacia \n");
       else
           { tPosicion pos=l; //primer posicion no NULL de la lista
             while(pos!=l_fin(l)){

                   printf(" %d",l_recuperar(l,pos));
                   pos=pos->siguiente;}

           }

  printf("\n");}



void probarLista(){


tLista l;
crear_lista(&l);

printf("muestro la lista \n");

mostrar(l);

printf("muestro la longitud de l : %d\n ",l_longitud(l));


printf("inserto 1,2,3,5 en fin \n");

l_insertar(l,l_primera(l),1);

l_insertar(l,l_fin(l),2);

l_insertar(l,l_fin(l),3);

l_insertar(l,l_fin(l),5);

mostrar(l);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

printf("inserto 4 en ultima \n");

l_insertar(l,l_ultima(l),4);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

mostrar(l);

printf("inserto 9 en primera \n");

l_insertar(l,l_primera(l),9);

printf("muestro la longitud de l : %d\n ",l_longitud(l));

mostrar(l);

tPosicion pos=l;

printf(" muestro primera como l_primera(l)->elemento 'NULL': %d\n",pos->elemento);

printf(" muestro ultima como l_ultima(l)->elemento : %d\n",l_ultima(l)->elemento);

printf(" muestro fin como l_fin(l)->elemento : %d\n",l_fin(l)->elemento);

printf(" recupero primera: %d\n",l_recuperar(l,l_primera(l)));

printf(" recupero ultima: %d\n",l_recuperar(l,l_ultima(l)));

printf(" recupero anterior ultima '3' -> '4' : %d\n",l_recuperar(l,l_anterior(l,l_ultima(l))));

printf(" recupero siguiente a primera '9' -> '1' : %d\n",l_recuperar(l,l_siguiente(l,l_primera(l))));

printf(" elimino primera '9' :");

l_eliminar(l,l_primera(l),&fEliminar);

mostrar(l);

printf(" elimino ultima '5' :");

l_eliminar(l,l_ultima(l),&fEliminar);

mostrar(l);

printf(" elimino 2 como siguiente de primera :");

l_eliminar(l,l_primera(l)->siguiente,&fEliminar);

mostrar(l);

printf(" muestro fin: %d \n",l_recuperar(l,l_ultima(l)));

printf("destruyo la lista");
l_destruir(&l,&fEliminar);

}

int main(int argc,char* argv[]){

  
probarLista();


return 0;}

