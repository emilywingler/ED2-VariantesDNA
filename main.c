// ED2_Grupo <4>_[Emily][Gabrielly][Guilherme][Samuel].zip

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "arquivos.h"


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

// // Função principal para o algoritmo KMP
int *kmp(char *texto, int ttam, char *padrao, int ptam, Sequencia *padraoDNA) {
    int i;
    int *pi = preprocessamento(padrao, ptam);
    int k = -1;
    int count = 0;

    if (!pi) {
        return NULL; // Retorna NULL em caso de falha na alocação de memória
    }

    int *tempOcorreu = malloc(sizeof(int) * ttam);
    if (!tempOcorreu) {
        free(pi);
        return NULL;
    }

    for (i = 0; i < ttam; i++) {
        // Loop principal para percorrer o texto e encontrar o padrão
        while (k > -1 && padrao[k + 1] != texto[i]) k = pi[k];
        if (texto[i] == padrao[k + 1]) k++;
        if (k == ptam - 1) {
            tempOcorreu[count++] = i - k;
        }
    }

    free(pi);

    // Atribui o array de posições à estrutura Sequencia
    padraoDNA->ocorreu = tempOcorreu;
    padraoDNA->ocorreu_count = count;

    return tempOcorreu;
}

void buscaKmp(No *listaDNA, char *padrao, int ttam) {
    No *atual = listaDNA;

    while (atual != NULL) {
        Sequencia *padraoDNA = (Sequencia *)atual->info;
        int *ocorreu = kmp(padraoDNA->dados, strlen(padraoDNA->dados), padrao, strlen(padrao), padraoDNA);

        if (ocorreu != NULL && padraoDNA->ocorreu_count > 0) {
            printf("[%s] no. de ocorrencias: %d posicoes:", padraoDNA->id, padraoDNA->ocorreu_count);

            for (int j = 0; j < padraoDNA->ocorreu_count; j++) {
                printf(" %d", padraoDNA->ocorreu[j]);
            }

            printf("\n");
        }

        free(ocorreu);
        atual = atual->prox;
    }
    free(atual);
}


// ..
int main() {
    FILE *arquivo1, *arquivo2;
    // Abre o arquivo para leitura
    arquivo1 = fopen("PadroesVirus.txt", "r");
    arquivo2 = fopen("BaseDadosDNA.txt", "r");
    // Verifica se o arquivo foi aberto com sucesso
    validade(arquivo1);
    validade(arquivo2);

    Fila *padroes = (Fila *)malloc(sizeof(Fila));
    Fila *sequencia = (Fila *)malloc(sizeof(Fila));

    No *virus = ProcessaPadrao(arquivo1, padroes);
    No *DNA = ProcessaPadrao(arquivo2, sequencia);
    

    int Qts_padroes = TamanhoFila(virus);


    No *atual = virus;
    for (int i = 0; i < Qts_padroes && atual != NULL; i++) {
        Padrao *padraoVirus = (Padrao *)atual->info;
        printf("%s\n", padraoVirus->id);
        buscaKmp(DNA, padraoVirus->dados, strlen(padraoVirus->dados));
        printf("\n");
        atual = atual->prox;
    }

    LiberarFila(padroes);
    LiberarFila(sequencia);


    fclose(arquivo1);
    fclose(arquivo2);

    
    return 0;
}
