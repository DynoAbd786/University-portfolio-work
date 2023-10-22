
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "playGame.h"
#include "initGame.h"

/*
 * main function: program entry point
 */

int main(int argc, char *argv[])
{
  // checking for incorrect number of command line arguements
  if (argc != 3)
  {
    printf("Incorrect parameter values for board size or win length. Exiting\n");
    return 1;
  }
  
  // converting (if possible) board size and win length arguements to integers
  int board_size = atoi(argv[1]);
  int win_length = atoi(argv[2]);

  // checking for sucessful conversion
  if (board_size == 0 || win_length == 0)
  {
    printf("Incorrect parameter values for board size or win length. Exiting\n");
    return 2;
  }

  Game *game; // pointer for the game structure

  // allocate memory and assign starting values to the structure
  game = initGame(board_size, win_length);

  // checking if returned game is NULL, due to any erroneous data provided from command line arguements
  if (game == NULL)
  {
    printf("Incorrect parameter values for board size or win length. Exiting\n");
    return 3;
  }
  
  // play a full game
  playGame(game);

  free(game); // free heap memory that was used

  return 0;
}

