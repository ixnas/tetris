#include "draw.h"
#include "world.h"
#include <ncurses.h>

void DrawChar(int x, int y, char c)
{
	mvaddch(y, x * 2, c);
}

void DrawEmpty(int x, int y)
{
	DrawChar(x, y, '.');
}

void DrawBlock(int x, int y)
{
	DrawChar(x, y, 'x');
}

void DrawEmptyBoard()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			DrawEmpty(x, y);
		}
	}
}

void DrawWorld()
{
	int size = sizeof(World.Cells) / sizeof(World.Cells[0]);
	int totalLines = size / World.LineSize;
	int x, y;

	for (int i = 0; i < size; i++)
	{
		if (World.Cells[i] != -1)
		{
			y = World.Cells[i] / World.LineSize;
			x = World.Cells[i] - (World.LineSize * y);
			DrawChar(x, y, '#');
			move(24, 0);
			printw("%d %d", x, y);
		}
	}

}

void DrawShape(struct Shape *shape)
{
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int totalLines = shape->ShapeSize / shape->LineSize;
	int x, y;

	for (int i = 0; i < size; i++)
	{
		y = shape->Blocks[i] / totalLines;
		x = shape->Blocks[i] - (shape->LineSize * y);
		DrawBlock(x + shape->X, y + shape->Y);
	}
}