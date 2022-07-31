#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include"arvore.h"

struct arvore{
    Arvore* esq;
    Arvore* dir;
    long int peso;
    unsigned char letra;
    int id;
};

Arvore* inicializaArvore(){
    Arvore* arv;
    arv = malloc(sizeof(Arvore));
    arv->dir=NULL;
    arv->esq=NULL;
    arv->peso=0;
    arv->id=0;
    arv->letra=-1;

    return arv;
}

Arvore* insereArvore(unsigned char carac){
    Arvore* arv = inicializaArvore();
    arv->letra=carac;
    arv->id=1;
    return arv;
}

Arvore* uneArvores(Arvore* dir, Arvore* esq){
    Arvore* arv;
    arv = inicializaArvore();
    arv->dir=dir;
    arv->esq=esq;
    setPeso(arv,getPeso(dir)+getPeso(esq));
    return arv;
}

unsigned char getCaractere(Arvore* arv){
    return arv->letra;
}

long int getPeso(Arvore* arv){
    return arv->peso;
}

void setPeso(Arvore* arv, long int peso){
    if(arv!=NULL){
        arv->peso=peso;
    }
    return;
}

static char* buscaNoArvore(Arvore* arv, unsigned char carac){
    char* codigoD; char* codigoE;
    if(arv==NULL){
        return NULL;
    
    }else if(arv->id==1){
        if(arv->letra==carac){
            char* codigo = malloc(2*sizeof(char));
            codigo[0]='2';
            codigo[1]='\0';
            return codigo;

        }else{
            return NULL;
        }
    
    }else if(arv->dir!=NULL){
        codigoD = buscaNoArvore(arv->dir,carac);
       
        if(codigoD!=NULL && !strcmp(codigoD, "2")){
            codigoD[0] = '1';
            return codigoD;
        
        }else if((codigoD)!=NULL){
            strcat(codigoD, "1");
            return codigoD;
        }

        free(codigoD);

    }if(arv->esq!=NULL){
        codigoE = buscaNoArvore(arv->esq,carac);
        if(codigoE!=NULL && !strcmp(codigoE, "2")){
            codigoE[0] = '0';
            return codigoE;
        
        }else if((codigoE)!=NULL){
            strcat(codigoE, "0");
            return codigoE;
        }

        free(codigoE);
    }

    return NULL;

}

unsigned char* buscaArvore(Arvore* arv,unsigned char carac){
    unsigned char* codigo = (unsigned char*) buscaNoArvore(arv,carac);
    printf("%s\n",codigo);
    free(codigo);
    return NULL;
}


void liberaArvore(Arvore* arv){
    if(arv==NULL){
        return;

    }else if(arv->dir==NULL&&arv->esq==NULL){
        free(arv);
        return;
    }

    if(arv->esq!=NULL){
        liberaArvore(arv->esq);
    }
    
    if(arv->dir!=NULL){
        liberaArvore(arv->dir);
    }
    free(arv);
    return;
}

static void imprimeArvore (Arvore* arv, int space){


    if (arv == NULL){
        return;
    }


    space += 10;

    imprimeArvore (arv->dir, space);

    printf("\n");
    for (int i = 10; i < space; i++){
        printf(" ");
    }

    if(getCaractere(arv)<128&&getCaractere(arv)>=0){
        printf("%c\n", getCaractere(arv));
    }else{
        printf("O");
    }
    imprimeArvore (arv->esq, space);

}

void arv_imprime(Arvore* arv){
    imprimeArvore(arv, 0);
    return;
}