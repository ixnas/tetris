#include "shape_l1.h"

void SetupShapeL1()
{
	char shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	char blockIndexes[blockIndexesSize];

	blockIndexes[0] = 0;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(&L1, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
