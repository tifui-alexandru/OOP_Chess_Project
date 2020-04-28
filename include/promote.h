#ifndef CHESS_PROMOTE_H
#define CHESS_PROMOTE_H

#include "../include/gameFront.h"
using namespace sf;

class promote
{
public:
    Texture promoteT;
    Sprite promoteS;

    Vector2u size;

    int chosenType;

public:

    promote();

    ~promote();

    void promoteRun();
};

#endif //CHESS_PROMOTE_H
