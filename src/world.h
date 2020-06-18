#ifndef WORLD_H
#define WORLD_H
#include "shape.h"

struct World 
{
    int Cells[200];
    int LineSize;
};

struct Collision
{
    int Left, Right, Bottom;
};

void SetupWorld(struct World *world);
void AddToWorld(struct World *world, struct Shape *shape);
void CheckCollision(struct World *world, struct Shape *shape, struct Collision *collision);
int CheckClipping(struct World *world, struct Shape *shape);

#endif