#ifndef CHESS_PROMOTE_H
#define CHESS_PROMOTE_H

#include "gameFront.h"
using namespace sf;

class Promote
{
    Texture promoteT;
    Sprite promoteS;

    Vector2u size;

    PieceType chosenType;

    void promoteRun();
public:

    Promote();

    ~Promote();

    PieceType getPiece();
};

#endif //CHESS_PROMOTE_H
