
/*
 * Purpose: 2-player game of tic-tac-toe
 * Author: Daniel Chen
 * Date: Feb 25, 2018
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define WIN 1
#define IN_PROGRESS 0
#define TIE -1
#define CROSS 'X'
#define NOUGHT 'O'
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define TRUE 1
#define FALSE 0
#define SIZE 3                   /* size of board can be 3 or 4 */
#define ROWSIZE SIZE * 4 + 1     /* number of characters on a row */
#define STARS "*****"

void initBoard(char board[][SIZE]);
int switchPlayer(int player);
void makeMove(char board[][SIZE], int player, char marker);
int updateBoard(char board[][SIZE], int choice, char marker);
int updateStatus(char board[][SIZE], char marker);
int checkRows(char board[][SIZE], char marker);
int checkRow(char board[], char marker);
int checkCols(char board[][SIZE], char marker);
int checkCol(char board[][SIZE], int col, char marker);
int checkDiagonals(char board[][SIZE], char marker);
int checkMainDiagonal(char board[][SIZE], char marker);
int checkCounterDiagonal(char board[][SIZE], char marker);
int isBoardFull(char board[][SIZE]);
void displayResult(int status, int player);
void clearScreen(void);
void displayBoard(char markerForPlayer[], char board[][SIZE]);
void displayHeader(char markerForPlayer[]);
void displayBoardRow(char boardRow[]);
void displayBoardRowSeparator(void);

