#ifndef CHESS_SHOWEND_H
#define CHESS_SHOWEND_H
#include <SFML/Graphics.hpp>

class showEnd
{
    sf::Texture endT;
    sf::Sprite endS;

    sf::Vector2u size;

public:
    showEnd(int status);
    //showEnd(GameStatus);

    void showRun();
};

#endif //CHESS_SHOWEND_H
