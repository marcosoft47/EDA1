#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arq.h"
#define SIZECSV 10000

//Pega o que tiver no campo num
const char* getfield(char* line, int num);

int main(){
    FILE *fp = fopen("dataset_v1.csv", "r");
    srand(time(NULL));
    char linha[SIZECSV][64];
    int contador = 0;
    char tmp[64];

    fgets(tmp,64,fp);
    while(fgets(tmp,64,fp))
        strcpy(linha[contador++], tmp);
    contador = 0;
    // for(int i = 0; i <= 10; i++)
    //     puts(linha[rand() % SIZECSV]);
    

    //Começar FDE prioridade simples
    struct descF *desc = NULL;
    info *pessoa = NULL;
    pessoa = iniciaInfo();
    desc = cria(SIZECSV);
    int num = 0;
    while(contador <= 5){
        // num = rand() % SIZECSV;
        // printf("%s\n",getfield(linha[num],2));
        // strcpy(pessoa->nome,getfield(linha[num],1));
        // pessoa->matricula = atoi(getfield(linha[num],2));
        // pessoa->ranking = atoi(getfield(linha[num],3));
        // strcpy(pessoa->curso,getfield(linha[num],4));
        strcpy(pessoa->nome,"eeee");
        pessoa->matricula = 2;
        pessoa->ranking = 3;
        strcpy(pessoa->curso,"aeiou");

        insere(pessoa,desc);
        contador++;
    }
    // for (contador = 0; contador <= 5;contador++)
    printf("Deu boa\n");
}

const char* getfield(char* line, int num){
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}