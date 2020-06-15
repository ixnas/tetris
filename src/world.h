#ifndef WORLD_H
#define WORLD_H

struct World 
{
    int Cells[200];
    int LineSize;
};

struct World World;

void SetupWorld();
int ConvertToWorldCoordinate(int block, int lineSize, int offsetX, int offsetY);

#endif