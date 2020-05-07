#ifndef CHESS_SHOWEND_H
#define CHESS_SHOWEND_H
#include <SFML/Graphics.hpp>

class showEnd
{
public:
    sf::Texture endT;
    sf::Sprite endS;

    sf::Vector2u size;

public:
    showEnd(int);
    //showEnd(GameStatus);

    ~showEnd();

    void showRun();
};

#endif //CHESS_SHOWEND_H
