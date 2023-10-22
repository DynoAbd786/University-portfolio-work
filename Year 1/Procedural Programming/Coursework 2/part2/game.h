
/*
 * data structure for the game
 */

// hardcoding max and min board size as required by part 2
#define MAX_BOARD_SIZE 8
#define MIN_BOARD_SIZE 3

// hardcoding the min win length as per part 2 spec
#define MIN_WIN_LENGTH 3

typedef struct _game {
  char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];    // board for storing the game state
  int boardSize;       // board size 
  int winLength;       // length of a winning line
  int maxTurns;        // maximum possible moves
  int turns;           // current number of moves
  int adjacencyCount;  // identifying a match of 2 variables 
} Game;

