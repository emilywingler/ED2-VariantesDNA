#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    void *info;
    int size;
    struct no *prox, *ant;
}fila;

//Cria No;
fila *Cria(void *info){
    fila *novo = (fila*)malloc(sizeof(fila));
    if(!novo){
        printf("Erro de alocação");
        exit(1);
    }
    novo->info = info;
    novo->size = 0;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

int FilaVazia(fila *f){
    return (f->prox == NULL);
}

//Entra na fila;
fila *EntraNaFila(fila *f, void *dado){
    fila *novo = Cria(dado);
    if(FilaVazia(f)){
        f->prox = novo;
        novo->ant = f;
    }
    else{
        fila *aux = f;
        while (aux->prox!=NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
    f->size+=1;
    return f;
}

//Sai da fila
void SaiDaFila(fila **f){
    if(FilaVazia(*f)){
        printf("A lista já está vazia");
    }
    else{
        fila *aux = *f;
        *f = aux->prox;
        aux->prox->ant = *f;
        free(aux);
        (*f)->size-=1;
    }
}
//Tamanho da fila;

int tamanho(fila *f){
    return f->size;
}

void PercorreFila(fila *f, void *dado){
    if(FilaVazia(f)){
        printf("Fila está fazia");
    }
    else{
        fila *aux = f;
        while (aux!=NULL)
        {
            printf("%i ", dado);
            aux = aux->prox;
        }
    }
}
