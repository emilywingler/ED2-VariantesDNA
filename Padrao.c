#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct no
{
    char *id;
    char *variante;
    struct no *prox;
}Padrao;

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
int main(){
    FILE *arquivo;

    // Abre o arquivo para leitura
    arquivo = fopen("PadroesVirus.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (!arquivo) {
        printf("Não foi possível ler o arquivo\n");
        exit(1);
    }

    char linha[70];
    Padrao *inicio = NULL;
    Padrao *virus = NULL;
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';
        if(linha[0] == '>' && linha[1] == 'E' && linha[2] == 'O' && linha[3] == 'F'){
            break;
        }
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
    