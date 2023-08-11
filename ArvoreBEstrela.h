// Arquivo ArvoreBEstrela.h
#ifndef ARVOREBESTRELA_H
#define ARVOREBESTRELA_H

#define ordem 8 //número máximo de filhos

typedef struct NO* ArvB;

// Definição do Tipo de Nó
struct NO 
{
    int qnt_chaves;
    int *chaves; 
    ArvB *filhos;
};

ArvB* arvB_cria();
void arvB_criaNO()
void arvB_destroi(ArvB *raiz);
// int arvB_insere(ArvB* raiz, int valor);
int arvB_remove(ArvB *raiz, int valor);
int arvB_busca(ArvB *raiz, int valor);
int arvB_qtd_nos(ArvB *raiz);
int arvB_qtd_chaves(ArvB *raiz);
void arvB_destroiNo(ArvB no);
void imprime(ArvB *raiz);
void imprimeNO(ArvB no);

#endif