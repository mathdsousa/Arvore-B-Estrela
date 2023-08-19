#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "ArvoreBEstrela.h"

#define DEBUG 1

int compareChaves(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

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

int arvB_destroi(ArvB* raiz)
{
    if(raiz == NULL)
        return 0;
    arvB_destroiNO(raiz);
    free(raiz);
    return 1;
}

void arvB_destroiNO(ArvB* no)
{  
    if(DEBUG)
        printf("Entrou no destroi\n");
    if(no == NULL || no == NULL)
    {
        if(DEBUG)
            printf("O destrói deu errado\n");
        return; 
    }

    int i = 0, result = 0;

    while(i <= (*no)->qnt_chaves && (*no)->filhos[0] != NULL)
        result = arvB_destroi(&(*no)->filhos[i++]);

    if(DEBUG)
        printf("Desalocando memoria\n");

    free((*no)->chaves);
    free((*no)->filhos);
    free(*no);

    if(DEBUG)
        printf("Destroi deu certo\n");
}

int arvB_insere(ArvB* no, int valor)
{
    int i = 0;
    int result = 0;

    if(no != NULL && (*no)->filhos[0] == NULL) // Rever
    {
        result = arvB_insereNO(no, valor);
        if(result != -1)
            *no = (*split(no, result)); // Além de dividir, deve inserir o aux na primeira posição livre do segundo vetor
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

int arvB_insereNO(ArvB* no, int valor)
{
    int i = 0;
    int aux;

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
        return -1; // Não houve propagação de valor;
    }
    
    if(DEBUG)
        printf("Houve overflow \n");


    // Promoção de chave
    int* chaves = (int*) malloc(sizeof(int)*ordem);

    for(int j = 0; j < ordem - 1; j++)
        chaves[j] = (*no)->chaves[j];
    chaves[ordem - 1] = valor;

    qsort(chaves, ordem, sizeof(int), compareChaves);

    aux = chaves[4];

    if(DEBUG)
        printf("Chaves promovida: %d\n", aux);

    for(int j = 0; j < ordem - 1; j++)
    {
        if (j < 4)
            (*no)->chaves[j] = chaves[j];
        else if (j > 4)
            (*no)->chaves[j - 1] = chaves[j];
    }

    free(chaves);

    return aux;
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
        {
            result = arvB_insereNO(novoNO1, (*no)->chaves[i]);
            (*novoNO1)->filhos[i] = (*no)->filhos[i];
        }
        else
        {
            result = arvB_insereNO(novoNO2, (*no)->chaves[i]);
            (*novoNO2)->filhos[i-4] = (*no)->filhos[i];
        }
    }
    imprime(novoNO1);
    imprime(novoNO2);

    (*novoNO2)->filhos[3] = (*no)->filhos[ordem - 1];
    result = arvB_insereNO(novoNOPai, valor);

    imprime(novoNOPai);

    (*novoNOPai)->filhos[0] = (*novoNO1);
    (*novoNOPai)->filhos[1] = (*novoNO2);

    arvB_destroiNO(no);

    return novoNOPai;
}

int arvB_remove(ArvB *no, int valor)
{
    
}

int arvB_busca(ArvB* raiz, int valor)
{
    if (raiz == NULL || *raiz == NULL) {
        return 0; // Key not found
    }
    ArvB aux;
    aux = *raiz;

    int i = 0;
    while (i < aux->qnt_chaves && valor > aux->chaves[i]) {
        i++;
    }

    if (i < aux->qnt_chaves && valor == aux->chaves[i]) {
        return 1; // Chave encontrada
    } else if (aux->filhos == NULL) {
        return 0; // Chave nao foi encontrada
    } else {
        return arvB_busca(&(aux->filhos[i]), valor); //procura recursivamente
    }
}
    
int arvB_qtd_nos(ArvB *raiz)
{
    if (raiz == NULL || *(raiz) == NULL) {
        return 0;
    }

    int count = 1; // inicializa o contador + a propria raiz
    ArvB aux= *raiz;
    int aux1 = aux->qnt_chaves;
    for (int i = 0; i <= aux1; i++) {
        //erro na linha 209, possivelmente
        count += arvB_qtd_nos(&(aux->filhos[i])); // chama a recursao
    }
    return count;
}


int arvB_qtd_chaves(ArvB *raiz)
{
    if (raiz == NULL|| *raiz == NULL) {
        return 0;
    }

    ArvB aux= *raiz;
    int aux1 = aux->qnt_chaves;
    int count = aux1; // inicializa o contador + qnt de chaves no noh
    for (int i = 0; i <= aux1; i++) {
        //erro na linha 226, possivelmente
        count += arvB_qtd_chaves(&(aux->filhos[i])); // chama a recursao
    }
    return count;

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
