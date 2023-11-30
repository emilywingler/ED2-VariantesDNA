#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição de estrutura para representar um nó na lista de padrões
typedef struct No {
    char *padrao;    // Padrão a ser buscado
    int ptam;         // Tamanho do padrão
    struct No *prox;  // Ponteiro para o próximo nó na lista
} No;



// Função para realizar o preprocessamento do padrão usando o algoritmo KMP
int *preprocessamento(char *padrao, int ptam) {
    int k = -1;
    int i = 1;
    int *pi = malloc(sizeof(int) * ptam);

    if (!pi) {
        return NULL; // Retorna NULL em caso de falha na alocação de memória
    }

    pi[0] = k;

    for (i = 1; i < ptam; i++) {
        // Loop para calcular o array de preprocessamento (pi)
        while (k > -1 && padrao[k + 1] != padrao[i]) k = pi[k];
        if (padrao[i] == padrao[k + 1]) k++;
        pi[i] = k;
    }

    return pi;
}

// Função principal para o algoritmo KMP
int kmp(char *texto, int ttam, char *padrao, int ptam) {
    int i;
    int *pi = preprocessamento(padrao, ptam);
    int k = -1;
    int count = 0;

    if (!pi) {
        return -1; // Retorna -1 em caso de falha na alocação de memória
    }

    for (i = 0; i < ttam; i++) {
        // Loop principal para percorrer o texto e encontrar o padrão
        while (k > -1 && padrao[k + 1] != texto[i]) k = pi[k];
        if (texto[i] == padrao[k + 1]) k++;
        if (k == ptam - 1) {
            printf("Encontrou na posição %i.\n", i - k);
            count++;
        }
    }

    free(pi); // Libera a memória alocada para o array de preprocessamento
    return count;
}

// Função para realizar a busca KMP para cada padrão na lista
void buscaKmp(No *listaPadroes, char *texto, int ttam) {
    No *atual = listaPadroes;

    while (atual != NULL) {
        // Chama a função KMP para cada padrão na lista
        int count = kmp(texto, ttam, atual->padrao, atual->ptam);
        printf("Vezes em que o padrão '%s' apareceu: %i\n", atual->padrao, count);
        atual = atual->prox;
    }
}

// Função para adicionar um novo padrão à lista
No *adicionarPadrao(No *lista, char *padrao, int ptam) {
    No *novo = (No *)malloc(sizeof(No));

    if (!novo) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    // Atribui os valores ao novo nó na lista
    novo->padrao = padrao;
    novo->ptam = ptam;
    novo->prox = lista;

    return novo;
}


int main() {
    // Texto no qual a busca será realizada
    FILE *dna, *padrao;
    char texto[] = "abacaabaccabacabaabb";

    // Inicialização da lista de padrões
    No *listaPadroes = NULL;
    listaPadroes = adicionarPadrao(listaPadroes, "aba", 3);
    listaPadroes = adicionarPadrao(listaPadroes, "acc", 3);

    // Realiza a busca KMP para cada padrão na lista
    buscaKmp(listaPadroes, texto, strlen(texto));

    // Libera a memória alocada para cada nó na lista
    No *atual = listaPadroes;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    return 0;
}
