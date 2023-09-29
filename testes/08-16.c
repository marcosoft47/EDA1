#define NULL 0
typedef struct teste{
    int inteiro;
    float real;
    char nome[30];
} data;
typedef struct nodo{
    data dt;
    nodo *link;
} nodo;
typedef struct descritor{
    int tamanho;
    nodo *inicio;
} descritor;

void reinicia (descritor *p){
    if (!p->inicio)
        return;
    nodo *aux = p->inicio;
    p->inicio = aux->link;
    free(aux);
    while (p->inicio!=NULL){
        aux = p->inicio;
        p->inicio = p->inicio->link;
        free(aux);
    }
    p->tamanho = 0;
    return;
}

void insere (descritor *p, nodo *novo, int pos){}