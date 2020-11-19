#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
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
void ingrmapeo(FILE* f1,tMapeo m){
    f1=fopen("f1.txt","r");
    char* pal=malloc(sizeof(char) * 80);
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
                    //printf("\n");
                    if(m_recuperar(m,pal)==NULL){
                      //  printf("la palabra no estaba en el mapeo\n");
                        rec=malloc(sizeof(char));
                        *rec=1;
                        m_insertar(m,pal,rec);
                    }else{
                            //printf("\n");
                            //printf("dsp de recuperar palabra valor vale: %i\n",*rec);
                            rec=m_recuperar(m,pal);
                            *(rec)= *(rec)+1;
                            m_insertar(m,pal,rec);
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
            rec=malloc(sizeof(char));
            *rec=1;
            m_insertar(m,pal,rec);
        }else{
                //printf("\n");
                //printf("dsp de recuperar palabra valor vale: %i\n",*rec);
                rec=m_recuperar(m,pal);
                *(rec)= *(rec)+1;
                m_insertar(m,pal,rec);
                //printf("dsp de insertar palabra valor vale: %i\n",*rec);
                            //i=0;
                            //haypalabra=0;
                }
    }/*else{
        free(pal);
    }*/

}
int main(){
    printf("Bienvenidos al programa evaluador\n");
    printf("\n");
    tMapeo m;
    crear_mapeo(&m,10,&fHash,&fComparacion);
    FILE * f1=NULL;
    ingrmapeo(f1,m);
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
            printf("Opcion 1: Cantidad de apalariciones\n");
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
                 printf("-oprima enter para finalizar");
            }
            else{
                printf("Opcion invalida\n");
                sleep(1);
                system("cls");

            }
        }

    }while(opcion!='2');
    return 0;
}
