#include "shape_line.h"

void SetupShapeLine()
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 16;
	lineSize = 4;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 4;
	blockIndexes[1] = 5;
	blockIndexes[2] = 6;
	blockIndexes[3] = 7;

	SetupShape(&Line, shapeSize, lineSize, blockIndexes, blockIndexesSize, 5);
}
