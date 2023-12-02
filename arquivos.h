#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "arquivos.h"

typedef struct {
    char *id;
    char *dados;
} Padrao;

typedef struct {
    char *id; // Identificador e descrição combinados
    char *dados;
    int existe; // 0 ou 1 caso o padrão exista neles
    int ocorrencias;
    int *ocorreu; //vetor de ocorrências do padrão
} Sequencia;


/*
 * Função para limpar caracteres indesejados da sequência de DNA
 * Parâmetros:
 *   - Padrao: ponteiro para a sequência de DNA a ser limpa
 * Retorno:
 *   - ponteiro para a sequência de DNA limpa
 */
char *LimparPadrao(const char *Padrao);

/*
 * Função para verificar se é o fim do arquivo
 * Parâmetros:
 *   - linha: ponteiro para a linha lida do arquivo
 * Retorno:
 *   - 1 se for o fim do arquivo, 0 se pode continuar
 */
int FimDeArquivo(const char *linha);

/*
 * Função para alocar espaço para um novo padrão
 * Retorno:
 *   - ponteiro para a estrutura do padrão alocado
 */
Padrao *AlocaPadrao();

/*
 * Função para verificar se o arquivo foi aberto com sucesso
 * Parâmetros:
 *   - arquivo: ponteiro para o arquivo a ser verificado
 */
void validade(FILE *arquivo);

/*
 * Função para processar padrões a partir de um arquivo e armazená-los em uma fila
 * Parâmetros:
 *   - arquivo: ponteiro para o arquivo contendo os padrões
 *   - padroes: ponteiro para a fila onde os padrões serão armazenados
 * Retorno:
 *   - ponteiro para o início da fila de padrões
 */
No *ProcessaPadrao(FILE *arquivo, Fila *padroes);

#endif // ARQUIVO_H
