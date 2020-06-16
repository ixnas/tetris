#ifndef DRAW_H
#define DRAW_H
#include "shape.h"

void DrawChar(int x, int y, char c);
void DrawEmpty(int x, int y);
void DrawBlock(int x, int y);
void DrawEmptyBoard();
void DrawWorld();
void DrawShape(struct Shape *shape);

#endif