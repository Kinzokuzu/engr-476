#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ticTacToe.h"

#define BOARD_LENGTH 9

int main() {
    // Open file with current board state
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read board state from file
    char board[BOARD_LENGTH];
    for (int i = 0; i < BOARD_LENGTH; i++) {
        board[i] = fgetc(file);
    }
    fclose(file);

    // Print current board state
    printf("Current board state:\n");
    printBoard(board);

    // Print best move
    int bestMove = minimax(board);
    printf("Best move:\n");
    // char newBoard[BOARD_LENGTH];
    setNewBoard(board, bestMove, board);
    printBoard(board);

    // Write optimal move sequence to file
    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < BOARD_LENGTH; i++) {
        fputc(board[i], file);
    }
    fputc('\n', file);

    // Play game until terminal state
    while (!isTerminal(board)) {
        bestMove = minimax(board);
        setNewBoard(board, bestMove, board);
        printBoard(board);
        for (int i = 0; i < BOARD_LENGTH; i++) {
            fputc(board[i], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}
