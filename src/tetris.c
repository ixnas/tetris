#include <stdio.h>
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
	initscr();
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
