#ifndef SHAPE_H
#define SHAPE_H
#include <stdbool.h>
#include "array_tools.h"

struct Shape
{
    int Blocks[4];
    int ShapeSize;
    int LineSize;
    int X;
    int Y;
    int ColorPair;
};

void CopyShape(struct Shape *old, struct Shape *new);
void SetupShape(struct Shape *shape, int shapeSize, int lineSize, int *blockIndexes, int blockIndexesSize, int colorPair);
int GetRotatedBlockPosition(int block, struct Shape *shape);
void RotateShape(struct Shape *shape, int turns);

#endif