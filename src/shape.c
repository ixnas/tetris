#include "shape.h"
#include <ncurses.h>

static int GetRotatedBlockPosition(int block, struct Shape* shape)
{
	int totalLines, currentLine, totalBlocks;

	totalBlocks = shape->ShapeSize;
	totalLines = totalBlocks / shape->LineSize;
	currentLine = block / totalLines;

	return ((block + 1) * totalLines - currentLine - 1) % totalBlocks;
}

void SetupShape(struct Shape* shape, int shapeSize, int lineSize, int* blockIndexes, int blockIndexesSize,
                int colorPair)
{
	int* firstBlockIndex;
	int totalBlocks, i;
	firstBlockIndex = blockIndexes;
	totalBlocks = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);

	shape->ShapeSize = shapeSize;
	shape->LineSize = lineSize;
	shape->X = 3; /* arbitrary center */
	shape->Y = 0;
	shape->ColorPair = colorPair;

	for (i = 0; i < totalBlocks; i++)
	{
		shape->Blocks[i] = *blockIndexes;
		blockIndexes++;
	}
}

void RotateShape(struct Shape* shape, int turns)
{
	int newBlockPosition, i, j;
	int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
	int newShape[size];
	CopyArray(shape->Blocks, newShape, size);

	for (i = 0; i < size; i++)
	{
		newBlockPosition = shape->Blocks[i];
		for (j = 0; j < turns; j++)
		{
			newBlockPosition = GetRotatedBlockPosition(newBlockPosition, shape);
		}
		newShape[i] = newBlockPosition;
	}

	SortArray(newShape, size);
	CopyArray(newShape, shape->Blocks, size);
}
