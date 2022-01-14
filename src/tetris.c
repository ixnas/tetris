#include "defaults.h"
#include "game.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
	initscr();
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
