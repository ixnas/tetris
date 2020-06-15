#include <stdio.h>
#include <ncurses.h>
#include "array_tools.h"
#include "world.h"
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

void PrintShapeWorldCoordinates(struct Shape *shape, int offsetX, int offsetY)
{
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int coordinates[size];

	for (int i = 0; i < size; i++)
	{
		coordinates[i] = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, offsetX, offsetY);
	}

	move(22, 0);
	printw("World: ");
	for (int i = 0; i < size; i++)
	{
		printw("%d ", coordinates[i]);
	}
}

void Loop(struct Shape *shape)
{
	int x, y, c;
	struct Collision collision;

	x = 0;
	y = 0;

	while (1)
	{
		DrawEmptyBoard();
		DrawShape(shape, x, y);
		DrawWorld();
		PrintShapeArray(shape);
		PrintShapeWorldCoordinates(shape, x, y);
		CheckCollision(shape, x, y, &collision);
		refresh();
		c = getch();
		switch (c)
		{
		case 'q':
			return;
		case ' ':
			RotateShape(shape);
			if (CheckClipping(shape, x, y))
			{
				for (int i = 0; i < 3; i++) RotateShape(shape);
			}
			break;
		case KEY_DOWN:
			if (!collision.Bottom)
			{
				y++;
			}
			break;
		case KEY_LEFT:
			if (!collision.Left)
			{
				x--;
			}
			break;
		case KEY_RIGHT:
			if (!collision.Right)
			{
				x++;
			}
			break;
		case 'l':
			AddToWorld(shape, x, y);
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
		SetupWorld();
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
