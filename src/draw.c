#include "draw.h"
#include "world.h"
#include <ncurses.h>

void DrawChar(int x, int y, char c)
{
	mvaddch(y, x * 2, c);
	mvaddch(y, x * 2 + 1, ' ');
}

void DrawBlock(int x, int y)
{
	DrawChar(x + 1, y + 1, ' ');
}

void DrawEmptyBoard(struct World *world)
{
	int i, j;
	int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
	int lines = worldSize / world->LineSize;
	attron(COLOR_PAIR(4));
	for (i = 0; i < world->LineSize + 2; i++)
	{
		DrawChar(i, 0, '0');
		DrawChar(i, lines + 1, '0');
	}
	for (i = 1; i <= lines; i++)
	{
		DrawChar(0, i, '0');
		DrawChar(world->LineSize + 1, i, '0');
		attron(COLOR_PAIR(1));
		for (j = 1; j <= world->LineSize; j++)
		{
			DrawChar(j, i, ' ');
		}
		attron(COLOR_PAIR(4));
	}
	attron(COLOR_PAIR(1));
}

void DrawWorld()
{
	int size = sizeof(World.Cells) / sizeof(World.Cells[0]);
	int x, y, i;

	for (i = 0; i < size; i++)
	{
		if (World.Cells[i] != -1)
		{
			y = i / World.LineSize;
			x = i - (World.LineSize * y);
			attron(COLOR_PAIR(World.Cells[i]));
			DrawBlock(x, y);
			attron(COLOR_PAIR(1));
		}
	}
}

void DrawShape(struct Shape *shape)
{
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int totalLines = shape->ShapeSize / shape->LineSize;
	int x, y, i;

	attron(COLOR_PAIR(shape->ColorPair));
	for (i = 0; i < size; i++)
	{
		y = shape->Blocks[i] / totalLines;
		x = shape->Blocks[i] - (shape->LineSize * y);
		DrawBlock(x + shape->X, y + shape->Y);
	}
	attron(COLOR_PAIR(1));
}