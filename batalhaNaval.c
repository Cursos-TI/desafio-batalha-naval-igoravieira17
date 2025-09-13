#include <stdio.h>
#include <stdbool.h>

#define N 10          // tamanho do tabuleiro (NxN)
#define SHIP 3        // valor que representa navio no tabuleiro
#define SHIP_SIZE 3   // tamanho fixo dos navios

/* ---- utilitário: imprime a matriz do tabuleiro ---- */
void printBoard(int board[N][N]) {
    printf("\n=== TABULEIRO (0=agua, 3=navio) ===\n\n   ");
    for (int c = 0; c < N; c++) printf("%d ", c);
    printf("\n");
    for (int r = 0; r < N; r++) {
        printf("%2d ", r);
        for (int c = 0; c < N; c++) printf("%d ", board[r][c]);
        printf("\n");
    }
}

/* ---- validações de limites ---- */
bool fitsHorizontal(int row, int col) { return row >= 0 && row < N && col >= 0 && col + SHIP_SIZE - 1 < N; }
bool fitsVertical  (int row, int col) { return col >= 0 && col < N && row >= 0 && row + SHIP_SIZE - 1 < N; }

/* ---- validação de sobreposição ---- */
bool freeHorizontal(int b[N][N], int row, int col) { for (int c = col; c < col + SHIP_SIZE; c++) if (b[row][c] != 0) return false; return true; }
bool freeVertical  (int b[N][N], int row, int col) { for (int r = row; r < row + SHIP_SIZE; r++) if (b[r][col] != 0) return false; return true; }

/* ---- posicionadores ---- */
bool placeHorizontal(int b[N][N], int row, int col) {
    if (!fitsHorizontal(row, col)) { printf("ERRO: H fora dos limites em (%d,%d)\n", row, col); return false; }
    if (!freeHorizontal(b, row, col)) { printf("ERRO: H sobreposto em (%d,%d)\n", row, col); return false; }
    printf("Navio H em: ");
    for (int c = col; c < col + SHIP_SIZE; c++) { b[row][c] = SHIP; printf("(%d,%d) ", row, c); }
    printf("\n"); return true;
}

bool placeVertical(int b[N][N], int row, int col) {
    if (!fitsVertical(row, col)) { printf("ERRO: V fora dos limites em (%d,%d)\n", row, col); return false; }
    if (!freeVertical(b, row, col)) { printf("ERRO: V sobreposto em (%d,%d)\n", row, col); return false; }
    printf("Navio V em: ");
    for (int r = row; r < row + SHIP_SIZE; r++) { b[r][col] = SHIP; printf("(%d,%d) ", r, col); }
    printf("\n"); return true;
}

int main(void) {
    /* 1) Tabuleiro: toda água (0) */
    int board[N][N] = {0};

    /* 2) “modelos” dos navios (didático) */
    int navioH[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    int navioV[SHIP_SIZE] = {SHIP, SHIP, SHIP};
    (void)navioH; (void)navioV; // só para evitar warning

    /* 3) Coordenadas iniciais (definidas no código) */
    int hRow = 2, hCol = 1; // horizontal ocupará (2,1)(2,2)(2,3)
    int vRow = 5, vCol = 7; // vertical   ocupará (5,7)(6,7)(7,7)

    /* 4) Posicionamento com validação */
    printf("=== Posicionamento dos Navios ===\n");
    bool okH = placeHorizontal(board, hRow, hCol);
    bool okV = placeVertical  (board, vRow, vCol);

    /* 5) Exibição do tabuleiro */
    if (okH && okV) printBoard(board);
    else printf("\nCoordenadas invalidas: ajuste e execute novamente.\n");

    return 0;
}