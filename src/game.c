#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
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
    int cellsFilled, i, j;
    int size = sizeof(World.Cells) / sizeof(World.Cells[0]);

    for (i = 0; i < size; i = i + World.LineSize)
    {
        cellsFilled = 0;
        for (j = 0; j < World.LineSize; j++)
        {
            if (World.Cells[i + j] != -1)
            {
                cellsFilled++;
            }
        }

        if (cellsFilled == World.LineSize)
        {
            /* Overwrite lines */
            for (j = i + World.LineSize - 1; j >= World.LineSize; j--)
            {
                World.Cells[j] = World.Cells[j - World.LineSize];
            }
            /* Write empty line to beginning */
            for (j = 0; j < World.LineSize; j++)
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
    DrawEmptyBoard(&World);
    DrawShape(&game->CurrentShape);
    DrawWorld();
    move(0,0);
}

void MoveLeft(struct Game *game)
{
    if (!game->Collision.Left)
    {
        game->CurrentShape.X--;
    }
}

void MoveRight(struct Game *game)
{
    if (!game->Collision.Right)
    {
        game->CurrentShape.X++;
    }
}

void MoveDown(struct Game *game, int *timeout)
{
    if (!game->Collision.Bottom)
    {
        game->CurrentShape.Y++;
    }
    else
    {
        AddToWorld(&game->CurrentShape);
        RemoveFullLines(game);
        SetNewBlock(game);
    }

    *timeout = 1000;
}

void Rotate(struct Game *game, int *clipping)
{
    RotateShape(&game->CurrentShape, 1);
    *clipping = CheckClipping(&game->CurrentShape);
    if (*clipping)
    {
        RotateShape(&game->CurrentShape, 3);
        *clipping = CheckClipping(&game->CurrentShape);
    }
}

void Drop(struct Game *game, int *timeout)
{
    while (!game->Collision.Bottom)
    {
        game->CurrentShape.Y++;
        CheckCollision(&game->CurrentShape, &game->Collision);
    }

    AddToWorld(&game->CurrentShape);
    RemoveFullLines(game);
    SetNewBlock(game);

    *timeout = 1000;
}

void Loop(struct Game *game)
{
    int c;
    struct timeval startTime;
    struct timeval endTime;
    int totalTime;
    int clipping = 0;
    int timeout = 1000;
    timeout(timeout);

    while (1)
    {
        clipping = CheckClipping(&game->CurrentShape);
        if (clipping) return;
        gettimeofday(&startTime, NULL);
        Render(game);
        CheckCollision(&game->CurrentShape, &game->Collision);
        refresh();
        c = getch();
        gettimeofday(&endTime, NULL);
        totalTime = ((endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec) / 1000;
        switch (c)
        {
        case 'q':
            return;
        case ' ':
            Drop(game, &timeout);
            break;
        case KEY_UP:
            Rotate(game, &clipping);
            break;
        case KEY_DOWN:
            MoveDown(game, &timeout);
            break;
        case KEY_LEFT:
            MoveLeft(game);
            break;
        case KEY_RIGHT:
            MoveRight(game);
            break;
        case -1:
            MoveDown(game, &timeout);
            break;
        }
        if (c != -1)
        {
            timeout = timeout - totalTime;
            if (timeout < 1)
            {
                timeout = 1000;
            }
        }
        timeout(timeout);
    }
}