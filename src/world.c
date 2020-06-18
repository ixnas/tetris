#include "world.h"
#include <ncurses.h> /* remove this shit */

static int ConvertToWorldCoordinate(struct World *world, int block, int lineSize, int offsetX, int offsetY)
{
    int line = block / lineSize;
    int lineSizeDifference = world->LineSize - lineSize;
    return block + line * lineSizeDifference + offsetX + world->LineSize * offsetY;
}

void SetupWorld(struct World *world)
{
    int size = sizeof(world->Cells) / sizeof(world->Cells[0]);
    int i;

    for (i = 0; i < size; i++)
    {
        world->Cells[i] = -1;
    }

    world->LineSize = 10;
}

void AddToWorld(struct World *world, struct Shape *shape)
{
    int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int coordinates[size];
    int i;

    for (i = 0; i < size; i++)
    {
        coordinates[i] = ConvertToWorldCoordinate(world, shape->Blocks[i], shape->LineSize, shape->X, shape->Y);
    }

    for (i = 0; i < size; i++)
    {
        if (world->Cells[coordinates[i]] == -1)
        {
            world->Cells[coordinates[i]] = shape->ColorPair;
        }
    }
}

void CheckCollision(struct World *world, struct Shape *shape, struct Collision *collision)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(world->Cells) / sizeof(world->Cells[0]);
    int coordinate, blockBelow, blockLeft, blockRight, i;

    collision->Bottom = collision->Left = collision->Right = 0;

    for (i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(world, shape->Blocks[i], shape->LineSize, shape->X, shape->Y);
        blockLeft = coordinate - 1;
        blockRight = coordinate + 1;
        blockBelow = coordinate + world->LineSize;

        if (coordinate >= worldSize - world->LineSize)
        {
            collision->Bottom = 1;
        }

        if (coordinate % world->LineSize == 0)
        {
            collision->Left = 1;
        }

        if (coordinate % world->LineSize == world->LineSize - 1)
        {
            collision->Right = 1;
        }

        if (world->Cells[blockLeft] != -1)
        {
            collision->Left = 1;
        }
        if (world->Cells[blockRight] != -1)
        {
            collision->Right = 1;
        }
        if (world->Cells[blockBelow] != -1)
        {
            collision->Bottom = 1;
        }
    }
}

int CheckClipping(struct World *world, struct Shape *shape)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(world->Cells) / sizeof(world->Cells[0]);
    int coordinate, currentLine, currentX, i;

    for (i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(world, shape->Blocks[i], shape->LineSize, shape->X, shape->Y);

        currentLine = shape->Blocks[i] / shape->LineSize;
        currentX = shape->Blocks[i] - currentLine * shape->LineSize + shape->X;

        /* Clipping through the sides of the world */
        if (currentX < 0 || currentX >= world->LineSize)
        {
            return 1;
        }

        /* Clipping through top and bottom of the world */
        if (coordinate < 0 || coordinate >= worldSize)
        {
            return 1;
        }

        /* Clipping into other blocks inside the world */
        if (world->Cells[coordinate] != -1)
        {
            return 1;
        }
    }
    return 0;
}