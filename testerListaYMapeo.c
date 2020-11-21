#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"
void fEliminar(tElemento e){
   e=NULL;
   free(e);
   }

int fComparacion(void *e1, void *e2){

return strcmp((char*)e1,(char*)e2);}

void fEliminarC(tClave c1){
   c1=NULL;
   free(c1);}

void fEliminarV(tValor v1){
   v1=NULL;
   free(v1);}


int fHash(void *c){
    char *p=c;
    int hash = 0;
    int  d;
    while ((d = *p ++))
        hash += d;
    return fabs(hash);}



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


printf("\n");
printf("\n");
printf("################################################################################################\n");
printf("#######################################----PRUEBO LISTA----#####################################\n");
printf("################################################################################################\n");
printf("\n");
printf("\n");



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

printf("/////////-------->destruyo el lista<-----------------///////\n");
l_destruir(&l,&fEliminar);


printf("\n");
printf("\n");
printf("\n");
printf("\n");

printf("################################################################################################\n");
printf("#####################----TERMINE PRUEBA LISTA SIN ERROR----#####################################\n");
printf("################################################################################################\n");
printf("\n");
printf("\n");
printf("\n");
printf("\n");
}


void probarMapeo(){

printf("\n");
printf("\n");
printf("#################################################################################################\n");
printf("##############################----PRUEBO MAPEO----###############################################\n");
printf("#################################################################################################\n");
printf("\n");
tMapeo m;
crear_mapeo(&m,10,&fHash,fComparacion);

////////////////////////////////Entradas///////////////////////////////////////////
char* mi_clave1 = malloc(sizeof(char) * 5);
mi_clave1[0]='H';
mi_clave1[1]='o';
mi_clave1[2]='l';
mi_clave1[3]='a';
mi_clave1[4]='\0';

int * mi_valor1 = malloc(sizeof(int));
*mi_valor1 = 1;

char* mi_clave2 = malloc(sizeof(char) * 4);
mi_clave2[0]='H';
mi_clave2[1]='o';
mi_clave2[2]='l';
mi_clave2[3]='\0';

int * mi_valor2 = malloc(sizeof(int));
*mi_valor2 = 2;

char* mi_clave3 = malloc(sizeof(char) * 5);
mi_clave3[0]='P';
mi_clave3[1]='a';
mi_clave3[2]='p';
mi_clave3[3]='a';
mi_clave3[4]='\0';

int * mi_valor3 = malloc(sizeof(int));
*mi_valor3 = 3;

char* mi_clave4 = malloc(sizeof(char) * 5);
mi_clave4[0]='m';
mi_clave4[1]='a';
mi_clave4[2]='m';
mi_clave4[3]='a';
mi_clave4[4]='\0';

int * mi_valor4 = malloc(sizeof(int));
*mi_valor4 =4;

char* mi_clave5 = malloc(sizeof(char) * 5);
mi_clave5[0]='s';
mi_clave5[1]='a';
mi_clave5[2]='p';
mi_clave5[3]='o';
mi_clave5[4]='\0';

int * mi_valor5 = malloc(sizeof(int));
*mi_valor5 = 5;

char* mi_clave6 = malloc(sizeof(char) * 5);
mi_clave6[0]='j';
mi_clave6[1]='i';
mi_clave6[2]='j';
mi_clave6[3]='i';
mi_clave6[4]='\0';

int * mi_valor6 = malloc(sizeof(int));
*mi_valor6 = 6;

char* mi_clave7 = malloc(sizeof(char) * 5);
mi_clave7[0]='l';
mi_clave7[1]='o';
mi_clave7[2]='l';
mi_clave7[3]='a';
mi_clave7[4]='\0';

int * mi_valor7 = malloc(sizeof(int));
*mi_valor7 = 7;

char* mi_clave8 = malloc(sizeof(char) * 5);
mi_clave8[0]='a';
mi_clave8[1]='l';
mi_clave8[2]='o';
mi_clave8[3]='e';
mi_clave8[4]='\0';

int * mi_valor8 = malloc(sizeof(int));
*mi_valor8 = 8;

char* mi_clave9 = malloc(sizeof(char) * 5);
mi_clave9[0]='a';
mi_clave9[1]='l';
mi_clave9[2]='o';
mi_clave9[3]='e';
mi_clave9[4]='\0';


char* mi_clave10 = malloc(sizeof(char) * 5);
mi_clave10[0]='z';
mi_clave10[1]='z';
mi_clave10[2]='z';
mi_clave10[3]='z';
mi_clave10[4]='\0';
//////////////////////////////////////////Pruebpunciones antes de insertar////////////////////////////////

int * salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 mapeo vacio %d\n",salida);
printf("elimino c1 de un mapeo vacio n");
m_eliminar(m,mi_clave1,&fEliminarC,&fEliminarV);
printf("paso eliminar de vacio sin error \n");

///////////////////////////Pruebo el insertar u factor de escala////////////////////////////////
printf("inserto elementos \n");


m_insertar(m,mi_clave1,mi_valor1);
m_insertar(m,mi_clave2,mi_valor2);
m_insertar(m,mi_clave3,mi_valor3);
m_insertar(m,mi_clave4,mi_valor4);
m_insertar(m,mi_clave5,mi_valor5);
m_insertar(m,mi_clave6,mi_valor6);
m_insertar(m,mi_clave7,mi_valor7);
m_insertar(m,mi_clave8,mi_valor8);

printf("mostrar longitud tabla %d \n",m->longitud_tabla);
printf("mostrar cantidad elementos %d \n",m->cantidad_elementos);
printf("mostrar longitud fator escala %f \n",(float)m->cantidad_elementos/(float)m->longitud_tabla);


/////////////////////////////Veamos recuperar//////////////////////////////////////////////
printf("Recupero elementos \n");


salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 %d\n", *salida);

salida=m_recuperar(m,mi_clave2);
printf("recuperar c2 %d\n",*salida);

 salida=m_recuperar(m,mi_clave3);
printf("recuperar c3 %d\n", *salida);

 salida=m_recuperar(m,mi_clave4);
printf("recuperar c4 %d\n", *salida);


 salida=m_recuperar(m,mi_clave5);
printf("recuperar c5 %d\n", *salida);


 salida=m_recuperar(m,mi_clave6);
printf("recuperar c6 %d\n", *salida);


 salida=m_recuperar(m,mi_clave7);
printf("recuperar c7 %d\n", *salida);


 salida=m_recuperar(m,mi_clave8);
printf("recuperar c8 %d\n", *salida);

 salida=m_recuperar(m,mi_clave9);
printf("recuperar c9 que es igual a c8 %d\n", *salida);

 salida=m_recuperar(m,mi_clave10);
printf("recuperar c10 que no esta %d\n", salida);


/////////////////////////////////////////////////Pruebo eliminar de un mapeo con elementos///////////////////////////////////////////////////////

printf("elimino c1 de un mapeo que lo contiene \n");
m_eliminar(m,mi_clave1,&fEliminarC,&fEliminarV);
salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 mapeo para ver si lo elimino %d\n",salida);

//analizo los hash
printf("hash c1: %d\n",fHash(mi_clave1)%m->longitud_tabla);
printf("hash c2: %d\n",fHash(mi_clave2)%m->longitud_tabla);
printf("hash c3: %d\n",fHash(mi_clave3)%m->longitud_tabla);
printf("hash c4: %d\n",fHash(mi_clave4)%m->longitud_tabla);
printf("hash c5: %d\n",fHash(mi_clave5)%m->longitud_tabla);
printf("hash c6: %d\n",fHash(mi_clave6)%m->longitud_tabla);
printf("hash c7: %d\n",fHash(mi_clave7)%m->longitud_tabla);
printf("hash c8: %d\n",fHash(mi_clave8)%m->longitud_tabla);
printf("hash c9: %d\n",fHash(mi_clave9)%m->longitud_tabla);
printf("hash c10: %d\n",fHash(mi_clave10)%m->longitud_tabla);

printf("reincerto c1 \n");
m_insertar(m,mi_clave1,mi_valor1);
salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 mapeo para ver si inserto %d\n",*salida);

printf("elimino c10 que perteneceria a un fila no vacia \n");
m_eliminar(m,mi_clave10,&fEliminarC,&fEliminarV);
salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 para comprobar que no lo elimino por error %d\n",*salida);

printf("elimino dos vece c1 para comprobar que no da erro eliminar de una fila vacia %d\n");
m_eliminar(m,mi_clave1,&fEliminarC,&fEliminarV);
m_eliminar(m,mi_clave1,&fEliminarC,&fEliminarV);

salida=m_recuperar(m,mi_clave1);
printf("recuperar c1 para comprobar que lo elimino %d\n",salida);
printf("\n");
printf("/////////-------->destruyo el mapeo<-----------------///////\n");
m_destruir(&m,&fEliminarC,&fEliminarV);
printf("\n");
printf("################################################################################################\n");
printf("#####################----TERMINE PRUEBA MAPEO SIN ERROR----#####################################\n");
printf("################################################################################################\n");
printf("\n");
printf("\n");
printf("\n");
printf("\n");
}

int main(){

probarLista();

probarMapeo();


return 0;}

