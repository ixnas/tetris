#include "shape.h"
#include <ncurses.h>

void CopyShape(struct Shape *old, struct Shape *new)
{
	int totalBlocks;

	new->LineSize = old->LineSize;
	new->ShapeSize = old->ShapeSize;
	new->X = old->X;
	new->Y = old->Y;
	new->ColorPair = old->ColorPair;

	totalBlocks = sizeof(old->Blocks) / sizeof(old->Blocks[0]);

	CopyArray(old->Blocks, new->Blocks, totalBlocks);
}

void SetupShape(struct Shape *shape, int shapeSize, int lineSize, int *blockIndexes, int blockIndexesSize, int colorPair)
{
	int *firstBlockIndex;
	int totalBlocks;
	firstBlockIndex = blockIndexes;
	totalBlocks = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);

	shape->ShapeSize = shapeSize;
	shape->LineSize = lineSize;
	shape->X = 3; // arbitrary center
	shape->Y = 0;
	shape->ColorPair = colorPair;

	for (int i = 0; i < totalBlocks; i++)
	{
		shape->Blocks[i] = *blockIndexes;
		blockIndexes++;
	}
}

int GetRotatedBlockPosition(int block, struct Shape *shape)
{
	int totalLines, currentLine, totalBlocks;

	totalBlocks = shape->ShapeSize;
	totalLines = totalBlocks / shape->LineSize;
	currentLine = block / totalLines;

	return ((block + 1) * totalLines - currentLine - 1) % totalBlocks;
}

void RotateShape(struct Shape *shape, int turns)
{
	int newBlockPosition;
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int newShape[size];
	CopyArray(shape->Blocks, newShape, size);

	for (int i = 0; i < size; i++)
	{
		newBlockPosition = shape->Blocks[i];
		for (int j = 0 ; j < turns; j++)
		{
			newBlockPosition = GetRotatedBlockPosition(newBlockPosition, shape);
		}
		newShape[i] = newBlockPosition;
	}

	SortArray(newShape, size);
	CopyArray(newShape, shape->Blocks, size);
}

void PrintShapeArray(struct Shape *shape)
{
	move(21, 0);
	int arrSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	printw("Local: ");
	for (int i = 0; i < arrSize; i++)
	{
		printw("%d ", shape->Blocks[i]);
	}
	refresh();
}
