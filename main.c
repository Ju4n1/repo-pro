#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "mapeo.h"


#define ABRIR_ARCH_ERROR -1
#define PROG_INICIA_ERROR -2

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



void IngresarArchivo(FILE* f1,tMapeo m){
    char* pal=malloc(sizeof(char) * 255);
    char c;
    int haypalabra=0;
    int i=0;
    int* rec;
    while(feof(f1)==0){
        c=fgetc(f1);
            if((c>=65 && c<=90)||(c>=97 && c<=122)){
                haypalabra=1;
                pal[i]=c;
                i++;
                //printf("%c",c);
            }else{
                if(haypalabra){
                    pal[i]='\0';
                    if(m_recuperar(m,pal)==NULL){
                      //  printf("la palabra no estaba en el mapeo\n");
                        rec=malloc(sizeof(int));
                        *rec=1;
                        m_insertar(m,pal,rec);
                    }else{
                            //printf("\n");
                            //printf("dsp de recuperar palabra valor vale: %i\n",*rec);
                            rec=m_recuperar(m,pal);
                            *(rec)= *(rec)+1;
                            free(pal);
                            //printf("dsp de insertar palabra valor vale: %i\n",*rec);
                            //i=0;
                            //haypalabra=0;
                        }
                    pal= malloc(sizeof(char) * 80);
                    haypalabra=0;
                    i=0;
                }
            }
    }
    if ((feof(f1) )&&(haypalabra)){
        /*rec=m_recuperar(m,pal);
        *(rec)= *(rec)+1;
        m_insertar(m,pal,rec);*/
        if(m_recuperar(m,pal)==NULL){
            printf("la palabra no estaba en el mapeo\n");
            rec=malloc(sizeof(int));
            *rec=1;
            m_insertar(m,pal,rec);
        }else{
                //printf("\n");
                //printf("dsp de recuperar palabra valor vale: %i\n",*rec);
                rec=m_recuperar(m,pal);
                *(rec)= *(rec)+1;
                free(pal);
                //printf("dsp de insertar palabra valor vale: %i\n",*rec);
                            //i=0;
                            //haypalabra=0;
                }
    }

}
void menu(FILE * arch){
    tMapeo m;
    crear_mapeo(&m,10,&fHash,&fComparacion);
    IngresarArchivo(arch,m);
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
        fflush(stdin);
        if(opcion=='1'){
            system("cls");
            printf("Opcion 1: Cantidad de apariciones\n");
            printf("%5s","");
            printf("-Ingrese la palabra a buscar: ");
            char*palabra=malloc(sizeof(char)*80);
            scanf("%s",palabra);
            fflush(stdin);
            if(m_recuperar(m,palabra)!=NULL){
                int* apariciones=m_recuperar(m,palabra);
                printf("La cantidad de apariciones de %s es: %i\n",palabra,*apariciones);
            }
            else{
                printf("La palabra %s no se encuentra en el texto.\n",palabra);
                }
            free(palabra);
        }
        else{
            if(opcion=='2'){
                 system("cls");
                 printf("Opcion 2: Salir del programa\n");
                 m_destruir(&m,&fEliminarC,&fEliminarV);
                 printf("%5s","");
                 printf("-Se ha finalizado el evaluador");
            }
            else{
                printf("Opcion invalida\n");
                //sleep(1);
                system("cls");

            }
        }

    }while(opcion!='2');
}
/*
int main(int argc, char *argv[]){
    printf("||#####Bienvenidos al programa evaluador #####||");
    printf("\n");
    if (argc==2){
        char * nombreArch=argv[1];
        FILE* Archivo;
        Archivo=fopen(nombreArch,"r");
        if(Archivo==NULL){
            return ABRIR_ARCH_ERROR;
        }else{
            menu(Archivo);
        }

    }else{
        printf ("Error al invocar del programa\n");
        return PROG_INICIA_ERROR;
    }
    return 0;
}*/
int main(){

    FILE* Archivo;
    Archivo=fopen("f1.txt","r");
    menu(Archivo);
    return 0;
}
