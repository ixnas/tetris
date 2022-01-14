#ifndef SHAPE_H
#define SHAPE_H
#include "array_tools.h"
#include <stdbool.h>

struct Shape
{
	int Blocks[4];
	int ShapeSize;
	int LineSize;
	int X;
	int Y;
	int ColorPair;
};

void SetupShape(struct Shape* shape, int shapeSize, int lineSize, int* blockIndexes, int blockIndexesSize,
                int colorPair);
void RotateShape(struct Shape* shape, int turns);

#endif