#ifndef GAME1VS1_H
#define GAME1VS1_H
#include "gameFront.h"

class Game1vs1 : virtual public GameFront {

    const ButtonBox <size_t> resignButton = {526, 400, 526 + 126, 400 + 66};
    const ButtonBox <size_t> drawButton = {526, 310, 526 + 126, 310 + 66};
    const ButtonBox <size_t> acceptResign = {526, 400, 526 + 126 / 2, 400 + 66};
    const ButtonBox <size_t> declineResign = {526 + 126 / 2 + 1, 400, 526 + 166, 400 + 66};
    const ButtonBox <size_t> acceptDraw = {526, 310, 526 + 126 / 2, 310 + 66};
    const ButtonBox <size_t> declineDraw = {526 + 126 / 2 + 1, 310, 526 + 166, 310 + 66};

    sf::Texture atMoveBlackImg, atMoveWhiteImg, proposeDrawImg, proposeDrawNowImg;
    sf::Texture acceptDrawImg, resignImg, resignNowImg, buttonsMenuImg, promoteMenuImg;
    sf::Texture YesNoButtonImg, YesButtonImg, NoButtonImg, EndedImg, acceptDrawNowImg;
    sf::Texture drawProposedImg;


    sf::Sprite atMoveBlackSprite, atMoveWhiteSprite, proposeDrawSprite, proposeDrawNowSprite;
    sf::Sprite acceptDrawSprite, resignSprite, resignNowSprite, buttonsMenuSprite, promoteMenuSprite;
    sf::Sprite YesNoButtonSprite, YesButtonSprite, NoButtonSprite, EndedSprite, acceptDrawNowSprite;
    sf::Sprite drawProposedSprite;

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
    void printTime();

public:
    Game1vs1();
    void play();
};

#endif // !GAME1VS1_H