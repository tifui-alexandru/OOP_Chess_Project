#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {

    sf::Texture atMoveBlackImg, atMoveWhiteImg, proposeDrawImg, acceptDrawImg, resignImg;
    sf::Sprite atMoveBlackSprite, atMoveWhiteSprite, proposeDrawSprite, acceptDrawSprite, resignSprite;
    sf::Clock clock;

    float minutesWhite;
    float minutesBlack;

    float addWhite;
    float addBlack;

    float secondsLeftWhite;
    float secondsLeftBlack;

    float ant;

    int atMove;
    int antMove;

    sf::Text textWhite;
    sf::Text textBlack;

    sf::Font font;

public:
    Game1vs1();
    void play();
    void showEnd(int);
    void printTime();
};

#endif // !GAME1VS1_H