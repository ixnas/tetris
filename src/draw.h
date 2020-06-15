#ifndef DRAW_H
#define DRAW_H
#include "shape.h"

void DrawChar(char x, char y, char c);
void DrawEmpty(char x, char y);
void DrawBlock(char x, char y);
void DrawEmptyBoard();
void DrawShape(struct Shape *shape, char offsetX, char offsetY);

#endif