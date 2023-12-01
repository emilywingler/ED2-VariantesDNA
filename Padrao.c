#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char *id;
    char *variante;
} Padrao;

typedef struct No {
    void *info;
    struct No *prox, *ant;
} No;

typedef struct {
    No *inicio;
    No *fim;
} FilaPadroes;

No *CriaNo(void *info) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação\n");
        exit(1);
    }
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

FilaPadroes *EntraNaFila(FilaPadroes *f, void *info) {
    No *novo = CriaNo(info);
    if (f->inicio == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        novo->ant = f->fim;
        f->fim = novo;
    }
    return f;
}

void SaiDaFila(FilaPadroes *f) {
    if (f->inicio != NULL) {
        No *removido = f->inicio;
        f->inicio = f->inicio->prox;

        if (f->inicio != NULL) {
            f->inicio->ant = NULL;
        } else {
            f->fim = NULL;
        }

        free(removido->info);
        free(removido);
    }
}

void LiberarFila(FilaPadroes *f) {
    while (f->inicio != NULL) {
        SaiDaFila(f);
    }
    free(f);
}

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

No *ProcessaPadrao(FILE *arquivo, FilaPadroes *padroes){
    char linha[70];
    // FilaPadroes *padroes = (FilaPadroes *)malloc(sizeof(FilaPadroes));
    padroes->inicio = NULL;
    padroes->fim = NULL;

   while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    linha[strcspn(linha, "\n")] = '\0';

    if (FimDeArquivo(linha)) break;

    Padrao *virus;

    if (linha[0] == '>') {
        virus = AlocaPadrao();
        virus->id = strdup(&linha[1]); // Ignora o '>'
        virus->variante = NULL;

        EntraNaFila(padroes, virus);
    } else {
        char *limpaDado = LimparPadrao(linha);
        Padrao *virusAtual = (Padrao *)padroes->fim->info;

        if (virusAtual->variante == NULL) {
            virusAtual->variante = strdup(limpaDado);
        } else {
            // Realoca a variante para acomodar a nova sequência
            virusAtual->variante = realloc(virusAtual->variante, (strlen(virusAtual->variante) + strlen(limpaDado) + 1) * sizeof(char));
            // Concatena a nova sequência à variante existente
            strcat(virusAtual->variante, limpaDado);
        }

        free(limpaDado);
    }
    }

    return padroes->inicio;
}

//Tudo funciona agora precisamos mainpular os arqu

int main() {
    FILE *arquivo;
    // Abre o arquivo para leitura
    arquivo = fopen("PadroesVirus.txt", "r");
    // Verifica se o arquivo foi aberto com sucesso
    validade(arquivo);

    FilaPadroes *padroes = (FilaPadroes *)malloc(sizeof(FilaPadroes));

    No *virus = ProcessaPadrao(arquivo,padroes);
    while (virus != NULL) {
        Padrao *padraoAtual = (Padrao *)virus->info;
        printf("Identificador e Descrição: %s\n", padraoAtual->id);
        printf("Sequência de DNA: %s\n", padraoAtual->variante);

        virus = virus->prox;
    }

    LiberarFila(padroes);

    fclose(arquivo);

    return 0;
}
