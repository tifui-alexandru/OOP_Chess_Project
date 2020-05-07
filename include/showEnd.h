#ifndef CHESS_SHOWEND_H
#define CHESS_SHOWEND_H

#include "../include/gameFront.h"
using namespace sf;

class showEnd
{
public:
    Texture endT;
    Sprite endS;

    Vector2u size;

public:
    showEnd(int);
    //showEnd(GameStatus);

    ~showEnd();

    void showRun();
};

#endif //CHESS_SHOWEND_H
