#include <stdlib.h>
#include <ncurses.h>
#include "game.h"
#include "shape_t.h"
#include "array_tools.h"
#include "draw.h"
#include "shape.h"
#include "shape_block.h"
#include "shape_l1.h"
#include "shape_l2.h"
#include "shape_line.h"
#include "shape_s1.h"
#include "shape_s2.h"
#include "shape_t.h"

void PrintShapeWorldCoordinates(struct Shape *shape)
{
    int size = sizeof(shape->Blocks) / sizeof(shape->Blocks[0]);
    int coordinates[size];

    for (int i = 0; i < size; i++)
    {
        coordinates[i] = ConvertToWorldCoordinate(shape->Blocks[i], shape->LineSize, shape->X, shape->Y);
    }

    move(22, 0);
    printw("World: ");
    for (int i = 0; i < size; i++)
    {
        printw("%d ", coordinates[i]);
    }
}

void SetupShapes()
{
    SetupShapeLine();
    SetupShapeL1();
    SetupShapeL2();
    SetupShapeS1();
    SetupShapeS2();
    SetupShapeT();
    SetupShapeBlock();
}

void SetNewBlock(struct Game *game)
{
    int x;

    // Keep searching for an x in a range divisible by n
    do
    {
        x = rand();
    } while (x >= RAND_MAX - (RAND_MAX % 7));

    x %= 7;

    switch (x)
    {
    case 0:
        CopyShape(&Block, &game->CurrentShape);
        break;
    case 1:
        CopyShape(&L1, &game->CurrentShape);
        break;
    case 2:
        CopyShape(&L2, &game->CurrentShape);
        break;
    case 3:
        CopyShape(&Line, &game->CurrentShape);
        break;
    case 4:
        CopyShape(&S1, &game->CurrentShape);
        break;
    case 5:
        CopyShape(&S2, &game->CurrentShape);
        break;
    case 6:
        CopyShape(&T, &game->CurrentShape);
        break;
    }
}

void RemoveFullLines(struct Game *game)
{
    int cellsFilled;
    int size = sizeof(World.Cells) / sizeof(World.Cells[0]);

    for (int i = 0; i < size; i = i + World.LineSize)
    {
        cellsFilled = 0;
        for (int j = 0; j < World.LineSize; j++)
        {
            if (World.Cells[i + j] != -1)
            {
                cellsFilled++;
            }
        }

        if (cellsFilled == World.LineSize)
        {
            // Overwrite lines
            for (int j = i + World.LineSize - 1; j >= World.LineSize; j--)
            {
                World.Cells[j] = World.Cells[j - World.LineSize];
            }
            // Write empty line to beginning
            for (int j = 0; j < World.LineSize; j++)
            {
                World.Cells[j] = -1;
            }
        }
    }
}

void SetupGame(struct Game *game)
{
    SetupShapes();
    SetupWorld();
    SetNewBlock(game);
}

void Render(struct Game *game)
{
    DrawEmptyBoard();
    DrawShape(&game->CurrentShape);
    DrawWorld();
    PrintShapeArray(&game->CurrentShape);
    PrintShapeWorldCoordinates(&game->CurrentShape);
}

void Loop(struct Game *game)
{
    int c;

    while (1)
    {
        Render(game);
        CheckCollision(&game->CurrentShape, &game->Collision);
        refresh();
        c = getch();
        switch (c)
        {
        case 'q':
            return;
        case ' ':
            RotateShape(&game->CurrentShape, 1);
            if (CheckClipping(&game->CurrentShape))
            {
                RotateShape(&game->CurrentShape, 3);
            }
            break;
        case KEY_DOWN:
            if (!game->Collision.Bottom)
            {
                game->CurrentShape.Y++;
            }
            break;
        case KEY_LEFT:
            if (!game->Collision.Left)
            {
                game->CurrentShape.X--;
            }
            break;
        case KEY_RIGHT:
            if (!game->Collision.Right)
            {
                game->CurrentShape.X++;
            }
            break;
        case 'l':
            AddToWorld(&game->CurrentShape);
            RemoveFullLines(game);
            SetNewBlock(game);
            break;
        }
    }
}