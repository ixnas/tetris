#include "world.h"
#include <ncurses.h> // remove this shit

struct World World;

void SetupWorld()
{
    int size = sizeof(World.Cells) / sizeof(World.Cells[0]);

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

void AddToWorld(struct Shape *shape)
{
    int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int coordinates[size];

    for (int i = 0; i < size; i++)
    {
        coordinates[i] = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, shape->X, shape->Y);
    }

    for (int j = 0; j < size; j++)
    {
        if (World.Cells[coordinates[j]] == -1)
        {
            World.Cells[coordinates[j]] = shape->ColorPair;
        }
    }
}

void CheckCollision(struct Shape *shape, struct Collision *collision)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int worldLines = worldSize / World.LineSize;
    int coordinate, blockBelow, blockLeft, blockRight;

    collision->Bottom = collision->Left = collision->Right = 0;

    for (int i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, shape->X, shape->Y);
        blockLeft = coordinate - 1;
        blockRight = coordinate + 1;
        blockBelow = coordinate + World.LineSize;

        if (coordinate >= worldSize - World.LineSize)
        {
            collision->Bottom = 1;
        }

        if (coordinate % World.LineSize == 0)
        {
            collision->Left = 1;
        }

        if (coordinate % World.LineSize == World.LineSize - 1)
        {
            collision->Right = 1;
        }

        if (World.Cells[blockLeft] != -1)
        {
            collision->Left = 1;
        }
        if (World.Cells[blockRight] != -1)
        {
            collision->Right = 1;
        }
        if (World.Cells[blockBelow] != -1)
        {
            collision->Bottom = 1;
        }
    }

    move(26, 0);
    printw("L: %d  R: %d  D: %d", collision->Left, collision->Right, collision->Bottom);
}

int CheckClipping(struct Shape *shape)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int coordinate, currentLine, currentX;

    for (int i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, shape->X, shape->Y);

        currentLine = shape->Blocks[i] / shape->LineSize;
        currentX = shape->Blocks[i] - currentLine * shape->LineSize + shape->X;

        // Clipping through the sides of the world
        if (currentX < 0 || currentX >= World.LineSize)
        {
            move(27, 0);
            printw("Clipping: %d", 1);
            return 1;
        }

        // Clipping through top and bottom of the world
        if (coordinate < 0 || coordinate >= worldSize)
        {
            move(27, 0);
            printw("Clipping: %d", 1);
            return 1;
        }

        // Clipping into other blocks inside the world
        if (World.Cells[coordinate] != -1)
        {
            move(27, 0);
            printw("Clipping: %d", 1);
            return 1;
        }
    }

    move(27, 0);
    printw("Clipping: %d", 0);
    return 0;
}