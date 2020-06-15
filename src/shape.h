#ifndef SHAPE_H
#define SHAPE_H
#include <stdbool.h>
#include "arrcopy.h"

struct Shape
{
    bool Blocks[16];
    char ShapeSize;
    char LineSize;
};

void CopyShape(struct Shape *old, struct Shape *new);
void SetupShape(struct Shape *shape, char shapeSize, char lineSize, char *blockIndexes, char blockIndexesSize);
char GetRotatedBlockPosition(char block, struct Shape *shape);
void RotateShape(struct Shape *shape);
void PrintShapeArray(struct Shape *shape);

#endif