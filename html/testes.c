#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int ehexcessao(char texto[]){
    char excessoes[][50] = {"<!DOCTYPE>","<input>","<frame>","<br>","<img>","<option>"};
    for (int i = 0; i < (sizeof(excessoes) / sizeof(excessoes[0])); i++){
        if(strcmp(excessoes[i], texto) == 0)
            return TRUE;
    }
    return FALSE;
}

int main(){
    char texto[] = "<input>";
    if (ehexcessao(texto))
        printf("aeipou");
    else
        printf("aefas");
}
