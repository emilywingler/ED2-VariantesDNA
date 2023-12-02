#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include <stdio.h>

// Definição de estrutura para representar um nó na lista
typedef struct No {
    void *info;
    struct No *prox, *ant;
} No;

// Definição de estrutura para representar a fila
typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Função para criar um novo nó
No *CriaNo(void *info);

/*
 * Função para entrar na fila
 * Parâmetros:
 *   - f: ponteiro para a fila
 *   - info: ponteiro para os dados a serem armazenados no novo nó
 * Retorno:
 *   - ponteiro para a fila atualizada
 */
Fila *EntraNaFila(Fila *f, void *info);

/*
 * Função para sair da fila
 * Parâmetros:
 *   - f: ponteiro para a fila
 */
void SaiDaFila(Fila *f);

/*
 * Função para liberar a fila e seus nós
 * Parâmetros:
 *   - f: ponteiro para a fila
 */
void LiberarFila(Fila *f);

/*
 * Função para obter o tamanho da fila
 * Parâmetros:
 *   - f: ponteiro para No da fila
 * Retorno:
 *   - número de elementos na fila
 */
int TamanhoFila(No *f);

#endif // FILA_H
 