#include <stdio.h>
#include <string.h>

// Estrutura que representa um território do jogo War
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    // Vetor para armazenar os 5 territórios
    Territorio territorios[5];

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    // Laço para entrada dos dados dos territórios
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        scanf("%29s", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf("%9s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== TERRITORIOS CADASTRADOS ===\n\n");
	
	int n = 0;
    for (n = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-------------------------\n");
    }

    return 0;
}
