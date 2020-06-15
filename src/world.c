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
    World.Cells[0] = 45;
}

int ConvertToWorldCoordinate(int block, int lineSize, int offsetX, int offsetY)
{
    int line = block / lineSize;
    int lineSizeDifference = World.LineSize - lineSize;
    return block + line * lineSizeDifference + offsetX + World.LineSize * offsetY;
}

void AddToWorld(struct Shape *shape, int offsetX, int offsetY)
{
    int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int coordinates[size];

    for (int i = 0; i < size; i++)
    {
        coordinates[i] = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, offsetX, offsetY);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < worldSize; j++)
        {
            if (World.Cells[j] == -1)
            {
                World.Cells[j] = coordinates[i];
                break;
            }
        }
    }
}

void CheckCollision(struct Shape *shape, int x, int y, struct Collision *collision)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int worldLines = worldSize / World.LineSize;
    int coordinate, blockBelow, blockLeft, blockRight;

    collision->Bottom = collision->Left = collision->Right = 0;

    for (int i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, x, y);
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

        for (int j = 0; j < worldSize; j++)
        {
            if (World.Cells[j] == -1)
            {
                continue;
            }
            if (World.Cells[j] == blockLeft)
            {
                collision->Left = 1;
            }
            if (World.Cells[j] == blockRight)
            {
                collision->Right = 1;
            }
            if (World.Cells[j] == blockBelow)
            {
                collision->Bottom = 1;
            }
        }
    }

    move(26, 0);
    printw("L: %d  R: %d  D: %d", collision->Left, collision->Right, collision->Bottom);
}

int CheckClipping(struct Shape *shape, int x, int y)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int coordinate;

    move(27, 0);
    for (int i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, x, y);
        if (coordinate < 0 || coordinate >= worldSize)
        {
            printw("Clipping: %d", 1);
            return 1;
        }
        for (int j = 0; j < worldSize; j++)
        {
            if (coordinate == World.Cells[j])
            {
                printw("Clipping: %d", 1);
                return 1;
            }
        }
    }

    printw("Clipping: %d", 0);
    return 0;
}