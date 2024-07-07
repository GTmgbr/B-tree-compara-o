#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "btree2.h"

int main() {
    int opcao, matricula;
    char nomeArquivo[100];
    ArvoreB *arvore = criarArvoreB();

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Criar índice\n");
        printf("2. Procurar elementos\n");
        printf("3. Remover registro\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo para criar o índice: ");
                scanf("%s", nomeArquivo);
                criarIndice(arvore, nomeArquivo);
                printf("Índice criado a partir do arquivo %s.\n", nomeArquivo);
                break;
            case 2:
                printf("Digite a matrícula a ser buscada: ");
                scanf("%d", &matricula);

                // contagem de tempo consulta btree
                clock_t inicioBTree = clock();
                int linha = buscarElemento(arvore->raiz, matricula);
                clock_t fimBTree = clock();
                double tempoBTree = (double)(fimBTree - inicioBTree) / CLOCKS_PER_SEC;
                printf("Tempo de busca na B-Tree: %f segundos\n", tempoBTree);

                // contagem de tempo consulta arquivo
                clock_t inicioArquivo = clock();
                if (linha != -1) {
                    buscarNoArquivo(nomeArquivo, linha);
                    clock_t fimArquivo = clock();
                    double tempoArquivo = (double)(fimArquivo - inicioArquivo) / CLOCKS_PER_SEC;
                    printf("Tempo de busca no Arquivo: %f segundos\n", tempoArquivo);
                } else {
                    printf("Matrícula %d não encontrada.\n", matricula);
                }
                break;
            case 3:
                printf("Digite a matrícula a ser removida: ");
                scanf("%d", &matricula);
                remover(arvore, matricula);
                printf("Matrícula %d removida do índice.\n", matricula);
                break;
            case 4:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}