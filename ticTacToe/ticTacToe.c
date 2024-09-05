#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    return (emptyCount % 2 == 1) ? X : O;
}

void setActions(char *board, int *actions) {
    int actionCount = 0;
    for (int i = 0; i < BOARD_LENGTH; i++) {
        if (board[i] == EMPTY) {
            actions[actionCount] = i;
            actionCount++;
        }
    }
   
    while (actionCount < BOARD_LENGTH) {
        actions[actionCount] = NONE;
        actionCount++;
    }
}

void setNewBoard(char *board, int action, char *newBoard) {
    if (board[action] != EMPTY) {
       return; 
    }

    for (int i = 0; i < BOARD_LENGTH; i++) {
        newBoard[i] = board[i];
    }
    newBoard[action] = getPlayer(board);
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
    int actions[BOARD_LENGTH];
    setActions(board, actions);
    for (int i = 0; actions[i] != NONE; i++) {
        char newBoard[BOARD_LENGTH];
        setNewBoard(board, actions[i], newBoard);
        int newVal = getMinValue(newBoard);
        maxVal = max(newVal, maxVal);
    }
    
    return maxVal;
}

int getMinValue(char *board) {
    if (isTerminal(board)) {
        return getUtility(board);
    }

    int minVal = INT_MAX;
    int actions[BOARD_LENGTH];
    setActions(board, actions);
    for (int i = 0; actions[i] != NONE; i++) {
        char newBoard[BOARD_LENGTH];
        setNewBoard(board, actions[i], newBoard);
        int newVal = getMaxValue(newBoard);
        minVal = min(newVal, minVal);
    }

    return minVal;
}

int minimax(char *board) {
    if (isTerminal(board)) {
        return NONE;
    }

    // The best opening for X is any corner, hard coding that here.
    if (isEmpty(board)) {
        int cornerMove[4] = {0, 2, 6, 8};
        srand(time(NULL));
        int randomInx = rand() % 4;
        return cornerMove[randomInx];
    }

    int bestMove = NONE;
    if (getPlayer(board) == X) {
        int utility = INT_MIN;
        int actions[BOARD_LENGTH];
        setActions(board, actions);
        int actions_idx = 0;
        while (actions[actions_idx] != NONE) {
            char newBoard[BOARD_LENGTH];
            setNewBoard(board, actions[actions_idx], newBoard);
            int minVal = getMinValue(newBoard);

            if (minVal > utility) {
                bestMove = actions[actions_idx];
                utility = minVal;
            }

            actions_idx++;
        }
    }
    else {
        int utility = INT_MAX;
        int actions[BOARD_LENGTH];
        setActions(board, actions);
        int actions_idx = 0;
        while (actions[actions_idx] != NONE) {
            char newBoard[BOARD_LENGTH];
            setNewBoard(board, actions[actions_idx], newBoard);
            int maxVal = getMaxValue(newBoard);

            if (maxVal < utility) {
                bestMove = actions[actions_idx];
                utility = maxVal;
            }

            actions_idx++;
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
