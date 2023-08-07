#include <stdio.h>
#include "ArvoreBEstrela.h"

int main() {
    // Criando uma árvore B com 3 chaves, todas inicializadas como -1 e filhos igual a NULL
    ArvB* minhaArvore = arvB_cria();

    // Verificando se a árvore foi criada corretamente
    if (minhaArvore == NULL || *minhaArvore == NULL) {
        printf("Falha ao criar a arvore!\n");
        return 1;
    }

    // Acessando as chaves da árvore
    int i;

    printf("Quantidade de chaves: %d\n", (*minhaArvore)->qnt_chaves);
    printf("Chaves: ");
    for (i = 0; i < ordem - 1; i++) {
        printf("%d ", (*minhaArvore)->chaves[i]);
    }
    printf("\n");

    // Lembre-se de liberar a memória alocada para a árvore quando não for mais necessária
    // Coloque isso após ter terminado de usar a árvore e não precisar mais dela
    
    arvB_destroi(minhaArvore);

    return 0;
}