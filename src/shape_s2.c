#include "shape_s2.h"

void SetupShapeS2()
{
	char shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	char blockIndexes[blockIndexesSize];

	blockIndexes[0] = 3;
	blockIndexes[1] = 4;
	blockIndexes[2] = 7;
	blockIndexes[3] = 8;

	SetupShape(&S2, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
