#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "mapeo.h"

// En caso que se produzca una finalizaci�n del programa debido a un error, determinan la naturaleza del mismo.
#define ABRIR_ARCH_ERROR -1
#define PROG_INICIA_ERROR -2

/**
 Elimina un elemento y libera el espacio que este ocupa en memoria, se utiliza para la implementaci�n de lista, y en la tabla del mapeo.
**/
void fEliminar(tElemento e){
   e=NULL;
   free(e);}

/**
 Dada dos cadenas de caracteres las compara, resultando en un "0" si estas son iguales, y distinto de "0" si son distintas.
**/
int fComparacion(void *e1, void *e2){

return strcmp((char*)e1,(char*)e2);}

/**
 Elimina una clave y libera el espacio que esta ocupa en memoria, esta funci�n es utilizada para la implementaci�n del mapeo.
**/
void fEliminarC(tClave c1){
   c1=NULL;
   free(c1);}

/**
 Elimina un valor y libera el espacio que este ocupa en memoria, esta funci�n es utilizada para la implementaci�n del mapeo.
**/
void fEliminarV(tValor v1){

v1=NULL;
free(v1);}

/**
 La funci�n hash a partir de un cadena de caracteres calcula un entero positivo, esta funci�n se utiliza para determinar la fila
 a la que pertenece una clave dentro del mapeo.
 La fuente de la misma http://www.cse.yorku.ca/~oz/hash.html más las recomendaci�n de un ayudante.
**/
int fHash(void *c){
char *p=c;
int hash = 0;
int  d;
       while ((d = *p ++))
           hash +=(hash<<3)+d;

return fabs(hash);}


/**
  A partir del archivo "f1", alamacena las palabras que contenga el mismos, en el mapeo "m" usando como clave a la palabra y como valor su cantidad de apariciones.
**/

void IngresarArchivo(FILE* f1,tMapeo m){
    char* pal=malloc(sizeof(char) * 80);
    int haypalabra=0;
    int* rec;
    while(feof(f1)==0){
        fscanf(f1,"%s",pal);// Almaceno la palabra en pal.
        if(strlen(pal)>0){
            haypalabra=1;
        }
        if(haypalabra){
            if(m_recuperar(m,pal)==NULL){ // Determina si la palabra ya se habia procesado.
                rec=malloc(sizeof(int));
                *rec=1;
                m_insertar(m,pal,rec);
            }else{
                rec=m_recuperar(m,pal);
                *(rec)= *(rec)+1; // Actualizo el valor pero directamente accediendo al puntero, y evito hacer otro insertar.
                free(pal); // Libera la memoria ya que la palabra ya se habia procesado antes.
            }
        }
        pal= malloc(sizeof(char) * 80);// Se reserva espacio para la nueva palabra.
        haypalabra=0;
    }
    if (feof(f1)&&(haypalabra)) {
        if(m_recuperar(m,pal)==NULL){
            rec=malloc(sizeof(int));
            *rec=1;
            m_insertar(m,pal,rec);
        }
        else{
            if(haypalabra){
                rec=m_recuperar(m,pal);
                *(rec)= *(rec)+1;
                free(pal);
            }
        }
    }else{free(pal);}// Este free ya que se reserv� espacio de memoria con un contenido vacio.

}


void menu(FILE * arch){

	tMapeo m;
    crear_mapeo(&m,10,&fHash,&fComparacion);
    IngresarArchivo(arch,m);
    printf("||#####Bienvenidos al programa evaluador #####||\n");
    printf("Que desea hacer con el archivo?\n");
    char opcion;

	do{

		printf("Menu de opciones \n");
        printf("%5s","");
        printf("-Si desea saber la cantidad de apariciones de una palabra presione: 1\n");
        printf("%5s","");
        printf("-Si desea salir presione: 2\n");
        printf("Opcion: ");
        scanf("%c",&opcion);

		fflush(stdin);// Limpio el buffer de teclado.

		if(opcion=='1'){
            system("cls");// Limpio la consola.
            printf("Opcion 1: Cantidad de apariciones\n");
            printf("%5s","");
            printf("-Ingrese la palabra a buscar: ");
            char*palabra=malloc(sizeof(char)*80);// Reservo espacio para leer la palabra de teclado.
            scanf("%s",palabra);
            fflush(stdin);    // Limpio el buffer de teclado.

			if(m_recuperar(m,palabra)!=NULL){ // Determina si esta o no la palabra en el archivo.
                int* apariciones=m_recuperar(m,palabra);
                printf("La cantidad de apariciones de %s es: %i\n",palabra,*apariciones);
            }
            else{
                printf("La palabra %s no se encuentra en el texto.\n",palabra);
                }
            free(palabra);// Libero la palabra ya que no se vuelve a usar.
        }
        else{

            if(opcion=='2'){
                 system("cls");
                 printf("Opcion 2: Salir del programa\n");
                 m_destruir(&m,&fEliminarC,&fEliminarV);
                 printf("%5s","");
                 printf("-Se ha finalizado el evaluador");
                 fclose(arch);
                 }
            else{
                printf("Opcion invalida\n");
                Sleep(1);// Este retardo es para que se vea el cartel antes e limpiar la consola.
                system("cls");// Limpio la consola.

            }
        }

    }while(opcion!='2');}



int main(int argc, char *argv[]){
    if (argc==2){
        char * nombreArch=argv[1]; // Nomre del archivo.
        FILE* Archivo;
        Archivo=fopen(nombreArch,"r");// Abro el archivo para solo lectura.
        if(Archivo==NULL){
            printf("El archivo no existe. \n");
            return ABRIR_ARCH_ERROR;
        }else{
              menu(Archivo);
        }

    }else{
          printf ("Error al invocar del programa. \n");
          return PROG_INICIA_ERROR;
    }

	printf ("El programa finaliza sin errores. \n");
	return 0;
}
