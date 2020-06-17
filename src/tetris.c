#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ncurses.h>
#include "game.h"

const int MIN_X = 10;
const int MIN_Y = 20;

bool ScreenSizeOk()
{
	int x, y;

	getmaxyx(stdscr, x, y);

	return x >= MIN_X * 2 && y >= MIN_Y;
}

void PlayGame()
{
	struct Game game;
	SetupGame(&game);
	Loop(&game);
}

void ShowErrorScreenNotOk()
{
	printf("Screen too small\n");
}

int main()
{
	curs_set(0);
	struct timeval tm;
	gettimeofday(&tm, NULL);
	srand(tm.tv_sec + tm.tv_usec * 1000000ul);
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_BLUE);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_CYAN);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	attron(COLOR_PAIR(1));
	keypad(stdscr, 1);
	if (ScreenSizeOk())
	{
		PlayGame();
		endwin();
	}
	else
	{
		endwin();
		ShowErrorScreenNotOk();
	}

	return 0;
}
