#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBEstrela.h"

int main()
{
    ArvB *minhaArvore = arvB_cria();

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 1);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 10);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 20);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 30);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 40);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 60);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 50);

    imprime(minhaArvore); 

    arvB_insere(minhaArvore, 80);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 2);

    imprime(minhaArvore);
    
    arvB_insere(minhaArvore, 51);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 21);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 61);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 31);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 41);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 70);

    imprime(minhaArvore);
    
    //printf("%d", (*minhaArvore)->chaves[0]);

    int teste = arvB_busca(minhaArvore, 31);
    printf("teste da busca: %d\n", teste);

    teste = arvB_qtd_nos(minhaArvore);
    printf("numero de nos: %d\n", teste);

    teste = arvB_qtd_chaves(minhaArvore);
    printf("numero de chaves: %d\n", teste);

    printf("testando remocao\n");
    teste = arvB_remove(minhaArvore,50);
    imprime(minhaArvore);


    arvB_destroi(minhaArvore);

    return 0;
}