#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ticTacToe.h"

#define X 'x'
#define O 'o'
#define EMPTY '-'
#define NONE 111 // should probably be changed to something other than an int
#define BOARD_LENGTH 9

void test_isEmpty() {
    char emptyBoard[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char nonEmptyBoard1[BOARD_LENGTH] = {'X', EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char nonEmptyBoard2[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 'O'};

    printf("testing an empty board\n");
    assert(isEmpty(emptyBoard) == true);

    printf("testing a non-empty board with a mark at the beginning\n");
    assert(isEmpty(nonEmptyBoard1) == false);

    printf("testing a non-empty board with a mark at the end\n");
    assert(isEmpty(nonEmptyBoard2) == false);

    printf("testing a non-empty board with a mix of marks\n");
    char mixedBoard[BOARD_LENGTH] = {'X', 'O', ' ', ' ', ' ', ' ', 'X', 'O', ' '};
    assert(isEmpty(mixedBoard) == false);
}

void test_getPlayer() {
    char emptyBoard[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char oneMoveBoard[BOARD_LENGTH] = {X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char twoMovesBoard[BOARD_LENGTH] = {X, O, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char threeMovesBoard[BOARD_LENGTH] = {X, O, X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char fullBoard[BOARD_LENGTH] = {X, O, X, O, X, O, X, O, X}; // Already filled, but technically shouldn't happen in a valid game.

    printf("testing an empty board\n");
    assert(getPlayer(emptyBoard) == X);

    printf("testing a board with one move\n");
    assert(getPlayer(oneMoveBoard) == O);

    printf("testing a board with two moves\n");
    assert(getPlayer(twoMovesBoard) == X);

    printf("testing a board with three moves\n");
    assert(getPlayer(threeMovesBoard) == O);

    printf("testing a full board\n");
    assert(getPlayer(fullBoard) == O);
}

// Helper function to compare expected and actual results
void compareResults(int *actual, int *expected) {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        assert(actual[i] == expected[i]);
    }
}

void test_getActions() {
    char emptyBoard[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char oneMoveBoard[BOARD_LENGTH] = {X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char fullBoard[BOARD_LENGTH] = {X, O, X, O, X, O, X, O, X};
    char mixedBoard[BOARD_LENGTH] = {X, EMPTY, O, EMPTY, X, EMPTY, O, EMPTY, X};

    int expectedEmptyBoard[BOARD_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int expectedOneMoveBoard[BOARD_LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8, NONE};
    int expectedFullBoard[BOARD_LENGTH] = {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE};
    int expectedMixedBoard[BOARD_LENGTH] = {1, 3, 5, 7, NONE, NONE, NONE, NONE, NONE};

    printf("testing an empty board\n");
    compareResults(getActions(emptyBoard), expectedEmptyBoard);

    printf("testing a board with one move\n");
    compareResults(getActions(oneMoveBoard), expectedOneMoveBoard);

    printf("testing a full board\n");
    compareResults(getActions(fullBoard), expectedFullBoard);

    printf("testing a mixed board\n");
    compareResults(getActions(mixedBoard), expectedMixedBoard);
}
// Helper function to compare boards
void compareBoards(char *actual, char *expected) {
    assert(memcmp(actual, expected, BOARD_LENGTH) == 0);
}

void test_getResult() {
    char emptyBoard[BOARD_LENGTH] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char oneMoveBoard[BOARD_LENGTH] = {X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char fullBoard[BOARD_LENGTH] = {X, O, X, O, X, O, X, O, X};
    char invalidMoveBoard[BOARD_LENGTH] = {X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

    char expectedAfterFirstMove[BOARD_LENGTH] = {X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char expectedAfterSecondMove[BOARD_LENGTH] = {X, O, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
    char expectedAfterThirdMove[BOARD_LENGTH] = {X, O, X, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

    printf("testing an empty board\n");
    compareBoards(getResult(emptyBoard, 0), expectedAfterFirstMove);

    printf("testing a board with one move\n");
    compareBoards(getResult(oneMoveBoard, 1), expectedAfterSecondMove);

    printf("testing a board with two moves\n");
    compareBoards(getResult(expectedAfterSecondMove, 2), expectedAfterThirdMove);

    printf("testing an invalid move\n");
    assert(getResult(invalidMoveBoard, 0) == NULL);

    printf("testing a full board\n");
    assert(getResult(fullBoard, 0) == NULL);
}

void test_getWinner() {
    printf("testing no winner yet\n");
    char noWinnerBoard[BOARD_LENGTH] = {X, O, X, O, X, O, O, X, EMPTY};
    assert(getWinner(noWinnerBoard) == EMPTY);

    printf("testing X wins with a row\n");
    char rowWinX[BOARD_LENGTH] = {X, X, X, O, O, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getWinner(rowWinX) == X);

    printf("testing O wins with a row\n");
    char rowWinO[BOARD_LENGTH] = {O, O, O, X, X, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getWinner(rowWinO) == O);

    printf("testing X wins with a column\n");
    char columnWinX[BOARD_LENGTH] = {X, O, EMPTY, X, O, EMPTY, X, EMPTY, EMPTY};
    assert(getWinner(columnWinX) == X);

    printf("testing O wins with a column\n");
    char columnWinO[BOARD_LENGTH] = {O, X, EMPTY, O, X, EMPTY, O, EMPTY, EMPTY};
    assert(getWinner(columnWinO) == O);

    printf("testing X wins with a diagonal\n");
    char diagonalWinX1[BOARD_LENGTH] = {X, O, EMPTY, EMPTY, X, O, EMPTY, EMPTY, X};
    assert(getWinner(diagonalWinX1) == X);

    char diagonalWinX2[BOARD_LENGTH] = {EMPTY, O, X, EMPTY, X, O, X, EMPTY, EMPTY};
    assert(getWinner(diagonalWinX2) == X);

    printf("testing O wins with a diagonal\n");
    char diagonalWinO1[BOARD_LENGTH] = {O, X, EMPTY, EMPTY, O, X, EMPTY, EMPTY, O};
    assert(getWinner(diagonalWinO1) == O);

    char diagonalWinO2[BOARD_LENGTH] = {EMPTY, X, O, EMPTY, O, X, O, EMPTY, EMPTY};
    assert(getWinner(diagonalWinO2) == O);

    printf("testing full board but no winner\n");
    char fullBoardNoWinner[BOARD_LENGTH] = {X, O, X, O, O, X, X, X, O};
    assert(getWinner(fullBoardNoWinner) == EMPTY);
}

void test_isTerminal() {
    printf("testing no winner and board is not full\n");
    char noWinnerNotFull[BOARD_LENGTH] = {X, O, X, O, X, O, O, X, EMPTY};
    assert(isTerminal(noWinnerNotFull) == false);

    printf("testing X wins with a row\n");
    char rowWinX[BOARD_LENGTH] = {X, X, X, O, O, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(isTerminal(rowWinX) == true);

    printf("testing O wins with a column\n");
    char columnWinO[BOARD_LENGTH] = {O, X, EMPTY, O, X, EMPTY, O, EMPTY, EMPTY};
    assert(isTerminal(columnWinO) == true);

    printf("testing O wins with a diagonal\n");
    char diagonalWinO[BOARD_LENGTH] = {O, X, X, EMPTY, O, X, EMPTY, EMPTY, O};
    assert(isTerminal(diagonalWinO) == true);

    printf("testing full board with no winner\n");
    char fullBoardNoWinner[BOARD_LENGTH] = {X, O, X, O, O, X, X, X, O};
    assert(isTerminal(fullBoardNoWinner) == true);

    printf("testing board not full, and no winner yet\n");
    char notFullNoWinner[BOARD_LENGTH] = {X, O, X, EMPTY, O, EMPTY, X, EMPTY, EMPTY};
    assert(isTerminal(notFullNoWinner) == false);
}

void test_getUtility() {
    printf("testing X wins\n");
    char xWins[BOARD_LENGTH] = {X, X, X, O, O, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getUtility(xWins) == 1);

    printf("testing O wins\n");
    char oWins[BOARD_LENGTH] = {O, O, O, X, X, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getUtility(oWins) == -1);

    printf("testing no winner, board not full\n");
    char noWinner[BOARD_LENGTH] = {X, O, X, O, X, O, O, X, EMPTY};
    assert(getUtility(noWinner) == 0);

    printf("testing no winner, board full\n");
    char draw[BOARD_LENGTH] = {X, O, X, O, O, X, X, X, O};
    assert(getUtility(draw) == 0);

    printf("testing X wins with a diagonal\n");
    char xWinsDiagonal[BOARD_LENGTH] = {X, O, EMPTY, EMPTY, X, O, EMPTY, EMPTY, X};
    assert(getUtility(xWinsDiagonal) == 1);

    printf("testing O wins with a column\n");
    char oWinsColumn[BOARD_LENGTH] = {O, X, EMPTY, O, X, EMPTY, O, EMPTY, EMPTY};
    assert(getUtility(oWinsColumn) == -1);
}

void test_minMaxFunctions() {
    printf("testing terminal board with X winning\n");
    char xWins[BOARD_LENGTH] = {X, X, X, O, O, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getMaxValue(xWins) == 1);
    assert(getMinValue(xWins) == 1);

    printf("testing terminal board with O winning\n");
    char oWins[BOARD_LENGTH] = {O, O, O, X, X, EMPTY, EMPTY, EMPTY, EMPTY};
    assert(getMaxValue(oWins) == -1);
    assert(getMinValue(oWins) == -1);

    printf("testing draw\n");
    char draw[BOARD_LENGTH] = {X, O, X, O, O, X, X, X, O};
    assert(getMaxValue(draw) == 0);
    assert(getMinValue(draw) == 0);

    printf("testing non-terminal board, X's turn, X should maximize\n");
    char xTurn[BOARD_LENGTH] = {X, O, X, O, O, EMPTY, X, EMPTY, EMPTY};
    assert(getMaxValue(xTurn) == 1);
    assert(getMinValue(xTurn) == 1);

    printf("testing non-terminal board, O's turn, O should minimize\n");
    char oTurn[BOARD_LENGTH] = {X, O, X, O, EMPTY, EMPTY, X, EMPTY, EMPTY};
    assert(getMaxValue(oTurn) == 0);
    assert(getMinValue(oTurn) == 0);
}

int main() {
    printf("\nRunning unit tests\n");

    printf("\n[test_isEmpty]\n");
    test_isEmpty();

    printf("\n[test_getPlayer]\n");
    test_getPlayer();

    printf("\n[test_getActions]\n");
    test_getActions();

    printf("\n[test_getResult]\n");
    test_getResult();

    printf("\n[test_getWinner]\n");
    test_getWinner();

    printf("\n[test_isTerminal]\n");
    test_isTerminal();

    printf("\n[test_getUtility]\n");
    test_getUtility();

    printf("\n[test_minMaxFunctions]\n");
    test_minMaxFunctions();

    printf("\nAll tests passed\n");
    return 0;
}
