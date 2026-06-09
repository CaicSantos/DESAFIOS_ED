#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int quantidade) {
	int i = 0;
    for (i = 0; i < quantidade; i++) {
        printf("\n=== Territorio %d ===\n", i + 1);

        printf("Nome: ");
        scanf("%29s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio *mapa, int quantidade) {
    printf("\n===== MAPA ATUAL =====\n");
	
	int i = 0;
    for (i= 0; i < quantidade; i++) {
        printf("\nIndice: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n===== BATALHA =====\n");
    printf("Atacante (%s) tirou: %d\n",
           atacante->nome, dadoAtacante);

    printf("Defensor (%s) tirou: %d\n",
           defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("\nO atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas;

    } else {

        printf("\nO defensor venceu!\n");

        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

// Função para liberar memória alocada
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = calloc(quantidade, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    printf("\nTerritorios cadastrados com sucesso!\n");
    exibirTerritorios(mapa, quantidade);

    int indiceAtacante;
    int indiceDefensor;

    printf("\n===== ATAQUE =====\n");

    printf("Escolha o indice do territorio atacante: ");
    scanf("%d", &indiceAtacante);

    printf("Escolha o indice do territorio defensor: ");
    scanf("%d", &indiceDefensor);

    // Validação dos índices
    if (indiceAtacante < 0 || indiceAtacante >= quantidade ||
        indiceDefensor < 0 || indiceDefensor >= quantidade) {

        printf("Indices invalidos!\n");
        liberarMemoria(mapa);
        return 1;
    }

    // Não permite atacar território da mesma cor
    if (strcmp(mapa[indiceAtacante].cor,
               mapa[indiceDefensor].cor) == 0) {

        printf("Nao e permitido atacar um territorio da mesma cor!\n");

    } else {

        atacar(&mapa[indiceAtacante],
               &mapa[indiceDefensor]);

        printf("\n===== RESULTADO =====\n");
        exibirTerritorios(mapa, quantidade);
    }

    liberarMemoria(mapa);

    return 0;
}
