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

// Cadastro dos territórios
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

// Exibe os territórios cadastrados
void exibirMapa(Territorio *mapa, int quantidade) {

    printf("\n===== MAPA =====\n");
	
	int i = 0;
    for (i = 0; i < quantidade; i++) {

        printf("\nIndice: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Sorteia uma missão e copia para o jogador
void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes) {

    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão (passagem por valor)
void exibirMissao(char missao[]) {

    printf("\n===== SUA MISSAO =====\n");
    printf("%s\n", missao);
}

// Simulação de ataque
void atacar(Territorio *atacante,
            Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("%s tirou %d\n",
           atacante->nome,
           dadoAtacante);

    printf("%s tirou %d\n",
           defensor->nome,
           dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas =
            atacante->tropas / 2;

        if (tropasTransferidas < 1)
            tropasTransferidas = 1;

        atacante->tropas -= tropasTransferidas;
        defensor->tropas = tropasTransferidas;

    } else {

        printf("Defensor venceu!\n");

        if (atacante->tropas > 1)
            atacante->tropas--;
    }
}

// Verifica se a missão foi concluída
int verificarMissao(char *missao,
                    Territorio *mapa,
                    int tamanho) {

    int territoriosAzuis = 0;
	
	int i = 0;
    for (i = 0; i < tamanho; i++) {

        if (strcmp(mapa[i].cor, "Azul") == 0)
            territoriosAzuis++;
    }

    // Exemplo simples:
    // missão cumprida se possuir 3 territórios azuis

    if (strstr(missao, "3 territorios") != NULL) {

        if (territoriosAzuis >= 3)
            return 1;
    }

    return 0;
}

// Libera memória alocada
void liberarMemoria(Territorio *mapa,
                    char *missaoJogador) {

    free(mapa);
    free(missaoJogador);
}

int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    // Alocação dinâmica do mapa
    Territorio *mapa =
        calloc(quantidade, sizeof(Territorio));

    if (mapa == NULL) {

        printf("Erro de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    // Vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar o exercito Vermelho",
        "Eliminar o exercito Verde",
        "Conquistar metade do mapa",
        "Dominar os territorios inimigos"
    };

    int totalMissoes =
        sizeof(missoes) / sizeof(missoes[0]);

    // Memória dinâmica para missão
    char *missaoJogador =
        malloc(100 * sizeof(char));

    if (missaoJogador == NULL) {

        free(mapa);
        return 1;
    }

    atribuirMissao(
        missaoJogador,
        missoes,
        totalMissoes
    );

    // Exibida apenas uma vez
    exibirMissao(missaoJogador);

    exibirMapa(mapa, quantidade);

    int atacante;
    int defensor;

    printf("\nEscolha o territorio atacante: ");
    scanf("%d", &atacante);

    printf("Escolha o territorio defensor: ");
    scanf("%d", &defensor);

    if (atacante < 0 ||
        atacante >= quantidade ||
        defensor < 0 ||
        defensor >= quantidade) {

        printf("Indices invalidos!\n");

        liberarMemoria(
            mapa,
            missaoJogador
        );

        return 1;
    }

    if (strcmp(mapa[atacante].cor,
               mapa[defensor].cor) == 0) {

        printf(
            "Nao e permitido atacar "
            "territorios da mesma cor!\n"
        );

    } else {

        atacar(
            &mapa[atacante],
            &mapa[defensor]
        );

        exibirMapa(
            mapa,
            quantidade
        );

        // Verificação silenciosa da missão
        if (verificarMissao(
                missaoJogador,
                mapa,
                quantidade)) {

            printf(
                "\n*** MISSAO CUMPRIDA! "
                "VOCE VENCEU! ***\n"
            );
        }
    }

    liberarMemoria(
        mapa,
        missaoJogador
    );

    return 0;
}
