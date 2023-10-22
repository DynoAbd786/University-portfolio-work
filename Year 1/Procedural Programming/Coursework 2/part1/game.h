
/*
 * data structure for the game
 */

// hardcoding board size and win length as required by part 1
#define BOARD_SIZE 3 
#define WIN_LENGTH 3

typedef struct _game {
  char board[BOARD_SIZE][BOARD_SIZE];    // board for storing the game state
  int boardSize;       // board size 
  int winLength;       // length of a winning line
  int maxTurns;        // maximum possible moves
  int turns;           // current number of moves
  int adjacencyCount;  // identifying a match of 2 variables 
} Game;

