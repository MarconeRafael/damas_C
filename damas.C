#include <stdio.h>
#include <stdlib.h>

// Função para verificar se uma posição é segura para colocar uma rainha
int posSeg(int **tabuleiro, int linha, int coluna, int n) {
    int i, j;

    // Verificar a mesma coluna
    for (i = 0; i < linha; i++) {
        if (tabuleiro[i][coluna] == 1) {
            return 0;
        }
    }

    // Verificar a diagonal superior esquerda
    for (i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) {
        if (tabuleiro[i][j] == 1) {
            return 0;
        }
    }

    // Verificar a diagonal superior direita
    for (i = linha, j = coluna; i >= 0 && j < n; i--, j++) {
        if (tabuleiro[i][j] == 1) {
            return 0;
        }
    }

    return 1;
}

// Função para resolver o problema das N rainhas usando backtracking
int resolve(int **tabuleiro, int n, int linha) {
    int coluna;

    // Caso base: todas as rainhas foram colocadas
    if (linha == n) {
        return 1;
    }

    // Tentar colocar uma rainha em cada coluna da linha atual
    for (coluna = 0; coluna < n; coluna++) {
        if (posSeg(tabuleiro, linha, coluna, n)) {
            // Colocar uma rainha nesta posição
            tabuleiro[linha][coluna] = 1;

            // Recursivamente tentar colocar as rainhas nas linhas restantes
            if (resolve(tabuleiro, n, linha + 1)) {
                return 1;  // Encontrou uma solução válida
            }

            // Se não encontrou uma solução válida, voltar atrás e tentar a próxima coluna
            tabuleiro[linha][coluna] = 0;
        }
    }

    return 0;  // Não foi possível encontrar uma solução
}
// Função para criar uma matriz de tamanho n x n
int **criarMatriz(int n) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
    }

    return matriz;
}

// Função para liberar a memória alocada para a matriz
void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Função para exibir o tabuleiro com as rainhas posicionadas
void exibirTabuleiro(int **tabuleiro, int n) {
    for (int i = 0; i <n; i++) {
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] == 1) {
                printf(" Q ");
            } else {
                printf(" ◦ ");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;

    printf("Digite o tamanho do tabuleiro (N): ");
    scanf("%d", &n);

    int **tabuleiro = criarMatriz(n);

    if (!resolve(tabuleiro, n, 0)) {
        printf("Não foi possível encontrar uma solução para o tabuleiro %dx%d.\n", n, n);
    } else {
        printf("Solução encontrada para o tabuleiro %dx%d:\n", n, n);
        exibirTabuleiro(tabuleiro, n);
    }

    liberarMatriz(tabuleiro, n);

    return 0;
}
