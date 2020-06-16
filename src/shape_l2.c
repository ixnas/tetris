#include "shape_l2.h"

void SetupShapeL2()
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 2;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(&L2, shapeSize, lineSize, blockIndexes, blockIndexesSize, 4);
}
