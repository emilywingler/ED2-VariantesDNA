//Os arquivos estão sendo salvos como uma pilha (lobo guará vem antes de onça pintada na saída), 
//mas eles devem ser uma fila para que saiam na ordem correta

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definição de estrutura para representar um nó na lista
typedef struct No {
    char *id; // Identificador e descrição combinados
    char *dados;
    int existe; // 0 ou 1 caso o padrão exista neles
    int ocorrencias;
    int *ocorreu; //vetor de ocorrências do padrão
    struct No *prox;
} Sequencia;

// Função para limpar caracteres indesejados da sequência de DNA
char *limparSequencia(char *sequencia) {
    int i, j = 0;
    char *limpaSequencia = malloc(strlen(sequencia) + 1);

    for (i = 0; sequencia[i] != '\0'; i++) {
        if (sequencia[i] == 'A' || sequencia[i] == 'C' || sequencia[i] == 'T' || sequencia[i] == 'G') {
            limpaSequencia[j++] = sequencia[i];
        }
    }

    limpaSequencia[j] = '\0';
    return limpaSequencia;
}

int main() {
    FILE *arquivo;

    // Abre o arquivo para leitura
    arquivo = fopen("BaseDadosDNA.txt", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (!arquivo) {
        printf("Não foi possível ler o arquivo\n");
        exit(1);
    }

    char linha[70];
    Sequencia *inicio = NULL;
    Sequencia *especie = NULL;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remove '\n' da linha, se houver
        linha[strcspn(linha, "\n")] = '\0';
        if(linha[0] == '>' && linha[1] == 'E' && linha[2] == 'O' && linha[3] == 'F'){
            break;
        }
        if (linha[0] == '>') {
            // Alocando memória para o novo nó
            especie = (Sequencia *)malloc(sizeof(Sequencia));

            // Verifica se a alocação foi bem-sucedida
            if (!especie) {
                printf("Erro na alocação de memória\n");
                exit(1);
            }

            // Combinando identificador e descrição em uma única string
            especie->id = strdup(&linha[1]); // Ignora o '>'
            
            // Inicializa a sequência de DNA
            especie->dados = NULL;

            // Adiciona a nova especie na lista
            especie->prox = inicio;
            inicio = especie;
        } else {
            // Limpa a sequência apenas se não for uma nova espécie
            char *limpaDado = limparSequencia(linha);

            // Verifica se dado é NULL ou não
            if (especie->dados == NULL) {
                especie->dados = strdup(limpaDado); // Aloca e copia
            } else {
                especie->dados = realloc(especie->dados, (strlen(especie->dados) + strlen(limpaDado) + 1) * sizeof(char));
                strcat(especie->dados, limpaDado); // Concatena com dado existente
            }

            free(limpaDado);
        }
    }

    // Imprime as espécies
    especie = inicio;
    while (especie != NULL) {
        
            printf("Identificador e Descrição: %s\n", especie->id);
            printf("Sequência de DNA: %s\n", especie->dados);
        
        Sequencia *proxima = especie->prox;
        free(especie->id); // Libera a memória alocada para id
        free(especie->dados);                   // Libera a memória alocada para dados
        free(especie);                          // Libera a memória alocada para especie
        especie = proxima;
    }

    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}
