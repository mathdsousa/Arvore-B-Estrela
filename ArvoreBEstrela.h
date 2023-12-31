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
    ArvB pai;
}; // Acho que vai ser preciso um campo para o pai

ArvB* arvB_cria();
void arvB_criaNO(ArvB *no);
int arvB_destroi(ArvB *raiz);
int arvB_novaInsere(ArvB* no, int valor, int raiz);
void arvB_destroiNO(ArvB* no);
int arvB_insere(ArvB* raiz, int valor);
int arvB_insereNO(ArvB* no, int valor); // Retorna um valor de chave em caso de overflow ou -2 se deu certo;
ArvB* split(ArvB* no, int valor);
int arvB_remove(ArvB *raiz, int valor);
int arvB_busca(ArvB *raiz, int valor);
int arvB_qtd_nos(ArvB *raiz);
int arvB_qtd_chaves(ArvB *raiz);
void imprime(ArvB* raiz);
void imprimeNO(ArvB no, int nivel);
void promocao(ArvB *no, int posicao, int valor);
void ajustaNO(ArvB* no, int valor, int posicao);
ArvB arvBBuscaRemove(ArvB* raiz, int valor);
//int verifica_se_raiz(ArvB* raiz, int chave);
#endif