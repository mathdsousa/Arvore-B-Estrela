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
    if(no == NULL)
        return -1;
    int result = arvB_novaInsere(&(*no), valor, 1);
    return 1;
}

int arvB_novaInsere(ArvB* no, int valor, int raiz)
{
    if(DEBUG)
    {
        printf("Entrou na nova insere\n");
        printf("Eh raiz? %d \n", raiz);
    }
    int i = 0;
    int result = -1, temp = -1;

    if(*no == NULL) // Verifica se o nó é NULL
        return 0;
    
    if((*no)->filhos[0] == NULL) // Verifica se chegou na folha    
    {
        if(DEBUG)
            printf("Entrou no caso da raiz\n");
        result = arvB_insereNO(no, valor);
        if(result != -1 && raiz == 1)
            *no = (*split(no, result)); 
    }
    else // Desce até chegar na raiz
    {
        if(DEBUG)
            printf("Entrou no outro caso \n");
        while((*no)->chaves[i] < valor && i < (*no)->qnt_chaves){i++;};
        if(DEBUG)
            printf("Posicao: %d \n", i);
        temp = arvB_novaInsere(&(*no)->filhos[i], valor, 0); // temp verifica se houve propagação de valor
    }                                                        // -2 significa que não houve propagação de valor 

    if(DEBUG)
        printf("temp: %d\n", temp);

    if(temp != -1 && raiz == 0) // Isso insere no nó intemediário
    {
        if(DEBUG) 
            printf("Caso do noh intermediario\n");
        result = arvB_insereNO(no, temp);
    }

    if(temp != -1 && raiz == 1) // Isso insere no nó raiz e verifica se é preciso o split
    {
        if(DEBUG) 
            printf("Caso do noh raiz na nova insere\n");
        result = arvB_insereNO(no, temp);
        if(result != -1)
            *no = (*split(no, result)); 
        result = 1;
    }

    if(DEBUG)
        printf("Result da insere: %d\n", result);

    return result;
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
            if((*no)->filhos[0] != NULL)
                ajustaNO(no, valor, i);
            (*no)->chaves[(*no)->qnt_chaves++] = valor;
        }
        else // Reordena e insere caso a posição i já esteja ocupada
        {
            if((*no)->filhos[0] != NULL)
                ajustaNO(no, valor, i);
            for(int j = ordem - 2; j > i; j--)
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

    aux = chaves[ordem/2];

    if(DEBUG)
        printf("Chaves promovida: %d\n", aux);

    for(int j = 0; j < ordem; j++) // Ajuste feito
    {
        if (j < ordem/2)
            (*no)->chaves[j] = chaves[j];
        else if (j > ordem/2)
            (*no)->chaves[j - 1] = chaves[j];
    }

    imprime(no);

    free(chaves);

    return aux;
}

void ajustaNO(ArvB* no, int valor, int posicao)
{   
    int aux;  
    ArvB* novoNO = (ArvB*) malloc(sizeof(ArvB));

    if(novoNO == NULL)
        return;

    arvB_criaNO(novoNO);
    
    for(int i = ordem/2; i < ordem - 1; i++)
    {
        aux = arvB_insereNO(novoNO, (*no)->filhos[posicao]->chaves[i]); // insere as ultimas chaves do antigo nó no novo;
        (*no)->filhos[posicao]->chaves[i] == -1; // Atribui -1 para as chaves movidas
        (*no)->filhos[posicao]->qnt_chaves--; // Decrementa quantidade de chaves nesse nó
    }
    for(int i = ordem/2; i < ordem; i++)
    {
        (*novoNO)->filhos[ordem/2 - i] = (*no)->filhos[posicao]->filhos[i]; // Move os ponteiros para o novo nó
        (*no)->filhos[posicao]->filhos[i] = NULL; // Atribui NULL para as posições que o ponteiro foi movido
    }
        
    if((*no)->chaves[posicao] == -1)
    {
        (*no)->filhos[posicao + 1] = *novoNO; // Liga o novo nó a esse nó pai;

        return;
    }

    for(int j = ordem - 1; j > posicao + 1; j--)
        (*no)->filhos[j] = (*no)->filhos[j - 1];

    (*no)->filhos[posicao + 1] = *novoNO; // Liga o novo nó a esse nó pai;
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
        if(i < ordem/2)
        {
            result = arvB_insereNO(novoNO1, (*no)->chaves[i]);
            (*novoNO1)->filhos[i] = (*no)->filhos[i];
        }
        else
        {
            result = arvB_insereNO(novoNO2, (*no)->chaves[i]);
            (*novoNO2)->filhos[i - (ordem/2)] = (*no)->filhos[i];
        }
    }

    imprime(novoNO1);
    imprime(novoNO2);

    (*novoNO2)->filhos[(ordem/2) - 1] = (*no)->filhos[ordem - 1];
    result = arvB_insereNO(novoNOPai, valor);

    imprime(novoNOPai);

    (*novoNOPai)->filhos[0] = (*novoNO1);
    (*novoNOPai)->filhos[1] = (*novoNO2);

    arvB_destroiNO(no);

    return novoNOPai;
}

int arvB_remove(ArvB *no, int valor)
{ 
    printf("Removendo o numero: %d\n", valor);

    ArvB aux = arvBBuscaRemove(no,valor);
    printf("testando buscaremove:\n");

    int auxt=ordem+1;


    if(*(aux->filhos) == NULL){
        // caso 1: tirar a FOLHA em um nó com numero maior que o min de chaves
        if(aux->qnt_chaves > ((ordem/2) -1)){
           for(int i =0; i<aux->qnt_chaves-1; i++){
                if(aux->chaves[i] == valor){
                    auxt =i;
                    aux->chaves[i] = aux->chaves[i+1];
                }
                else if(i > auxt){
                    aux->chaves[i] = aux->chaves[i+1];
                }
            }
            aux->qnt_chaves--;
        }    
    }
    return 1;


}

ArvB arvBBuscaRemove(ArvB* raiz, int valor){
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
        return aux; // Chave encontrada
    } else if (aux->filhos == NULL) {
        return 0; // Chave nao foi encontrada
    } else {
        return arvBBuscaRemove(&(aux->filhos[i]), valor); //procura recursivamente
    }
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
        printf("Nivel %d\n", nivel);
        for(int i = 0; i < nivel; i++)
            printf(" ");
        for(int i = 0; i < no->qnt_chaves; i++)
            printf("%d ", no->chaves[i]);
        printf("\n");
        for(int i = 0; i < no->qnt_chaves + 1; i++)
            imprimeNO(no->filhos[i], nivel + 1);
    }
}

void promocao(ArvB *no, int posicao, int valor)
{
    int aux = (*no)->filhos[posicao]->chaves[4];
}
