#include <stdio.h>
#include <malloc.h>
#include "ArvoreBEstrela.h"

#define DEBUG 1

ArvB* arvB_cria()
{
    ArvB *raiz = (ArvB*) malloc(sizeof(ArvB));

    if(raiz != NULL)
    {
        *raiz = NULL;
        arvB_criaNO(raiz);
        if(DEBUG)
            printf("Criou\n");
        return raiz;
    }
    free(raiz);
    return NULL;
}

void arvB_criaNO(ArvB *no)
{
    *no = (ArvB) malloc(sizeof(struct NO));

    if(no == NULL)
        return;

    (*no)->pai = NULL;
    (*no)->qnt_chaves = 0;
    (*no)->chaves = (int*) malloc(sizeof(int) * (ordem - 1));
    (*no)->filhos = (ArvB*) malloc(sizeof(ArvB) * ordem);

    for(int i = 0; i < ordem; i++)
    {
        (*no)->filhos[i] = NULL;
        if(i != ordem - 1)
            (*no)->chaves[i] = -1;
    }
    if(DEBUG)
        printf("Criou no\n");
}

int arvB_destroi(ArvB *raiz)
{  
    if(DEBUG)
        printf("Entrou no destroi\n");
    if(raiz != NULL)
    {
        arvB_destroiNO(*raiz);
        free(raiz);
        if(DEBUG)
            printf("Destruiu\n");
        return 1;
    }
    if(DEBUG)
        printf("O destrói deu errado\n");
    return -1; 
}

void arvB_destroiNO(ArvB no)
{
    if(no != NULL)
    {
        if(no->filhos[0] != NULL)
        {
            for(int i = 0; i < no->qnt_chaves + 1; i++)
                arvB_destroiNO(no->filhos[i]);
             free(no->filhos);
        }
        free(no->chaves);
        free(no);
    }
    if(DEBUG)
        printf("Destruiu no\n");
}

int arvB_insere(ArvB* no, int valor)
{
    int i = 0;
    int aux;

    if(no != NULL && (*no)->filhos[0] == NULL) // Rever
    {
        if((*no)->qnt_chaves < ordem - 1) // Primeiro caso - quando há espaço na folha
        {
            while((*no)->chaves[i] < valor && i < (*no)->qnt_chaves){i++;};
            if(i == (*no)->qnt_chaves) // Insere caso a posição i não esteja ocupada
            {
                (*no)->chaves[(*no)->qnt_chaves++] = valor;
            }
            else // Reordena e insere caso a posição i já esteja ocupada
            {
                for(int j = ordem - 1; j > i; j--)
                    (*no)->chaves[j] = (*no)->chaves[j - 1];
                (*no)->chaves[i] = valor;
                (*no)->qnt_chaves++;   
            }
        }
        else // Segundo caso - quando o nó folha está 100% ocupado - overflow
        {   
            if(DEBUG)
                printf("Entrou nesse else \n");
            while((*no)->chaves[i] < valor && i < (*no)->qnt_chaves - 1){i++;};
            aux = (*no)->chaves[ordem - 2]; // Salva o elemento da última posição
            imprime(no);
            for(int j = ordem - 1; j > i; j--) // Reordena e insere o valor na posição correta
                (*no)->chaves[j] = (*no)->chaves[j - 1];
            (*no)->chaves[i] = valor;  
            if(DEBUG)
                printf("Posicao de insercao: %d e valor a ser inserido: %d\n", i, aux);
            if(DEBUG)
                imprime(no);
            *no = (*split(no, aux)); // Além de dividir, deve inserir o aux na primeira posição livre do segundo vetor
        }
        return 1;
    }
    if((*no)->filhos[0] != NULL) // Caso não esteja em um nó folha, são feitas chamadas recursivas até encontrar um
    {
        if(DEBUG)
            printf("Entrou no outro caso \n");
        while((*no)->chaves[i] < valor && i < (*no)->qnt_chaves){i++;};
        if(DEBUG)
            printf("Posicao: %d \n", i);
        if((*no)->filhos[i]->filhos[0] == NULL && (*no)->filhos[i]->qnt_chaves == ordem - 1)
            promocao(no, i, valor);

        return arvB_insere(&(*no)->filhos[i], valor);
    }
    return -1;
}

ArvB* split(ArvB *no, int valor)
{
    if(DEBUG)
        printf("Entrou no split, valor: %d\n", valor);
    int result;

    ArvB* novoNO1 = (ArvB*) malloc(sizeof(ArvB));
    ArvB* novoNO2 = (ArvB*) malloc(sizeof(ArvB));
    ArvB* novoNOPai = (ArvB*) malloc(sizeof(ArvB));

    if(novoNO1 == NULL || novoNO2 == NULL || novoNOPai == NULL)
    {
        printf("Erro no split");
        return NULL;
    }

    arvB_criaNO(novoNO1); arvB_criaNO(novoNO2); arvB_criaNO(novoNOPai);

    for(int i = 0; i < ordem - 1; i++)
    {
        if(i < 4)
            result = arvB_insere(novoNO1, (*no)->chaves[i]);
        else if(i > 4)
            result = arvB_insere(novoNO2, (*no)->chaves[i]);
    }

    result = arvB_insere(novoNO2, valor);
    result = arvB_insere(novoNOPai, (*no)->chaves[4]);

    (*novoNOPai)->filhos[0] = (*novoNO1);
    (*novoNOPai)->filhos[1] = (*novoNO2);

    arvB_destroi(no);

    return novoNOPai;
}

int arvB_remove(ArvB *no, int valor)
{
    
}

int arvB_busca(ArvB *raiz, int valor)
{
    
}

int arvB_qtd_nos(ArvB *raiz)
{
    
}

int arvB_qtd_chaves(ArvB *raiz)
{
    
}

void imprime(ArvB* raiz)
{
    if(raiz != NULL)
        imprimeNO(*raiz, 0);
}

void imprimeNO(ArvB no, int nivel)
{
    if(no != NULL)
    {
        for(int i = 0; i < nivel; i++)
            printf(" ");
        for(int i = 0; i < no->qnt_chaves; i++)
            printf("%d ", no->chaves[i]);
        printf("\n");
        for(int i = 0; i < no->qnt_chaves + 1; i++)
            imprimeNO(no->filhos[i], nivel + 3);
    }
}

void promocao(ArvB *no, int posicao, int valor)
{
    int aux = (*no)->filhos[posicao]->chaves[4];
}
