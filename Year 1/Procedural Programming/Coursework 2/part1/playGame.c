#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "game.h"
#include "playGame.h"
#include "endGame.h"

/*
 * Controls the game logic from start to end
 */

void playGame(Game *game)
{
  char symbols[2] = {'X','O'}; // array of chars for each player

  // starting game
  printf("New game starting\n");
  showGame(game);
  
  // Each pass through the loop is one completed move by a player
  for (; game->turns < game->maxTurns; game->turns++)
  {
    char player_symbol = symbols[game->turns % 2]; // allocate player a char based on number of turns that have occured

    // Request a move from the next player and check it is valid (an unused square within the board)
    printf("Player %c: Enter your move as row column values:\n", player_symbol); // requesting player move
    
    int move_check = makeMove(game, player_symbol); // function to validate player move (1 for correct move, 0 if not)
    
    // looping until correct input
    while (move_check == 0)
    {
      printf("Move rejected. Please try again\n"); // use this message if move cannot be made
      move_check = makeMove(game, player_symbol); // asking for input again
    }

    // After each completed move display the board 
    showGame(game);

    // After each valid move, testing for win or draw using functions in endGame.c
    int win_check = winGame(game, player_symbol); // testing for win by the respective player (1 means player has won, 0 means otherwise)
    if (win_check == 1)
    {
      printf("Player %c has won\n", player_symbol); // use to announce a winner - game is over
      return; // end playGame function
    }

    // check if the player has drawn by analysing is anyone has won, as well as the number of moves made throughout the game, and compare it to max turns possible
    else if (win_check == 0 && game->turns == game->maxTurns - 1)
    {
      printf("Match is drawn\n"); // use to announce a draw - game is over
      return; // end playGame function
    }
  }

  return; // end playGame function
}

/*
 * Display the game board - do not adjust the formatting
 */

// function to output the game board in required format for autograder
void showGame(Game *game)
{
  printf("\n");
  printf("      0  1  2\n");
  printf("\n");
  printf(" 0    %c  %c  %c\n",game->board[0][0],game->board[0][1],game->board[0][2]);
  printf(" 1    %c  %c  %c\n",game->board[1][0],game->board[1][1],game->board[1][2]);
  printf(" 2    %c  %c  %c\n",game->board[2][0],game->board[2][1],game->board[2][2]);
  printf("\n");

  return;
}

/*
 * Read in the players chosen location
 * Check that the input is a valid empty square
 * If valid then update the board (return 1)
 * If invalid reject the move (return 0)
 */

int makeMove(Game *game, char symbol)
{
  // read the players move from the keyboard, expected as two integers coordinates as shown on the board 
  
  // check for user input
  // the following takes regard for input of any size
  // reference: Anon n.d. How to read from stdin with fgets()? Stack Overflow. [Online]. [Accessed 12 December 2022]. Available from: https://stackoverflow.com/questions/3919009/how-to-read-from-stdin-with-fgets.
  char *input = calloc(1,1); // create 1 array of size 1
  char buffer[20]; // create buffer array to read input to

  // repeat scanning for input until break command
  while(fgets(buffer, 20, stdin))
  {
    input = realloc(input, strlen(input)+1+strlen(buffer)); // reallocate the input array to size of buffer and '\0'
    strcat(input, buffer); // concatentate the arrays together

    if (strlen(buffer) != 19) // is the length of the buffer indicating the end of the inputted statement, if so, break loop
    {
      break;
    }
  }

  // extracting necessary variables from input array
  int row;
  int column;
  int check; // necessary for return if something has been stored to this variable

  int var_count = sscanf(buffer, "%i %i %i ", &row, &column, &check); // scan string to pull row and column variables. returns number of varibles scanned

  // running checks
  // checking for correct number of variables read (must be 2)
  if (var_count != 2) 
  {
    return 0;
  }

  // checking if inputs are acceptable for the size of the board
  if (row < 0 || row >= game->boardSize || column < 0 || column >= game->boardSize)
  {
    return 0;
  }

  // checking if the location has not been taken
  if (game->board[row][column] != '.')
  {
    return 0;
  }

  // after checks, move is valid. Update the board
  game->board[row][column] = symbol;
  
  // free the input variable
  free(input);

  return 1; // move accepted
}

