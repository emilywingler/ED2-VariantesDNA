#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct No {
    char *padrao;
    int ptam;
    struct No *prox;
} No;

int *preprocessamento(char *padrao, int ptam){
    int k = -1;
    int i = 1;
    int *pi = malloc(sizeof(int)*ptam);
    if(!pi){
        return NULL;
    }
    pi[0] = k;
    for(i=1; i<ptam;i++){
        while (k > -1 && padrao[k+1] != padrao[i]) k = pi[k];
        if (padrao[i] == padrao[k+1]) k++;
        pi[i] = k;
    }
    return pi;
}

int kmp(char *texto, int ttam, char *padrao, int ptam){
    int i;
    int *pi = preprocessamento(padrao,ptam);
    int k = -1;
    int count = 0;
    if(!pi){
        return -1;
    }
    for (i = 0; i<ttam; i++){
        while(k > -1 && padrao[k+1] != texto[i]) k = pi[k];
        if(texto[i] == padrao[k+1]) k++;
        if(k == ptam - 1){
            //free(pi);
            printf("Encontrou na posição %i .\n", i - k);
            count++;
        }
    }
    return count;
}

void buscaKmp(No *listaPadroes, char *texto, int ttam) {
    No *atual = listaPadroes;
    while (atual != NULL) {
        int count = kmp(texto, ttam, atual->padrao, atual->ptam);
        printf("Vezes em que o padrão '%s' apareceu: %i\n", atual->padrao, count);
        atual = atual->prox;
    }
}

No *adicionarPadrao(No *lista, char *padrao, int ptam) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro.\n");
        exit(1);
    }
    novo->padrao = padrao;
    novo->ptam = ptam;
    novo->prox = lista;
    return novo;
}

int main() {
    char texto[] = "abacaabaccabacabaabb";

    No *listaPadroes = NULL;
    listaPadroes = adicionarPadrao(listaPadroes, "aba", 3);
    listaPadroes = adicionarPadrao(listaPadroes, "acc", 3);

    buscaKmp(listaPadroes, texto, strlen(texto));

    No *atual = listaPadroes;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    return 0;
}