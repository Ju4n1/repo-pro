#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    unsigned long hash = 0;
    int  d;
    while ((d = *p ++))
        hash =  d+ (hash << 2)- hash;
    return fabs(hash);}




int main(int argc,char* argv[]){


char* mi_clave = malloc(sizeof(char) * 5);
mi_clave[0]='H';
mi_clave[1]='o';
mi_clave[2]='l';
mi_clave[3]='a';
mi_clave[4]='\n';

int * mi_valor1 = malloc(sizeof(int));
*mi_valor1 = 10;

char* mi_clave2 = malloc(sizeof(char) * 7);
mi_clave2[0]='Z';
mi_clave2[1]='a';
mi_clave2[2]='p';
mi_clave2[3]='a';
mi_clave2[4]='t';
mi_clave2[5]='o';
mi_clave2[6]='\n';

int * mi_valor2 = malloc(sizeof(int));
*mi_valor2 = 1;

char* mi_clave3 = malloc(sizeof(char) * 7);
mi_clave3[0]='Z';
mi_clave3[1]='z';
mi_clave3[2]='z';
mi_clave3[3]='z';
mi_clave3[4]='z';
mi_clave3[5]='z';
mi_clave3[6]='\n';


int * mi_valor3 = malloc(sizeof(int));
*mi_valor3 = 5;

char* mi_clave4 = malloc(sizeof(char) * 7);
mi_clave4[0]='Z';
mi_clave4[1]='z';
mi_clave4[2]='z';
mi_clave4[3]='z';
mi_clave4[4]='z';
mi_clave4[5]='z';
mi_clave4[6]='\n';
int * mi_valor4 = malloc(sizeof(int));
*mi_valor4 = 4;


char* mi_clave5 = malloc(sizeof(char) * 3);
mi_clave5[0]='a';
mi_clave5[1]='b';
mi_clave5[2]='\n';


char* mi_clave6 = malloc(sizeof(char) * 5);
mi_clave6[0]='a';
mi_clave6[1]='l';
mi_clave6[2]='o';
mi_clave6[3]='l';
mi_clave6[4]='\n';
int * mi_valor6 = malloc(sizeof(int));
*mi_valor6 = 6;


//pruebo fHash

printf("pruebo fHash: \n");
printf(" %d \n",fHash(mi_clave)%10);
printf(" %d \n",fHash(mi_clave2)%10);
printf(" %d \n",fHash(mi_clave3)%10);
printf(" %d \n",fHash(mi_clave4)%10);
printf(" %d \n",fHash(mi_clave5)%10);
printf(" %d \n",fHash(mi_clave6)%10);

//pruebo fComp
printf("pruebo comp: \n");
printf(" comparo la misma clave %d \n",fComparacion(mi_clave,mi_clave));
printf(" comparo claves distintas %d \n",fComparacion(mi_clave2,mi_clave));

//pruebo mapero

tMapeo m;

crear_mapeo(&m,10,&fHash,&fComparacion);



m_insertar(m,mi_clave,mi_valor1);
m_insertar(m,mi_clave2,mi_valor2);
m_insertar(m,mi_clave3,mi_valor3);
m_insertar(m,mi_clave4,mi_valor4);
m_insertar(m,mi_clave6,mi_valor6);

int * salida=m_recuperar(m,mi_clave);
printf("recupero clave %d \n",*salida);

salida=m_recuperar(m,mi_clave2);
printf("recupero clave2 %d \n",*salida);

salida=m_recuperar(m,mi_clave3);
printf("recupero clave3 %d :\n",*salida);

salida=m_recuperar(m,mi_clave4);
printf("recupero clave4 que es igual a clave 3 '5': %d \n",*salida);

salida=m_recuperar(m,mi_clave5);
printf("recupero clave5 que no esta en m %d \n",salida);

printf("inserto clave4 que es igual a clave3 pero con valor '4: \n");
m_insertar(m,mi_clave4,mi_valor4);

salida=m_recuperar(m,mi_clave3);
printf("recupero valor con clave3 que es igual a clave4, que tiene valor '4': %d \n",*salida);

salida=m_recuperar(m,mi_clave4);
printf("recupero valor con clave4 debería ser '4' %d \n",*salida);

printf("elimino clave5 que no esta y fila vacia, cantidad elemento deberia ser '3' y es: %d\n",m->cantidad_elementos);
m_eliminar(m,mi_clave5,&fEliminarC,&fEliminarV);

printf("elimino clave6 que no esta y fila no vacia, cantidad elemento deberia ser '3' y es: \n");
m_eliminar(m,mi_clave6,&fEliminarC,&fEliminarV);
printf("cantidad elementos %d\n",m->cantidad_elementos);

printf("elimino clave3 que esta en mapeo \n");
m_eliminar(m,mi_clave3,&fEliminarC,&fEliminarV);

salida=m_recuperar(m,mi_clave4);
printf("recupero valor con clave4 debería ser '0' porque no esta %d \n",salida);
printf("cantidad elementos %d\n",m->cantidad_elementos);

m_insertar(m,mi_clave4,mi_valor4);
m_insertar(m,mi_clave6,mi_valor6);


//inserto para probar rehash

char* mi_clave7 = malloc(sizeof(char) * 5);
mi_clave7[0]='l';
mi_clave7[1]='a';
mi_clave7[2]='l';
mi_clave7[3]='i';
mi_clave7[4]='\n';
int * mi_valor7 = malloc(sizeof(int));
*mi_valor7 = 7;

char* mi_clave8 = malloc(sizeof(char) * 5);
mi_clave8[0]='n';
mi_clave8[1]='g';
mi_clave8[2]='a';
mi_clave8[3]='n';
mi_clave8[4]='\n';
int * mi_valor8 = malloc(sizeof(int));
*mi_valor8 = 8;

char* mi_clave9 = malloc(sizeof(char) * 5);
mi_clave9[0]='p';
mi_clave9[1]='a';
mi_clave9[2]='p';
mi_clave9[3]='a';
mi_clave9[4]='\n';
int * mi_valor9 = malloc(sizeof(int));
*mi_valor9 = 9;

char* mi_clave10 = malloc(sizeof(char) * 5);
mi_clave10[0]='m';
mi_clave10[1]='a';
mi_clave10[2]='m';
mi_clave10[3]='a';
mi_clave10[4]='\n';
int * mi_valor10 = malloc(sizeof(int));
*mi_valor10 = 10;

m_insertar(m,mi_clave7,mi_valor7);
m_insertar(m,mi_clave8,mi_valor8);
m_insertar(m,mi_clave9,mi_valor9);
m_insertar(m,mi_clave10,mi_valor10);

printf("cantidad elementos %d\n",m->cantidad_elementos);
printf("cantidad elementos %d\n",m->longitud_tabla);

printf("factor escala %f\n",(float)m->cantidad_elementos/(float)m->longitud_tabla);

printf(" %d \n",fHash(mi_clave7)%m->longitud_tabla);
printf(" %d \n",fHash(mi_clave8)%m->longitud_tabla);
printf(" %d \n",fHash(mi_clave9)%m->longitud_tabla);
printf(" %d \n",fHash(mi_clave10)%m->longitud_tabla);


salida=m_recuperar(m,mi_clave7);
printf("recupero clave7, que tiene valor '7': %d \n",*salida);

salida=m_recuperar(m,mi_clave8);
printf("recupero clave8, que tiene valor '8': %d \n",*salida);

salida=m_recuperar(m,mi_clave9);
printf("recupero clave9, que tiene valor '9': %d \n",*salida);

salida=m_recuperar(m,mi_clave10);
printf("recupero clave10, que tiene valor '10': %d \n",*salida);

salida=m_recuperar(m,mi_clave5);
printf("recupero clave5, que no esta: %d \n",salida);

salida=m_recuperar(m,mi_clave3);
printf("recupero clave3, que tiene valor '4': %d \n",*salida);

printf("elimino clave5 \n");
m_eliminar(m,mi_clave5,&fEliminarC,&fEliminarV);

printf("elimino clave8 \n");
m_eliminar(m,mi_clave8,&fEliminarC,&fEliminarV);

printf("cantidad elementos '7' %d\n",m->cantidad_elementos);

m_destruir(&m,&fEliminarC,&fEliminarV);

return 0;}

