#include "shape_block.h"

void SetupShapeBlock()
{
	char shapeSize, lineSize, blockIndexesSize;

	shapeSize = 4;
	lineSize = 2;
	blockIndexesSize = 4;

	char blockIndexes[blockIndexesSize];

	blockIndexes[0] = 0;
	blockIndexes[1] = 1;
	blockIndexes[2] = 2;
	blockIndexes[3] = 3;

	SetupShape(&Block, shapeSize, lineSize, blockIndexes, blockIndexesSize);
}
