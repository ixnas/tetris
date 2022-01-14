#ifndef DRAW_H
#define DRAW_H
#include "shape.h"
#include "world.h"

void DrawEmptyBoard(struct World* world);
void DrawWorld(struct World* world);
void DrawShape(struct Shape* shape);
void DrawScore(int* score);
void DrawGameOver();

#endif