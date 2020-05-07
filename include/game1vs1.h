#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {

    sf::Texture atMoveBlackImg, atMoveWhiteImg, proposeDrawImg, proposeDrawNowImg;
    sf::Texture acceptDrawImg, resignImg, resignNowImg, buttonsMenuImg;
    sf::Sprite atMoveBlackSprite, atMoveWhiteSprite, proposeDrawSprite, proposeDrawNowSprite;
    sf::Sprite acceptDrawSprite, resignSprite, resignNowSprite, buttonsMenuSprite;
    sf::Clock clock;

    float minutesWhite;
    float minutesBlack;

    float addWhite;
    float addBlack;

    float secondsLeftWhite;
    float secondsLeftBlack;

    float ant;

    PieceColour atMove;

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