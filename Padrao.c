#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct no
{
    char *id;
    char *variante;
    struct no *prox;
}Padrao;


typedef struct f {
    void *info;
    struct f *prox, *ant;
} fila;


fila *Cria(void *info) {
    fila *novo = (fila *)malloc(sizeof(fila));
    if (!novo) {
        printf("Erro de alocação");
        exit(1);
    }
    novo->info = info;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

// Entra na fila;
fila *EntraNaFila(fila *f, void *dado) {
    fila *novo = Cria(dado);
    fila *aux = f;
    
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    
    aux->prox = novo;
    novo->ant = aux;

    return f;
}

// Sai da fila
void SaiDaFila(fila **f) {
    if ((*f)->prox == NULL) {
        printf("A fila já está vazia\n");
        return;
    }

    fila *aux = (*f)->prox;
    free(*f);
    *f = aux;
    if (*f != NULL) {
        (*f)->ant = NULL;
    }
}

// Tamanho da fila;
int tamanho(fila *f) {
    int count = 0;
    fila *aux = f->prox; // Pular o nó cabeça
    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }
    return count;
}
// devemos criar um padrão genérico para essa função 
// porque ela é utilizada por dois arquivos diferentes, Por enquanto deixa assim;
char *limparPadrao(char *Padrao) {
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

void ValidaArquivo(FILE *arquivo){
    if (!arquivo) {
        printf("Não foi possível ler o arquivo\n");
        exit(1);
    }
}

int FimDeArquivo(char *linha){
    if(linha[0] == '>' && linha[1] == 'E' && linha[2] == 'O' && linha[3] == 'F'){
            return 1; //fim de arquivo
        }
    return 0; //pode continuar
}
int main(){
    FILE *arquivo;
    // Abre o arquivo para leitura
    arquivo = fopen("PadroesVirus.txt", "r");
    ValidaArquivo(arquivo);
    // Verifica se o arquivo foi aberto com sucesso

    char linha[70];
    
    Padrao *inicio = NULL;
    Padrao *virus = NULL;
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
    
        if(FimDeArquivo(linha)) break;
        if (linha[0] == '>') {
            // Alocando memória para o novo nó
            virus = (Padrao *)malloc(sizeof(Padrao));

            // Verifica se a alocação foi bem-sucedida
            if (!virus) {
                printf("Erro na alocação de memória\n");
                exit(1);
            }

            // Combinando identificador e descrição em uma única string
            virus->id = strdup(&linha[1]); // Ignora o '>'
            
            // Inicializa a sequência de DNA
            virus->variante = NULL;

            // Adiciona a nova virus na lista
            virus->prox = inicio;
            inicio = virus;
        } else {
            // Limpa a sequência apenas se não for uma nova espécie
            char *limpaDado = limparPadrao(linha);

            // Verifica se dado é NULL ou não
            if (virus->variante == NULL) {
                virus->variante = strdup(limpaDado); // Aloca e copia
            } else {
                virus->variante = realloc(virus->variante, (strlen(virus->variante) + strlen(limpaDado) + 1) * sizeof(char));
                strcat(virus->variante, limpaDado); // Concatena com dado existente
            }

            free(limpaDado);
        }
    }

    virus = inicio;
    while (virus != NULL) {
        
            printf("Identificador e Descrição: %s\n", virus->id);
            printf("Sequência de DNA: %s\n", virus->variante);
        
        Padrao *proxima = virus->prox;
        free(virus->id); // Libera a memória alocada para id
        free(virus->variante);                   // Libera a memória alocada para dados
        free(virus);                          // Libera a memória alocada para virus
        virus = proxima;
    }
        
        return 0;
    }
    