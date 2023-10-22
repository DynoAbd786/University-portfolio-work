#include <stdlib.h>

#include "game.h"
#include "initGame.h"


/*
 * Intialise game data for a new game
 */

Game *initGame(int boardSize, int winLength) 
{
  // checking board size and win length fall within the required limits as per spec from part 2
  if (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE )
  {
    return NULL;
  }

  if (winLength < MIN_WIN_LENGTH || winLength > boardSize)
  {
    return NULL;
  }

  // allocate the Game data structure
  Game *game = malloc(sizeof(Game));
  
  // intialise the Game data structure values
  game->boardSize = boardSize;
  game->winLength = winLength;
  game->maxTurns = boardSize * boardSize;
  game->turns = 0;
  game->adjacencyCount = 0;

  // board values should be set to '.' (unused location)
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      game->board[i][j] = '.';
    }
  }
  
  // return empty table
  return game;
}