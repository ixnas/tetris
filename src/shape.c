#include "shape.h"
#include <ncurses.h>

void CopyShape(struct Shape *old, struct Shape *new)
{
	int totalBlocks;

	new->LineSize = old->LineSize;
	new->ShapeSize = old->ShapeSize;

	totalBlocks = sizeof(old->Blocks) / sizeof(old->Blocks[0]);

	CopyArray(old->Blocks, new->Blocks, totalBlocks);
}

void SetupShape(struct Shape *shape, int shapeSize, int lineSize, int *blockIndexes, int blockIndexesSize)
{
	int *firstBlockIndex;
	int totalBlocks;
	firstBlockIndex = blockIndexes;
	totalBlocks = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);

	shape->ShapeSize = shapeSize;
	shape->LineSize = lineSize;

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

void RotateShape(struct Shape *shape)
{
	int newBlockPosition;
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int newShape[size];
	CopyArray(shape->Blocks, newShape, size);

	for (int i = 0; i < size; i++)
	{
		newBlockPosition = GetRotatedBlockPosition(shape->Blocks[i], shape);
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
