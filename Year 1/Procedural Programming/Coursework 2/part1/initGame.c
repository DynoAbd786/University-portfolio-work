#include <stdlib.h>

#include "game.h"
#include "initGame.h"


/*
 * Intialise game data for a new game
 */

Game *initGame(int boardSize, int winLength) 
{
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