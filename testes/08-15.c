#define NULL 0
//-----05-----
typedef struct nodo2{
	struct nodo2 *a;
	struct nodo2 *b;
}nodo2;
int atv05(nodo2 *pt1, nodo2 *pt2){
	pt1->a = pt2->a;
	pt1->b = pt2;
	pt1->a->b = pt1;
	pt2->a = pt1;
	/*
	p->esq->dir->esq = p->esq;
	p->esq->dir->dir = p;
	p->esq = p->esq->dir;
	*/
}
//-----06-----
typedef struct nodo{
	int x;
	struct nodo *link;
}nodo;

int contaNodo(struct nodo *p){
	int cont = 0;
	if(p != NULL){
		cont = 1;
		while(p->link != NULL){
			cont++;
			p = p->link;
		}
	}
	return cont;
}
int contaNodoLoop(struct nodo *p){
	int cont = 0;
	struct nodo *aux = NULL;
	if(p != NULL){
		cont = 1;
		aux = p;
		while(p->link != aux){
			cont++;
			p = p->link;
		}
	}
	return cont;
}
int contaNodoNarciso(struct nodo *p){
	int cont = 0;
	if(p != NULL){
		cont = 1;
		while(p->link != p){
			cont++;
			p = p->link;
		}
	}
	return cont;
}

//-----07-----
typedef struct descritor{
	int tamanho;
	nodo *inicio;
}descritor;

int reinicia(descritor *p){

}