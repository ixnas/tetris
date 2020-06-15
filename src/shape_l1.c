#include "shape_l1.h"

void SetupShapeL1()
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 0;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(&L1, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
