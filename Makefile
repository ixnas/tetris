all:
	CC -std=c89 -Wall -O3 -o bin/tetris -lncurses src/*.c
