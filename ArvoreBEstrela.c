#include <stdio.h>
#include <malloc.h>
#include "ArvoreBEstrela.h"

#define DEBUG 1

ArvB* arvB_cria()
{
    ArvB* raiz = (ArvB*) malloc(sizeof(ArvB));
    *raiz = (ArvB) malloc(sizeof(struct NO));
    
    if(raiz != NULL)
    {
        (*raiz)->qnt_chaves = 0;
        (*raiz)->chaves = (int*) malloc(sizeof(int) * (ordem - 1));
        (*raiz)->filhos = (ArvB*) malloc(sizeof(ArvB) * ordem);

        if((*raiz)->chaves != NULL && (*raiz)->filhos != NULL)
        {
            for(int i = 0; i < ordem; i++)
            {
                (*raiz)->filhos[i] = NULL;
                if(i != ordem - 1)
                    (*raiz)->chaves[i] = -1;
            }
        }
        else
        {
            free((*raiz)->chaves);
            free((*raiz)->filhos);
            free(*raiz);
            free(raiz);
            return NULL;
        }
    }
    else
    {
        free(raiz);
        return NULL;
    }

    return raiz;
};

void split()
{
    return;
}

int arvB_insere(ArvB* raiz, int valor)
{
    if(raiz == NULL)
        return -1;
    return arvB_insereR(*raiz, valor);
}

int arvB_insereR(ArvB no, int valor)
{
    int i = 0;
    if(no->filhos[0] == NULL) // É folha
    {
        while(i < ordem && no->chaves[i] < valor){i++;} // Procura uma posição no vetor
        if(i < ordem && no->chaves[i] == -1) // Apenas insere na primeira posição livre.
        {
            no->chaves[i] = valor;
            return 1;
        }
        else if(i < ordem && no->chaves[i] != -1 && no->qnt_chaves < ordem - 1)
        {
            for(int j = no->chaves - 1; j >= i; j--) // Se a posição i já estiver ocupada, e o nó não estiver cheio,
                no->chaves[j + 1] = no->chaves[j];   // move-se as demais chaves para deixar
            no->chaves[i] = valor;                   // essa posição desocupada.
        }
        else if(i < ordem && no->qnt_chaves == ordem - 1 && no->filhos[i] != NULL)
        {
            arvB_insereR(no->filhos[i], valor);
        }
        else if(i == ordem && no->filhos[ordem - 1] != NULL)
        {
            arvB_insereR(no->filhos[ordem - 1], valor);
        }
        else
        {

        }
    }
}

void arvB_destroi(ArvB *raiz)
{
    if(raiz != NULL)
        arvB_destroiNo(*raiz);

    free(raiz);

    if(DEBUG)
        printf("destruiu...");
}

void arvB_destroiNo(ArvB no)
{
    if(no->qnt_chaves != 0)
        if(no->filhos[0] != NULL) // É folha?
            for(int i = 0; i < no->qnt_chaves + 1; i++)
                arvB_destroiNo((no->filhos[i]));

    free(no->filhos);
    free(no->chaves);
    free(no);

    if(DEBUG)
        printf("destruiu...");
}
