#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "arquivos.h"

char *LimparPadrao(const char *Padrao) {
    int i, j = 0;
    char *limpaPadrao = malloc(strlen(Padrao) + 1);

    for (i = 0; Padrao[i] != '\0'; i++) {
        if (Padrao[i] == 'A' || Padrao[i] == 'C' || Padrao[i] == 'T' || Padrao[i] == 'G') {
            limpaPadrao[j++] = Padrao[i];
        }
    }

    limpaPadrao[j] = '\0';
    return limpaPadrao;
}

int FimDeArquivo(const char *linha) {
    if (linha[0] == '>' && linha[1] == 'E' && linha[2] == 'O' && linha[3] == 'F') {
        return 1; // Fim de arquivo
    }
    return 0; // Pode continuar
}

Padrao *AlocaPadrao() {
    Padrao *virus = (Padrao *)malloc(sizeof(Padrao));
    // Verifica se a alocação foi bem-sucedida
    if (!virus) {
        printf("Erro na alocação de memória\n");
        exit(1);
    }
    return virus;
}

void validade(FILE *arquivo){
    if (!arquivo) {
        printf("Não foi possível ler o arquivo\n");
        exit(1);
    }
}

No *ProcessaPadrao(FILE *arquivo, Fila *padroes){
    char linha[70];
    // Fila *padroes = (Fila *)malloc(sizeof(Fila));
    padroes->inicio = NULL;
    padroes->fim = NULL;

   while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';

    if (FimDeArquivo(linha)) break;

    Padrao *virus;

    if (linha[0] == '>') {
        virus = AlocaPadrao();
        virus->id = strdup(&linha[1]); // Ignora o '>'
        virus->dados = NULL;

        EntraNaFila(padroes, virus);
    } else {
        char *limpaDado = LimparPadrao(linha);
        Padrao *virusAtual = (Padrao *)padroes->fim->info;

        if (virusAtual->dados == NULL) {
            virusAtual->dados = strdup(limpaDado);
        } else {
            // Realoca a dados para acomodar a nova sequência
            virusAtual->dados = realloc(virusAtual->dados, (strlen(virusAtual->dados) + strlen(limpaDado) + 1) * sizeof(char));
            // Concatena a nova sequência à dados existente
            strcat(virusAtual->dados, limpaDado);
        }

        free(limpaDado);
    }
    }

    return padroes->inicio;
}


