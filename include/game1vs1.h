#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {

    sf::Texture atMoveBlackImg, atMoveWhiteImg, proposeDrawImg, proposeDrawNowImg;
    sf::Texture acceptDrawImg, resignImg, resignNowImg, buttonsMenuImg, promoteMenuImg;
    sf::Texture YesNoButtonImg, YesButtonImg, NoButtonImg;


    sf::Sprite atMoveBlackSprite, atMoveWhiteSprite, proposeDrawSprite, proposeDrawNowSprite;
    sf::Sprite acceptDrawSprite, resignSprite, resignNowSprite, buttonsMenuSprite, promoteMenuSprite;
    sf::Sprite YesNoButtonSprite, YesButtonSprite, NoButtonSprite;

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

    EventType checkMenuClick(const int& x, const int& y);

public:
    Game1vs1();
    void play();
    void printTime();
};

#endif // !GAME1VS1_H