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
void AddToWorld(struct Shape *shape, int offsetX, int offsetY);
struct Collision CheckCollision(struct Shape *shape, int x, int y);
int CheckClipping(struct Shape *shape, int x, int y);

#endif