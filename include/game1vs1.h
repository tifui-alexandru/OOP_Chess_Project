#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {

    sf::Texture atMoveBlackImg, atMoveWhiteImg, proposeDrawImg, acceptDrawImg, resignImg;
    sf::Sprite atMoveBlackSprite, atMoveWhiteSprite, proposeDrawSprite, acceptDrawSprite, resignSprite;

public:
    Game1vs1();
    void play();
    void showEnd(int);
};

#endif // !GAME1VS1_H