int main(void) {
	char markerForPlayer[] = { CROSS, NOUGHT };
	char board[SIZE][SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
	int status = IN_PROGRESS;
	int player = PLAYER_TWO;

	initBoard(board);

	while (status == IN_PROGRESS) {
		player = switchPlayer(player);
		displayBoard(markerForPlayer, board);
		makeMove(board, player, markerForPlayer[player]);
		status = updateStatus(board, markerForPlayer[player]);
	}

	displayBoard(markerForPlayer, board);
	displayResult(status, player);

	system("PAUSE");
	return 0;
}

/*
 * Purposes: initializes the tic-tac-toe board with numbers that can
 *           be used by players to indicate which position they want to mark
 * Param: board - the tic-tac-toe board
 */
void initBoard(char board[][SIZE]) {
	int row;
	int col;
	char next = '0';

	for (row = 0; row < SIZE; row++) {
		for (col = 0; col < SIZE; col++) {
			board[row][col] = next;
			next++;
			if (next == '8' + 1)
				next = 'a';
		}
	}
}

/*
 * Purpose: switch from one player to the other
 * Param: player - the current player
 * Returns: the next player
 */
int switchPlayer(int player) {
	
  if (player)
    return PLAYER_ONE;

	return PLAYER_TWO;
}

/*
 * Purpose: performs a single move for given player; rejects moves
 *          to cells that are already occupied and prompts user to
 *          choose again.
 * Assume:  user enters a valid number corresponding to a position
 *          on the board
 * Param:   board - the tic tac toe board
 * Param:   player - the player whose turn is next
 * Param:   marker - the character the player uses to mark a position
 *                   on the board
 */
void makeMove(char board[][SIZE], int player, char marker) {
	int choice;

	do {
		printf("\nPlayer %d, enter a number: ", player);
		scanf("%d", &choice);
	} while (!updateBoard(board, choice, marker));
}

/*
 * Purpose: marks selected cell on board with given marker
 *          if choice is valid and cell is not already occupied
 * Param: board - the tic tac toe board
 * Param: choice - the cell to be marked
 * Param: marker - the character used to mark the cell
 * Returns: TRUE if cell is empty and successfully marked; 
 *          FALSE if choice is not valid or cell has already been marked
 */
int updateBoard(char board[][SIZE], int choice, char marker) {
	
  int row = choice / SIZE;
	int col = choice % SIZE;
  
  if (choice < 0 || choice > SIZE * SIZE)
    return FALSE;
  
  if (board[row][col] != CROSS && board[row][col] != NOUGHT){
    board[row][col] = marker;
    return TRUE;
  }
    
	return FALSE;
}

/*
 * Purpose: update game status - check for win or tie
 *          for player with given marker
 * Param: board - the tic tac toe board
 * Param: marker - the marker to check
 * Returns: WIN if player with marker has won
 *          IN_PROGRESS if game has not yet ended
 *          TIE if game is tied
*/
int updateStatus(char board[][SIZE], char marker) {
  
	if (checkRows(board, marker))
		return WIN;

	if (checkCols(board, marker))
		return WIN;

	if (checkDiagonals(board, marker))
		return WIN;

	if (!isBoardFull(board)) {
		return IN_PROGRESS;
	}

	return TIE;
}

/*
 * Purpose: checks if there is a row filled with marker 
 * Param: board - the tic tac toe board
 * Param: marker - the marker to be checked
 * Returns: TRUE if there is a row filled with marker,
 *          FALSE otherwise
 */
int checkRows(char board[][SIZE], char marker) {
	int row;

	for (row = 0; row < SIZE; row++) {
		if (checkRow(board[row], marker))
			return TRUE;
	}

	return FALSE;
}

/*
 * Purpose: checks if row is filled with marker
 * Param: boardRow - one row of the tic tac toe board 
 * Param: marker - the marker to be checked
 * Returns: TRUE if row is filled with marker,
 *          FALSE otherwise
 */
int checkRow(char boardRow[], char marker) {
	int index;

	for (index = 0; index < SIZE; index++) {
		if (boardRow[index] != marker)
			return FALSE;
	}

	return TRUE;
}

/*
 * Purpose: checks if there is a column filled with marker
 * Param: board - the tic tac toe board
 * Param: marker - the marker to be checked
 * Returns: TRUE if there is a column filled with marker,
 *          FALSE otherwise
*/
int checkCols(char board[][SIZE], char marker) {
	int col;

	for (col = 0; col < SIZE; col++) {
		if (checkCol(board, col, marker))
			return TRUE;
	}

	return FALSE;
}

/*
 * Purpose: checks if column is filled with marker
 * Param: board - the tic tac toe board
 * Param: col - index of column to be checked
 * Param: marker - the marker to be checked
 * Returns: TRUE if specified column is filled with marker
 *          FALSE otherwise
 */
int checkCol(char board[][SIZE], int col, char marker) {
	int row;

	for (row = 0; row < SIZE; row++) {
		if (board[row][col] != marker)
			return FALSE;
	}

	return TRUE;
}

/*
 * Purpose: checks if there is a diagonal filled with marker
 * Param: board - the tic tac toe board
 * Param: marker - the marker to be checked 
 * Returns: TRUE if there is a diagonal filled with marker
 *          FALSE otherwise
*/
int checkDiagonals(char board[][SIZE], char marker) {

  if (checkMainDiagonal(board,marker))
    return TRUE;

  if (checkCounterDiagonal(board, marker))
    return TRUE;

	return FALSE;
}

/*
 * Purpose: checks if main diagonal is filled with marker
 * Param: board - the tic tac toe board
 * Param: marker - the marker to be checked
 * Returns: TRUE if main diagonal is filled with marker,
 *          FALSE otherwise
 */
int checkMainDiagonal(char board[][SIZE], char marker) {
	
  int index;

  for (index = 0; index < SIZE; index++){
    if (board[index][index] != marker)
      return FALSE;
  }
	return TRUE;
}

/*
* Purpose: checks if counter diagonal is filled with marker
* Param: board - the tic tac toe board
* Param: marker - the marker to be checked
* Returns: TRUE if counter diagonal is filled with marker,
*          FALSE otherwise
*/
int checkCounterDiagonal(char board[][SIZE], char marker) {
	
  int index;

  for (index = 0; index < SIZE; index++){
    if (board[index][SIZE - index - 1] != marker)
      return FALSE;
  }
	return TRUE;
}

/*
 * Purpose: checks to see if board is full
 * Param: board - the tic tac toe board
 * Returns: TRUE if board is full, FALSE otherwise
*/
int isBoardFull(char board[][SIZE]) {
	
  int row;
	int col;

	for (row = 0; row < SIZE; row++) {
		for (col = 0; col < SIZE; col++) {
            if (board[row][col] != CROSS || board[row][col] != NOUGHT)
            return FALSE;
    }
  }
	return TRUE;
}

/*
 * Purpose: displays final result
 * Param: status - the game status
 * Param: the player who won (if game was not tied)
*/
void displayResult(int status, int player) {
	printf("\n\n");
	printf(STARS);
	if (status == WIN) {
		printf(" Player %d won! ", player);
	}
	else {
		printf(" It's a draw! ");
	}
	printf(STARS);
	printf("\n\n");
}

/*
 * Purpose: displays the board 
 * Param: markerForPlayer - array of markers used by players
 * Param: board - the tic tac toe board
*/
void displayBoard(char markerForPlayer[], char board[][SIZE]) {
	int row;

	clearScreen();
	displayHeader(markerForPlayer);

	for (row = 0; row < SIZE; row++) {
		displayBoardRowSeparator();
		displayBoardRow(board[row]);
	}
	displayBoardRowSeparator();
}

/*
 * Purpose: displays header showing markers used by each player
 * Param: markerForPlayer - array of markers used by players
 */
void displayHeader(char markerForPlayer[]) {
	printf("\n\nTic Tac Toe\n");
	printf("Player %d [%c], Player %d [%c]\n\n", 
		PLAYER_ONE, markerForPlayer[PLAYER_ONE], 
		PLAYER_TWO, markerForPlayer[PLAYER_TWO]);
}

/*
 * Purpose: displays single row of board
 * Param: boardRow - a single row of the tic tac toe board
*/
void displayBoardRow(char boardRow[]) {
	int index;

	for (index = 0; index < SIZE; index++) {
		printf("|");
		printf(" %c ", boardRow[index]);
	}

	printf("|\n");
}

/*
 * Purpose: display row separator for board
 */
void displayBoardRowSeparator(void) {
	int count;

	for (count = 0; count < ROWSIZE; count++) {
		printf("-");
	}

	printf("\n");
}

/*
 * Purpose: clears the screen
 */
void clearScreen(void) {

	system("cls"); 
}
