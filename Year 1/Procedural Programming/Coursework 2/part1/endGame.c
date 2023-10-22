#include <stdio.h>

#include "game.h"
#include "endGame.h"

/*
 * Functions in this module check for wins
 */

// test all possible ways the game can be won for one player
int winGame(Game *game, char symbol)
{
  // looping through the board
  for (int i = 0; i < game->boardSize; i++)
  {
    for (int j = 0; j < game->boardSize; j++)
    {
      // set the adjacency variable to 0 for no matches
      game->adjacencyCount = 0;

      // check if the variable in the board matches the requested symbol 
      if (game->board[i][j] == symbol)
      {
        // check necessary adjacent characters
        if (game->board[i][j + 1] == symbol)
        {
          game->adjacencyCount = 1; // indicate 1 for match of 2 variables
          // check if the adjacency leads on in the table, and see if the adjacency is long enough to count the player to win
          if (adjacency_check(game, symbol, i, j + 1, 0, 1) == 1)
          {
            return 1; // return 1 if game has been won
          }
        }

        for (int n = -1; n <= 1; n++)
        {
          if (game->board[i + 1][j + n] == symbol)
          {
            game->adjacencyCount = 1; // indicate 1 for match of 2 variables
            // check if the adjacency leads on in the table, and see if the adjacency is long enough to count the player to win
            if (adjacency_check(game, symbol, i + 1, j + n, 1, n) == 1)
            {
              return 1; // return 1 if game has been won
            }
          }
        }
      }
    }
  }

return 0;  // continue game

// checks here are presented as follows:
// for every correctly identified variable, we look around for any other matching variables in the order:
// ~  ~  ~
// ~  0  C
// C  C  C
// where ~ is not checked, 0 is the position for the variable used to check around, and C is a position for where the variable needs to be checked for matches
// reason for this method: all previous values have already been checked and as such, shouldn't need to be checked again
}


int adjacency_check(Game *game, char symbol, int row_pos, int column_pos, int row_dir, int column_dir)
{
  // function takes input the position on the board and checks if the same character in the direction specified by the winGame function
  // function is recursive (I think)
  // returns 1 if the checks indicate a win in the specified direction, 0 if no win detected in such direction

  // allocate new position to check variable from
  int new_row = row_pos + row_dir;
  int new_column = column_pos + column_dir;
  
  // checking if the new postion is within the board.
  if (new_row < 0 || new_row >= game->boardSize || new_column < 0 || new_column >= game->boardSize)
  {
    return 0; // return 0 for no win
  }

  // checking if the new position does contain the same symbol in the relative direction
  if (game->board[new_row][new_column] == symbol)
  {
    game->adjacencyCount++; // add 1 to the adjacency count

    // checking if the adjaceny count matches the win length
    // adjacencyCount is used for indicating a match of 2 of the same characters, thus why winLength needs - 1
    if (game->adjacencyCount == game->winLength - 1)
    {
      return 1; // return true if win is detected
    }
    else
    {
      // move to the next location in the given direction, recursively, and return the answer from that
      if (adjacency_check(game, symbol, new_row, new_column, row_dir, column_dir) == 1)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }

  return 0; // return if function has not detected a win
}

