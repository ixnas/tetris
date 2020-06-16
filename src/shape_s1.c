#include "shape_s1.h"

void SetupShapeS1()
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 4;
	blockIndexes[1] = 5;
	blockIndexes[2] = 6;
	blockIndexes[3] = 7;

	SetupShape(&S1, shapeSize, lineSize, blockIndexes, blockIndexesSize, 6);
}