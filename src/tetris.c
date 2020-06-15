#include <stdio.h>
#include <ncurses.h>
#include "arrcopy.h"
#include "draw.h"
#include "shape.h"
#include "shape_block.h"
#include "shape_l1.h"
#include "shape_l2.h"
#include "shape_line.h"
#include "shape_s1.h"
#include "shape_s2.h"
#include "shape_t.h"

const int MIN_X = 10;
const int MIN_Y = 20;

void SetupShapes()
{
	SetupShapeLine();
	SetupShapeL1();
	SetupShapeL2();
	SetupShapeS1();
	SetupShapeS2();
	SetupShapeT();
	SetupShapeBlock();
}

bool ScreenSizeOk()
{
	int x, y;

	getmaxyx(stdscr, x, y);

	return x >= MIN_X * 2 && y >= MIN_Y;
}

void Loop(struct Shape *shape)
{
	int c;
	char x, y;

	x = 0;
	y = 0;

	while (1)
	{
		DrawEmptyBoard();
		DrawShape(shape, x, y);
		PrintShapeArray(shape);
		refresh();
		c = getch();
		switch (c)
		{
		case 'q':
			return;
		case ' ':
			RotateShape(shape);
			break;
		case KEY_DOWN:
			y++;
			break;
		case KEY_LEFT:
			x--;
			break;
		case KEY_RIGHT:
			x++;
			break;
		}
	}
}

void PlayGame()
{
	struct Shape shape;
	CopyShape(&T, &shape);
	Loop(&shape);
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
		SetupShapes();
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
