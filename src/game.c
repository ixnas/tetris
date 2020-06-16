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

void SetupGame(struct Game *game)
{
    SetupShapes();
    SetupWorld();
    CopyShape(&T, &game->CurrentShape);
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
            CopyShape(&T, &game->CurrentShape);
            break;
        }
    }
}