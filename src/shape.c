#include "shape.h"
#include <ncurses.h>

void CopyShape(struct Shape *old, struct Shape *new)
{
	int totalBlocks;

	new->LineSize = old->LineSize;
	new->ShapeSize = old->ShapeSize;

	totalBlocks = sizeof(old->Blocks)/sizeof(old->Blocks[0]);
	CopyArray(old->Blocks, new->Blocks, totalBlocks);
}

void SetupShape(struct Shape *shape, char shapeSize, char lineSize, char *blockIndexes, char blockIndexesSize)
{
	bool block;
	char *firstBlockIndex;
	char totalBlocks;
	firstBlockIndex = blockIndexes;
	totalBlocks = sizeof(shape->Blocks)/sizeof(shape->Blocks[0]);

	shape->ShapeSize = shapeSize;
	shape->LineSize = lineSize;

	for (char i = 0; i < totalBlocks; i++)
	{
		block = 0;

		for (char j = 0; j < blockIndexesSize; j++)
		{
			if (*blockIndexes == i)
			{
				block = 1;
			}
			blockIndexes++;
		}
		blockIndexes = firstBlockIndex;

		shape->Blocks[i] = block;
	}
}

char GetRotatedBlockPosition(char block, struct Shape *shape)
{
	char totalLines, currentLine, totalBlocks;

	totalBlocks = shape->ShapeSize;
	totalLines = totalBlocks / shape->LineSize;
	currentLine = block / totalLines;

	return ((block + 1) * totalLines - currentLine - 1) % totalBlocks;
}

void RotateShape(struct Shape *shape)
{
	char newBlockPosition;
	char size = shape->ShapeSize;
	bool newShape[size];
	bool *shapeFirst = shape->Blocks;
	CopyArray(shape->Blocks, newShape, size);

	for (char i = 0; i < size; i++)
	{
		newBlockPosition = GetRotatedBlockPosition(i, shape);
		newShape[newBlockPosition] = shape->Blocks[i];
	}

	CopyArray(newShape, shapeFirst, size);
}

void PrintShapeArray(struct Shape *shape)
{
	move(21, 0);
	for (char i = 0; i < 16; i++)
	{
		printw("%d", shape->Blocks[i]);
	}

	refresh();
}
