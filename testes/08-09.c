#include <stdio.h>
#include <stdlib.h>
struct nodo{
    int x;
    struct nodo* link;
    };
typedef struct nodo* def_nodo;
def_nodo inicializa (void){
    return NULL;
}

int main(){
    int x = 3;
    printf("%i\n",++x);
}