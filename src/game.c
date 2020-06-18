#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include "defaults.h"
#include "game.h"
#include "array_tools.h"
#include "draw.h"
#include "shape.h"
#include "shape_types.h"

static void SetNewBlock(struct Game *game)
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
        SetupShapeBlock(&game->CurrentShape);
        break;
    case 1:
        SetupShapeL1(&game->CurrentShape);
        break;
    case 2:
        SetupShapeL2(&game->CurrentShape);
        break;
    case 3:
        SetupShapeLine(&game->CurrentShape);
        break;
    case 4:
        SetupShapeS1(&game->CurrentShape);
        break;
    case 5:
        SetupShapeS2(&game->CurrentShape);
        break;
    case 6:
        SetupShapeT(&game->CurrentShape);
        break;
    }
}

static void RemoveFullLines(struct Game *game)
{
    int cellsFilled, i, j;
    int size = sizeof(game->World.Cells) / sizeof(game->World.Cells[0]);
    int linesCleared = 0;

    for (i = 0; i < size; i = i + game->World.LineSize)
    {
        cellsFilled = 0;
        for (j = 0; j < game->World.LineSize; j++)
        {
            if (game->World.Cells[i + j] != -1)
            {
                cellsFilled++;
            }
        }

        if (cellsFilled == game->World.LineSize)
        {
            /* Overwrite lines */
            for (j = i + game->World.LineSize - 1; j >= game->World.LineSize; j--)
            {
                game->World.Cells[j] = game->World.Cells[j - game->World.LineSize];
            }
            /* Write empty line to beginning */
            for (j = 0; j < game->World.LineSize; j++)
            {
                game->World.Cells[j] = -1;
            }

            linesCleared++;
        }
    }
    switch (linesCleared)
    {
    case 1:
        game->Score += SCORE_SINGLE;
        break;
    case 2:
        game->Score += SCORE_DOUBLE;
        break;
    case 3:
        game->Score += SCORE_TRIPLE;
        break;
    case 4:
        game->Score += SCORE_TETRIS;
        break;
    }
}

static void SetupCurses(struct Game *game)
{
    struct timeval tm;
    noecho();
    gettimeofday(&tm, NULL);
    srand(tm.tv_sec + tm.tv_usec * 1000000ul);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    keypad(stdscr, 1);
}

static void Render(struct Game *game)
{
    DrawEmptyBoard(&game->World);
    DrawShape(&game->CurrentShape);
    DrawWorld(&game->World);
    DrawScore(&game->Score);
    move(0, 0);
}

static void MoveLeft(struct Game *game)
{
    if (!game->Collision.Left)
    {
        game->CurrentShape.X--;
    }
}

static void MoveRight(struct Game *game)
{
    if (!game->Collision.Right)
    {
        game->CurrentShape.X++;
    }
}

static void MoveDown(struct Game *game, int *timeout)
{
    if (!game->Collision.Bottom)
    {
        game->CurrentShape.Y++;
    }
    else
    {
        AddToWorld(&game->World, &game->CurrentShape);
        RemoveFullLines(game);
        SetNewBlock(game);
    }

    *timeout = FALL_SPEED_MS;
}

static void Rotate(struct Game *game, int *clipping)
{
    RotateShape(&game->CurrentShape, 1);
    *clipping = CheckClipping(&game->World, &game->CurrentShape);
    if (*clipping)
    {
        RotateShape(&game->CurrentShape, 3);
        *clipping = CheckClipping(&game->World, &game->CurrentShape);
    }
}

static void Drop(struct Game *game, int *timeout)
{
    int hardDropCount = 1;
    while (!game->Collision.Bottom)
    {
        hardDropCount++;
        game->CurrentShape.Y++;
        CheckCollision(&game->World, &game->CurrentShape, &game->Collision);
    }

    game->Score += hardDropCount;

    AddToWorld(&game->World, &game->CurrentShape);
    RemoveFullLines(game);
    SetNewBlock(game);

    *timeout = FALL_SPEED_MS;
}

void SetupGame(struct Game *game)
{
    game->Score = 0;
    SetupCurses(game);
    SetupWorld(&game->World);
    SetNewBlock(game);
}

void GameOver()
{
    DrawGameOver();
    timeout(-1);
    while (getch() != 'q');
}

void Loop(struct Game *game)
{
    int c;
    struct timeval startTime;
    struct timeval endTime;
    int totalTime;
    int clipping = 0;
    int timeout = FALL_SPEED_MS;

    while (1)
    {
        timeout(timeout);

        clipping = CheckClipping(&game->World, &game->CurrentShape);
        if (clipping)
            return GameOver();
        CheckCollision(&game->World, &game->CurrentShape, &game->Collision);

        gettimeofday(&startTime, NULL);

        Render(game);
        refresh();

        c = getch();

        gettimeofday(&endTime, NULL);
        totalTime = ((endTime.tv_sec - startTime.tv_sec) * 1000000 + endTime.tv_usec - startTime.tv_usec) / 1000;

        switch (c)
        {
        case 'q':
            GameOver();
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
                timeout = FALL_SPEED_MS;
            }
        }
    }
}