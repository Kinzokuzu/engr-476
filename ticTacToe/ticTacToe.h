#include <stdbool.h>

/** Returns true if no moves have been made, returns false otherwise.
 */
bool isEmpty(char *board);

/** Returns the player who has the next turn.
 */
char getPlayer(char *board);

/* Fills an array with all possible actions available on the board.
 */
void setActions(char *board, int *actions);

/* Sets the new board that results from making a move.
 */
void setNewBoard(char *board, int action, char *newBoard);

/* Returns the winner of the game, if there is one.
 */
char getWinner(char *board);

/* Returns true if the game is over, false otherwise.
 */
bool isTerminal(char *board);

/* Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
 */
int getUtility(char *board);

/** Returns the maximum utility from minValue(result(board, action)).
 */
int getMaxValue(char *board);

/** Returns the minimum utility from maxValue(result(board, action)).
 */
int getMinValue(char *board);

/* Returns the optimal action for the current player on the board.
 */
int minimax(char *board);

/** Prints the board as a 3x3 matrix
 */
void printBoard(char *board);
