#include "shape_types.h"

void SetupShapeBlock(struct Shape *shape)
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 4;
	lineSize = 2;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 0;
	blockIndexes[1] = 1;
	blockIndexes[2] = 2;
	blockIndexes[3] = 3;

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 2);
}

void SetupShapeL1(struct Shape *shape)
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

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 3);
}

void SetupShapeL2(struct Shape *shape)
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

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 4);
}

void SetupShapeLine(struct Shape *shape)
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

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 5);
}

void SetupShapeS1(struct Shape *shape)
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

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 6);
}

void SetupShapeS2(struct Shape *shape)
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 3;
	blockIndexes[1] = 4;
	blockIndexes[2] = 7;
	blockIndexes[3] = 8;

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 7);
}

void SetupShapeT(struct Shape *shape)
{
	int shapeSize, lineSize, blockIndexesSize;

	shapeSize = 9;
	lineSize = 3;
	blockIndexesSize = 4;

	int blockIndexes[blockIndexesSize];

	blockIndexes[0] = 1;
	blockIndexes[1] = 3;
	blockIndexes[2] = 4;
	blockIndexes[3] = 5;

	SetupShape(shape, shapeSize, lineSize, blockIndexes, blockIndexesSize, 8);
}