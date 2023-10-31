#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arq.h"
#define SIZECSV 10000
#define LOOPS 5
//Pega o que tiver no campo num.
char *getfield(const char* line, int num);

//Operação de teste do FDE sem referencial móvel. Retorna o número de loops.
int FDE(char linha[][64], int size, int usarRefMovel);

void clear();

int main(){
    FILE *fp = fopen("dataset_v1.csv", "r");
    srand(time(NULL));
    char linha[SIZECSV][64];
    char tmp[64];
    int contador = 0, running = 1, input = 0, escolha = 0;
    //Usar media como float quebra todos os calculos de média
    int media = 0;

    int numTestes[] = {500, 1000, 1500, 2000, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
    size_t qntTestes = sizeof(numTestes)/sizeof(numTestes[0]);
    int resultados[LOOPS][qntTestes];

    //Nesse programa, vamos passar pelo arquivo várias vezes.
    //Ao invés de carregar e descarregar várias vezes, só salvei ele todo na memória
    fgets(tmp,64,fp);
    while(fgets(tmp,64,fp))
        strcpy(linha[contador++], tmp);
    fclose(fp);
    contador = 0;
    
    printf("\e[1;1H\e[2J");
    while (running){
        printf("Escolha uma opção:\n");
        printf("(0) Sair do programa\n");
        printf("(1) Teste manual FDE sem referencial móvel\n");
        printf("(2) Teste automático de FDE sem referencial móvel\n");
        //Começar FDE prioridade simples
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 0:
            printf("Saindo...\n");
            running = 0;
            break;
        case 1:
            printf("Escolha a quantidade de itens que a fila terá: ");
            scanf("%d", &input);
            printf("Número de loops com fila de tamanho %i: %i\n", input, FDE(linha, input, NAO));
            input = 0;
            clear();
            break;
        case 2:
            printf("Realizando cálculos...\n");
            for (int i = 0; i < qntTestes; i++){
                for(contador = 0; contador < LOOPS; contador++){
                    resultados[contador][i] = FDE(linha, numTestes[i], NAO);
                    media += resultados[contador][i];
                }
                media /= LOOPS;
                printf("Media de loops com fila de tamanho %d: %d\n", numTestes[i], media);
                media = 0;
            }
            clear();
            break;
        case 3:
            printf("Escolha a quantidade de itens que a fila terá: ");
            scanf("%d", &input);
            printf("Número de loops com fila de tamanho %i: %i\n", input, FDE(linha, input, SIM));
            input = 0;
            clear();
            break;
        case 4:
            printf("Realizando cálculos...\n");
            for (int i = 0; i < qntTestes; i++){
                for(contador = 0; contador < LOOPS; contador++){
                    resultados[contador][i] = FDE(linha, numTestes[i], SIM);
                    media += resultados[contador][i];
                }
                media /= LOOPS;
                printf("Media de loops com fila de tamanho %d usando ref movel: %d\n", numTestes[i], media);
                media = 0;
            }
            clear();
            break;
        default:
            printf("Escolha uma opção válida!\n");
            clear();
            break;
        }
    }
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

int FDE(char linha[][64], int size, int usarRefMovel){
    int num = 0, contador = 0, qntLoop = 0;

    struct descF *desc = NULL;
    info *pessoa = NULL, *auxinfo;
    pessoa = iniciaInfo();
    desc = cria(sizeof(info));

    while(contador < size){
        num = rand() % SIZECSV;
        strcpy(pessoa->nome,getfield(linha[num],1));
        pessoa->matricula = atoi(getfield(linha[num],2));
        pessoa->ranking = atoi(getfield(linha[num],3));
        strcpy(pessoa->curso,getfield(linha[num],4));
        printf("%s %i %i %s\n", pessoa->nome, pessoa->matricula, pessoa->ranking, pessoa->curso);
        if (usarRefMovel)
            insereMovel(pessoa, desc, &qntLoop);
        else
            insere(pessoa,desc, &qntLoop);
        
        contador++;
    }
    /*Descomente para debug*/
    struct noFila *auxno = NULL;
    auxinfo = iniciaInfo();
    buscaNaCauda(auxinfo,desc);
    auxno = desc->cauda;
    while (auxno != NULL){
        printf("%s %i %i %s\n", auxno->dados.nome, auxno->dados.matricula, auxno->dados.ranking, auxno->dados.curso);
        auxno = auxno->defronte;
    }

    /*Recomente para dedebug*/
    desc = destroi(desc);
    return qntLoop;
}

void clear(){
    printf("Aperte qualquer botão...");
    fflush(stdin);
    __fpurge(stdin);
    getchar();
    printf("\e[1;1H\e[2J");
}