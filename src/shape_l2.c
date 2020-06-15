#include "shape_l2.h"

void SetupShapeL2()
{
	char shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	char blockIndexes[blockIndexesSize];

	blockIndexes[0] = 2;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(&L2, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
