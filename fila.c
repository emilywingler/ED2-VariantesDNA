// ED2_Grupo <4>_[Emily][Gabrielly][Guilherme][Samuel].zip

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

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

Fila *EntraNaFila(Fila *f, void *info) {
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

No *SaiDaFila(Fila *f) {
    if (f->inicio != NULL) {
        No *removido = f->inicio;
        f->inicio = f->inicio->prox;

        if (f->inicio != NULL) {
            f->inicio->ant = NULL;
        } else {
            f->fim = NULL;
        }

        removido->prox = NULL;
        removido->ant = NULL;

        return removido;
    }

    return NULL;
}

// Altere a função para não chamar mais a LiberarNo
void LiberarFila(Fila *f) {
    while (f->inicio != NULL) {
        No *removido = SaiDaFila(f);
        free(removido);  // Liberar diretamente o nó
    }
    free(f);
}


int TamanhoFila(No *f) {
    int count = 0;
    No *aux = f;
    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }
    return count;
}