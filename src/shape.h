#ifndef SHAPE_H
#define SHAPE_H
#include <stdbool.h>
#include "arrcopy.h"

struct Shape
{
    int Blocks[4];
    int ShapeSize;
    int LineSize;
};

void CopyShape(struct Shape *old, struct Shape *new);
void SetupShape(struct Shape *shape, int shapeSize, int lineSize, int *blockIndexes, int blockIndexesSize);
int GetRotatedBlockPosition(int block, struct Shape *shape);
void RotateShape(struct Shape *shape);
void PrintShapeArray(struct Shape *shape);

#endif