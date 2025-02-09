#ifndef GAME1VSPC_H
#define GAME1VSPC_H
#include "gameFront.h"

class Game1vsPC : virtual public GameFront {
private:
    PieceColour humanPlayer;

    const ButtonBox <size_t> endButton = {526, 350, 526 + 126, 350 + 92};
    const ButtonBox <size_t> acceptEndButton = {526, 350, 526 + 126 / 2, 350 + 92};
    const ButtonBox <size_t> declineEndButton = {526, 350, 526 + 126 / 2 + 1, 350 + 92};
    const ButtonBox <size_t> hintButton = {526, 250, 526 + 126, 250 + 66};

    sf::Texture buttonsMenuImg, promoteMenuImg, endGameButtonImg, endGameButtonNowImg;
    sf::Texture getHintButtonImg, getHintButtonNowImg, EndedImg;
    sf::Texture NoEndedImg, YesEndedImg, EndedMenuImg;

    sf::Sprite buttonsMenuSprite, promoteMenuSprite, endGameButtonSprite, endGameButtonNowSprite;
    sf::Sprite getHintButtonSprite, getHintButtonNowSprite, EndedSprite;
    sf::Sprite NoEndedSprite, YesEndedSprite, EndedMenuSprite;
    sf::Clock clock;
    sf::Text text;
    sf::Font font;

    EventType checkMenuClick(const int& x, const int& y);
    void printTime();
public:
    Game1vsPC(const PieceColour &humanCol = WHITE);
    void play();
};

#endif // !GAME1VSPC_H