#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ticTacToe.h"

#define X 'x'
#define O 'o'
#define EMPTY '-'
#define NONE 111 // should probably be changed to something other than an int
#define BOARD_LENGTH 9

bool isEmpty(char *board) {
    int idx = 0;

    while (idx < BOARD_LENGTH && board[idx] == EMPTY) {
        idx++;
    }

    return (idx == 9);
}

char getPlayer(char *board) {
    int emptyCount = 0;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        if (board[i] == EMPTY) {
            emptyCount++;
        }
    }

    if (emptyCount % 2 == 1) {
        return X;
    }
    return O;
}

int *getActions(char *board) {
    static int possibleActions[BOARD_LENGTH];
    int actionCount = 0;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        if (board[i] == EMPTY) {
            possibleActions[actionCount] = i;
            actionCount++;
        }
    }
   
    while (actionCount < BOARD_LENGTH) {
        possibleActions[actionCount] = NONE;
        actionCount++;
    }

    return possibleActions;
}

char *getResult(char *board, int action) {
    if (board[action] != EMPTY) {
       return NULL;
    }

    char player = getPlayer(board);
    static char newBoard[9];
    memcpy(newBoard, board, sizeof(newBoard));
    newBoard[action] = player;

    return newBoard;
}

char getWinner(char *board) {
    // Check row wins
    for (int i = 0; i < 3; i++) {
        if (board[i*3] == X && board[i*3 + 1] == X && board[i*3 + 2] == X) { return X; }
        if (board[i*3] == O && board[i*3 + 1] == O && board[i*3 + 2] == O) { return O; }
    }
    // Check column wins
    for (int i = 0; i < 3; i++) {
        if (board[0+i] == X && board[3+i] == X && board[6+i] == X) { return X; }
        if (board[0+i] == O && board[3+i] == O && board[6+i] == O) { return O; }
    }
    // Check diagonal wins
    if (board[0] == X && board[4] == X && board[8] == X) { return X; }
    if (board[0] == O && board[4] == O && board[8] == O) { return O; }
    if (board[2] == X && board[4] == X && board[6] == X) { return X; }
    if (board[2] == O && board[4] == O && board[6] == O) { return O; }

    return EMPTY;
}

bool isTerminal(char *board) {
    if (getWinner(board) != EMPTY) {
        return true;
    }

    for (int i = 0; i < BOARD_LENGTH; i++) {
        if (board[i] == EMPTY) {
            return false;
        }
    }

    return true;
}

int getUtility(char *board) {
    char winner = getWinner(board);
    if (winner == X) { return 1; }
    if (winner == O) { return -1; }
    return 0;
}

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int getMaxValue(char *board) {
    if (isTerminal(board)) {
        return getUtility(board);
    }

    int maxVal = INT_MIN;
    int *actions = getActions(board);
    int actions_idx = 0;
    while (actions[actions_idx] != NONE) {
        maxVal = max(maxVal, getMinValue(getResult(board, actions[actions_idx])));
    }
    
    return maxVal;
}

int getMinValue(char *board) {
    if (isTerminal(board)) {
        return getUtility(board);
    }

    int minVal = INT_MAX;
    int *actions = getActions(board);
    int actions_idx = 0;
    while (actions[actions_idx] != NONE) {
        minVal = min(minVal, getMaxValue(getResult(board, actions[actions_idx])));
    }

    return minVal;
}

/* Returns the optimal action for the current player on the board.
 */
int minimax(char *board) {
    if (isTerminal(board)) {
        return NONE;
    }

    // The best opening for X is any corner, hard coding that here.
    if (isEmpty(board)) {
        int cornerMove[4] = {0, 2, 6, 8};
        int randomInx = rand() % 4;
        return cornerMove[randomInx];
    }

    int bestMove = NONE;
    if (getPlayer(board) == X) {
        int utility = INT_MIN;
        int *actions = getActions(board);
        int actions_idx = 0;
        while (actions[actions_idx] != NONE) {
            int minVal = getMinValue(getResult(board, actions[actions_idx]));

            if (minVal > utility) {
                bestMove = actions[actions_idx];
                utility = minVal;
            }
        }
    }
    else {
        int utility = INT_MAX;
        int *actions = getActions(board);
        int actions_idx = 0;
        while (actions[actions_idx] != NONE) {
            int maxVal = getMaxValue(getResult(board, actions[actions_idx]));

            if (maxVal < utility) {
                bestMove = actions[actions_idx];
                utility = maxVal;
            }
        }
    }

    return bestMove;
}

void printBoard(char *board) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        if (i != 0 && i % 3 == 0) {
            printf("\n");
        }
        printf("%c", board[i]);
    }
    printf("\n");
}

// int main() {
//     srand(time(NULL)); // for opening move
// 
//     FILE *file_ptr;
//     char ch;
// 
//     file_ptr = fopen("inputFile.txt", "r");
//     if (file_ptr == NULL) {
//         perror("File can't be opened\n");
//         return EXIT_FAILURE;
//     }
// 
//     // Create the board from the input file.
//     char board[9];
//     int charCount = 0;
//     for (int i = 0; i < BOARD_LENGTH; i++) {
//         int ch = fgetc(file_ptr);
//         board[charCount] = (char)ch;
//         charCount++;
//     }
//     fclose(file_ptr);
// 
//     // Tests prints
//     printBoard(board);
// 
//     // getPlayer
//     printf("Next player: %c\n", getPlayer(board));
// 
//     // getActions
//     printf("Possible actions:\n");
//     int *actions = getActions(board);
//     int actions_idx = 0;
//     while (actions[actions_idx] != NONE) {
//         printf("%d,", actions[actions_idx]);
//         actions_idx++;
//     }
//     printf("\n");
// 
//     // getResult
//     actions_idx = 0;
//     while (actions[actions_idx] != NONE) {
//         char *newBoard = getResult(board, actions[actions_idx]);
//         for (int i = 0; i < BOARD_LENGTH; i++) {
//             printf("%c", newBoard[i]);
//         }
//         printf("\n");
// 
//         actions_idx++;
//     }
// 
//     printf("Is Terminal: %d\n", isTerminal(board));
// 
//     // getWinner
//     char x_winner[BOARD_LENGTH] = {X, X, X, O, O, EMPTY, EMPTY, EMPTY, EMPTY};
//     printBoard(x_winner);
//     printf("Winner: %c\n", getWinner(x_winner));
//     printf("Is Terminal: %d\n", isTerminal(x_winner));
//     printf("Utility: %d\n", getUtility(x_winner));
// 
//     char o_winner[BOARD_LENGTH] = {X, X, O, EMPTY, O, EMPTY, O, X, EMPTY};
//     printBoard(o_winner);
//     printf("Winner: %c\n", getWinner(o_winner));
//     printf("Utility: %d\n", getUtility(o_winner));
// 
//     char tie_board[BOARD_LENGTH] = {X, O, X, X, X, O, O, X, O};
//     printBoard(tie_board);
//     printf("Winner: %c\n", getWinner(tie_board));
//     printf("Utility: %d\n", getUtility(tie_board));
// 
//     char empty_board[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
//     printBoard(empty_board);
//     printf("isEmpty: %d\n", isEmpty(empty_board));
// 
//     printf("Best move: %d\n", minmax(board));
// 
//     // End test prints
// 
//     return 0;
// }
