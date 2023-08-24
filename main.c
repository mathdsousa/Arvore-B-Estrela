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
//    teste = verifica_se_raiz(minhaArvore,42);
//    printf("se raiz: %d\n",teste);
        arvB_insere(minhaArvore, 48);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 58);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 28);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 18);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 8);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 37);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 22);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 15);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 17);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 25);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 26);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 27);

    imprime(minhaArvore);

        arvB_insere(minhaArvore, 72);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 73);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 74);

    imprime(minhaArvore);
        arvB_insere(minhaArvore, 75);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 76);
    imprime(minhaArvore);
    arvB_insere(minhaArvore, 23);

    imprime(minhaArvore);
    arvB_insere(minhaArvore,24);

    imprime(minhaArvore);

    arvB_insere(minhaArvore, 29);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 3);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 4);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 5);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 6);
    imprime(minhaArvore);


    arvB_insere(minhaArvore, 62);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 63);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 64);
    imprime(minhaArvore);

    arvB_insere(minhaArvore, 65);
    imprime(minhaArvore);

    arvB_destroi(minhaArvore);

    return 0;
}