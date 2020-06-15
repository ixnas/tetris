#include "world.h"

struct World World;

void SetupWorld()
{
    int size = sizeof(World.Cells)/sizeof(World.Cells[0]);

    for (int i = 0; i < size; i++)
    {
        World.Cells[i] = -1;
    }

    World.LineSize = 10;
}

int ConvertToWorldCoordinate(int block, int lineSize, int offsetX, int offsetY)
{
    int line = block / lineSize;
    int lineSizeDifference = World.LineSize - lineSize;
    return block + line * lineSizeDifference + offsetX + World.LineSize * offsetY;
}