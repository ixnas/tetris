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
    int left, right, bottom;
};

void SetupWorld();
int ConvertToWorldCoordinate(int block, int lineSize, int offsetX, int offsetY);
void AddToWorld(struct Shape *shape, int offsetX, int offsetY);
struct Collision CheckCollision(struct Shape *shape, int moveX, int moveY);

#endif