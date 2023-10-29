#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arq.h"
#define SIZECSV 10000

//Pega o que tiver no campo num
char *getfield(const char* line, int num);

int FDEimovel(char linha[][64], int size);

int main(){
    FILE *fp = fopen("dataset_v1.csv", "r");
    srand(time(NULL));
    char linha[SIZECSV][64];
    char tmp[64];
    int contador = 0;
    int numTestes[] = {500, 1000, 1500, 2000, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    size_t qntTestes = sizeof(numTestes)/sizeof(numTestes[0]);

    fgets(tmp,64,fp);
    while(fgets(tmp,64,fp))
        strcpy(linha[contador++], tmp);
    fclose(fp);
    contador = 0;
    // for(int i = 0; i <= 10; i++)
    //     puts(linha[rand() % SIZECSV]);
    
    //Começar FDE prioridade simples
    for(contador = 0; contador < qntTestes; contador++)
        printf("Número de loops com fila de tamanho %i: %i\n", numTestes[contador], FDEimovel(linha, numTestes[contador]));
    printf("Deu boa\n");
}

char *getfield(const char* line, int num) {
    const char *p = line;
    size_t len;
    char *res;
    for (;;) {
        len = strcspn(p, ",\n");
        if (--num <= 0)
            break;
        p += len;
        if (*p == ',')
            p++;
    }
    res = malloc(len + 1);
    if (res) {
        memcpy(res, p, len);
        res[len] = '\0';
    }
    return res;
}

int FDEimovel(char linha[][64], int size){
    int num = 0, contador = 0, qntLoop = 0;

    struct descF *desc = NULL;
    info *pessoa = NULL, *auxinfo;
    struct noFila *auxno = NULL;
    pessoa = iniciaInfo();
    auxinfo = iniciaInfo();
    desc = cria(sizeof(info));

    while(contador < size){
        num = rand() % SIZECSV;
        // num = contador;
        strcpy(pessoa->nome,getfield(linha[num],1));
        pessoa->matricula = atoi(getfield(linha[num],2));
        pessoa->ranking = atoi(getfield(linha[num],3));
        strcpy(pessoa->curso,getfield(linha[num],4));

        insere(pessoa,desc, &qntLoop);
        contador++;
    }
    buscaNaCauda(auxinfo,desc);
    auxno = desc->cauda;
    while (auxno != NULL){
        // printf("%s %i %i %s\n", auxno->dados.nome, auxno->dados.matricula, auxno->dados.ranking, auxno->dados.curso);
        auxno = auxno->defronte;
    }
    desc = destroi(desc);
    return qntLoop;
}