#include <stdio.h>
#include <stdlib.h>

#define TAM 10

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Navio horizontal
    for (int j = 1; j <= 4; j++)
        tabuleiro[2][j] = 3;

    // Navio vertical
    for (int i = 5; i <= 8; i++)
        tabuleiro[i][7] = 3;

    // Diagonal principal
    for (int i = 0; i < 4; i++)
        tabuleiro[i][i] = 3;

    // Diagonal secundária
    for (int i = 0; i < 4; i++)
        tabuleiro[i][9 - i] = 3;
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("Tabuleiro com navios (3):\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void aplicarHabilidade(int ataque[TAM][TAM], int tipo, int centroX, int centroY) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            switch (tipo) {
                case 1: // Cone para baixo
                    if (i >= centroX && abs(j - centroY) <= (i - centroX))
                        ataque[i][j] = 1;
                    break;
                case 2: // Cruz
                    if (i == centroX || j == centroY)
                        ataque[i][j] = 1;
                    break;
                case 3: // Octaedro
                    if (abs(i - centroX) + abs(j - centroY) <= 2)
                        ataque[i][j] = 1;
                    break;
            }
        }
    }
}

void exibirResultado(int tabuleiro[TAM][TAM], int ataque[TAM][TAM]) {
    printf("Resultado do ataque (X = acerto, * = erro):\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (ataque[i][j] == 1) {
                if (tabuleiro[i][j] == 3)
                    printf("X ");
                else
                    printf("* ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM][TAM];
    int ataque[TAM][TAM] = {0};

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    exibirTabuleiro(tabuleiro);

    printf("Escolha uma habilidade de ataque:\n");
    printf("1 - Cone\n2 - Cruz\n3 - Octaedro\n> ");
    int tipoAtaque;
    scanf("%d", &tipoAtaque);

    int centroX = 5, centroY = 5; // Centro padrão do ataque
    aplicarHabilidade(ataque, tipoAtaque, centroX, centroY);
    exibirResultado(tabuleiro, ataque);

    return 0;
}
