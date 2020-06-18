#ifndef GAME_H
#define GAME_H
#include "shape.h"
#include "world.h"

struct Game
{
    struct Shape CurrentShape;
    struct Collision Collision;
    struct World World;
    int Score;
};

void SetupGame(struct Game *game);
void Loop(struct Game *game);

#endif