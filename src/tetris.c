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
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_GREEN, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_RED, COLOR_BLACK);
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
