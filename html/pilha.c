#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

struct pilha{
    struct tag *topo;
    int tam;
};
typedef struct tag{
    char info[50];
    int linha;
    struct tag *abaixo;
}tag;

//Verifica se a pilha está vazia
int vazia(struct pilha *pil){
  return pil->topo == NULL;
}

//Adiciona um item ao topo da pilha
int empilha(tag *item, struct pilha *pil){
    tag *aux=NULL;
    aux= (tag *) malloc(sizeof(tag));

    if (aux!=NULL){
        memcpy(&(aux->info), item, sizeof(tag)); //<<<<<<<<<<
	    aux->abaixo=pil->topo;
     	pil->topo=aux;
	    (pil->tam)++;
        return TRUE;
    }
    else
        return FALSE;
}

//Remove um item do topo da pilha
int desempilha(tag *reg, struct pilha *pil){
    struct tag *aux=NULL;	  
    if (!vazia(pil)){
        memcpy(reg, &(pil->topo->info),sizeof(tag)); //<<<<<<<
	    aux=pil->topo->abaixo;
	    free(pil->topo);
	    pil->topo=aux;
        (pil->tam)--;
        return TRUE;
    }
    else
        return FALSE;
}
//inicia uma pilha com valores padrões
struct pilha *iniciaPilha(){
    struct pilha *p=NULL;
    p = (struct pilha *) malloc(sizeof(struct pilha));
    if (p){
	    p->topo=NULL;
        p->tam=0;
    }
    return p;
}
tag *iniciaTag(){
    tag *t=NULL;
    t = (tag *) malloc(sizeof(tag));
    if (t){
	    t->abaixo = NULL;
        t->linha = 0;
        strcpy(t->info," ");
    }
    return t;
    
}


//Reinicia uma pilha
void reinicia(struct pilha *pil){
    struct tag *aux=NULL;	  
    if (vazia(pil)==FALSE){	 
        aux=pil->topo->abaixo;
        while(aux!=NULL){
            free(pil->topo);
            pil->topo=aux;
            aux=aux->abaixo;
        }
        free(pil->topo);
        pil->topo=NULL;
        pil->tam=0;
    }
 	
}

//Destroi uma pilha
struct pilha *destroi(struct pilha *pil){
	reinicia(pil);
	free(pil);
  	return NULL;	
}	