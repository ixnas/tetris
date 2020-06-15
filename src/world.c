#include "world.h"
#include <ncurses.h> // remove this shit

struct World World;

void SetupWorld()
{
    int size = sizeof(World.Cells)/sizeof(World.Cells[0]);

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

struct Collision CheckCollision(struct Shape *shape, int x, int y)
{
    int shapeSize = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int worldSize = sizeof(World.Cells) / sizeof(World.Cells[0]);
    int worldLines = worldSize / World.LineSize;
    int coordinate, blockBelow, blockLeft, blockRight;

    struct Collision collision;
    collision.bottom = collision.left = collision.right = 0;

    for (int i = 0; i < shapeSize; i++)
    {
        coordinate = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, x, y);
        blockLeft = coordinate - 1;
        blockRight = coordinate + 1;
        blockBelow = coordinate + World.LineSize;

        if (coordinate >= worldSize - World.LineSize)
        {
            collision.bottom = 1;
        }

        if (coordinate % World.LineSize == 0)
        {
            collision.left = 1;
        }

        if (coordinate % World.LineSize == World.LineSize - 1)
        {
            collision.right = 1;
        }

        for (int j = 0; j < worldSize; j++)
        {
            if (World.Cells[j] == -1)
            {
                continue;
            }
            if (World.Cells[j] == blockLeft)
            {
                collision.left = 1;
            }
            if (World.Cells[j] == blockRight)
            {
                collision.right = 1;
            }
            if (World.Cells[j] == blockBelow)
            {
                collision.bottom = 1;
            }
        }
    }

    move(26, 0);
    printw("L: %d  R: %d  D: %d", collision.left, collision.right, collision.bottom);
    return collision;
}