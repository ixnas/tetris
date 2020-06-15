#include "shape_t.h"

void SetupShapeT()
{
	char shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	char blockIndexes[blockIndexesSize];

	blockIndexes[0] = 1;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(&T, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
