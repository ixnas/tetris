#include "draw.h"
#include <ncurses.h>

void DrawChar(char x, char y, char c)
{
	mvaddch(y, x * 2, c);
}

void DrawEmpty(char x, char y)
{
	DrawChar(x, y, '.');
}

void DrawBlock(char x, char y)
{
	DrawChar(x, y, 'x');
}

void DrawEmptyBoard()
{
	for (char x = 0; x < 10; x++)
	{
		for (char y = 0; y < 20; y++)
		{
			DrawEmpty(x, y);
		}
	}
}

void DrawShape(struct Shape *shape, char offsetX, char offsetY)
{
	int x, y;

	x = 0;
	y = 0;

	for (char i = 0; i < shape->ShapeSize; i++)
	{
		if (x == shape->LineSize)
		{
			y++;
			x = 0;
		}

		if (shape->Blocks[i] == 1)
		{
			DrawBlock(x + offsetX, y + offsetY);
		}

		x++;
	}
}