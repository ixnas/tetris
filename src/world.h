#ifndef WORLD_H
#define WORLD_H
#include "shape.h"

struct World 
{
    int Cells[200];
    int LineSize;
};

struct World World;

struct Collision
{
    int Left, Right, Bottom;
};

void SetupWorld();
int ConvertToWorldCoordinate(int block, int lineSize, int offsetX, int offsetY);
void AddToWorld(struct Shape *shape);
void CheckCollision(struct Shape *shape, struct Collision *collision);
int CheckClipping(struct Shape *shape);

#endif