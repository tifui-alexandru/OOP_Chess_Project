#ifndef CHESS_PROMOTE_H
#define CHESS_PROMOTE_H

#include <SFML/Graphics.hpp>
#include "pieces.h"

class Promote
{
    sf::Texture promoteT;
    sf::Sprite promoteS;

    sf::Vector2u size;

    PieceType chosenType;

    void promoteRun();
public:

    Promote();

    PieceType getPiece();
};

#endif //CHESS_PROMOTE_H
