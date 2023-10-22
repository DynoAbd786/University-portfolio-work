
# code details

EXE = ./tictactoe      
SRC = initGame.c main.c playGame.c endGame.c                 # ** list source code here **
OBJ = initGame.o main.o playGame.o endGame.o                 # ** list object code here **

# generic build details

CC     = gcc
CFLAGS = -std=c99 -Wall -g
CLIBS  = 
CLINK  = -lm

# compile to object code

%.o: %.c
	$(CC) -c $(CFLAGS) $(CLIBS) $< -o $@

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: game.h main.c initGame.h playGame.h
initGame.o: game.h initGame.h initGame.c 
playGame.o: game.h playGame.h playGame.c endGame.h
endGame.o: game.h endGame.h endGame.c
