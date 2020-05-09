#ifndef GAME1VSPC_H
#define GAME1VSPC_H
#include "gameFront.h"

class Game1vsPC : virtual public GameFront {
private:
    PieceColour humanPlayer;

    sf::Texture buttonsMenuImg, promoteMenuImg, endGameButtonImg, endGameButtonNowImg;
    sf::Texture getHintButtonImg, getHintButtonNowImg;

    sf::Sprite buttonsMenuSprite, promoteMenuSprite, endGameButtonSprite, endGameButtonNowSprite;
    sf::Sprite getHintButtonSprite, getHintButtonNowSprite;

    void printTime();
    sf::Clock clock;
    sf::Text text;
    sf::Font font;

    EventType checkMenuClick(const int& x, const int& y);

public:
    Game1vsPC(const PieceColour &humanCol = WHITE);
    void play();
};

#endif // !GAME1VSPC_H