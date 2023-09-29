#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.c"
//TODO: Não pegar erro com as excessões; Documentar; Almoçar :)
//Remove caracter especificado de uma string
void removeChar(char *str, char garbage);
int ehexcessao(char texto[]);

int main(int argc, char *argv[]){
    FILE *fp;
    int c;
    char texto[50] = "";
    int dentroTag = TRUE;
    int linha = 0;
    int deuruim = FALSE;

    struct pilha *pil = NULL;
    tag *exemplo;
    tag *tagaux;
    pil = iniciaPilha();
    exemplo = iniciaTag();
    tagaux = iniciaTag();

    for (int i = 1; i < argc; i++){
        fp = fopen(argv[i], "r");
        if (fp == NULL){
            printf("Erro na abertura do arquivo.");
            fclose(fp);
            return 0;
        }
        while ((c = fgetc(fp)) != EOF){
            if (c == '<')
                dentroTag = TRUE;
            if (c == '\n')
                linha++;
            
            //Enquanto TRUE, vai preenchendo o texto
            if (dentroTag){

                //Opa fechou a tag?
                if (c == '>' || c == ' '){
                    strcat(texto, ">");

                    if (texto[1] == '/'){
                        removeChar(texto, '/');
                        if (strcmp(texto, pil->topo->info) == 0 && !vazia(pil))
                            desempilha(exemplo, pil);
                        else{
                            //TODO: Imprimir o texto com '/'
                            printf("ERRO: No arquivo %s, na linha %i, esperado %s, encontrado %s\n", argv[i],linha, pil->topo->info, texto);
                            deuruim = TRUE;
                        }
                    } else{
                        if (!ehexcessao(texto)){
                            strcpy(exemplo->info, texto);
                            exemplo->linha = linha;
                            empilha(exemplo, pil);
                        }
                    }

                    dentroTag = FALSE;
                    memset(texto, 0, sizeof(texto));
                } else
                    texto[strlen(texto)] = c;
            }
        }
        if(!vazia(pil) && !deuruim){
            tagaux = pil->topo;
            while(tagaux->abaixo != NULL){
                printf("ERRO: No arquivo %s, %s não foi fechado\n", argv[i], tagaux->info);
                tagaux = tagaux->abaixo;
            }
            continue;
        }
        if (!deuruim)
            printf("Nenhum erro encontrado no arquivo %s :)\n", argv[i]);
        
        
        //Reiniciar valores (nem sei se boa parte disso realmente precisa :v)
        memset(texto, 0, sizeof(texto));
        dentroTag = TRUE;
        linha = 0;
        deuruim = FALSE;
        reinicia(pil);
    }
    fclose(fp);
    destroi(pil);
}

void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

int ehexcessao(char texto[]){
    char excessoes[][50] = {"<!DOCTYPE>","<input>","<frame>","<br>","<img>","<option>"};
    if (strncmp(texto, "<!--", 4) == 0)
        return TRUE;
    for (int i = 0; i < (sizeof(excessoes) / sizeof(excessoes[0])); i++){
        if(strcmp(excessoes[i], texto) == 0)
            return TRUE;
    }
    return FALSE;
}