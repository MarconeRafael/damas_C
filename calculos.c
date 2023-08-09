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
    // Caso base: todas as rainhas foram colocadas
    if (linha == n) {
        return 1;
    }

    int totalSolucoes = 0;

    // Tentar colocar uma rainha em cada coluna da linha atual
    for (int coluna = 0; coluna < n; coluna++) {
        if (posSeg(tabuleiro, linha, coluna, n)) {
            // Colocar uma rainha nesta posição
            tabuleiro[linha][coluna] = 1;

            // Recursivamente tentar colocar as rainhas nas linhas restantes
            totalSolucoes += resolve(tabuleiro, n, linha + 1);

            // Voltar atrás e tentar a próxima coluna
            tabuleiro[linha][coluna] = 0;
        }
    }

    return totalSolucoes;
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tabuleiro[i][j] == 1) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Função para calcular a quantidade de soluções para cada valor de N
int calcularSolucoes(int n) {
    int **tabuleiro = criarMatriz(n);
    int totalSolucoes = resolve(tabuleiro, n, 0);
    liberarMatriz(tabuleiro, n);
    return totalSolucoes;
}

int main() {
    int n;

    printf("Digite o tamanho máximo do tabuleiro (N): ");
    scanf("%d", &n);

    if (n < 8) {
        printf("N deve ser maior ou igual a 8 para exibir as soluções.\n");
        return 0;
    }

    // Array para armazenar as quantidades de soluções
    int solucoes[21] = {0}; // Índice 0 é ignorado, apenas para usar os índices de 1 a 20

    // Calcular as soluções para cada valor de N de 1 a n
    for (int i = 1; i <= n; i++) {
        solucoes[i] = calcularSolucoes(i);
    }

    // Exibir as quantidades de soluções para N >= 8
    printf("Quantidade de soluções para cada N de 8 a %d:\n", n);
    for (int i = 8; i <= n; i++) {
        printf("N=%d: %d soluções\n", i, solucoes[i]);
    }

    // Gerar gráfico usando gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "plot '-' with lines title 'Soluções por N'\n");
        for (int i = 8; i <= n; i++) {
            fprintf(gnuplotPipe, "%d %d\n", i, solucoes[i]);
        }
        fprintf(gnuplotPipe, "e\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    } else {
        printf("Erro ao executar gnuplot.\n");
    }

    return 0;
}
