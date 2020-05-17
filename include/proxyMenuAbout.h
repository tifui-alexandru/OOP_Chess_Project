#ifndef CHESS_PROXYMENUABOUT_H
#define CHESS_PROXYMENUABOUT_H
#include <SFML/Graphics.hpp>

class RealImage
{
    sf::Texture Telem1, Telem2;
    sf::Sprite Selem1, Selem2;
public:
    RealImage(sf::String usu1, sf::String usu2, int x, int y);

    ~RealImage(){}

    sf::Sprite drawOn();

    sf::Sprite drawOff();
};

class ImageX
{
    RealImage *real_thing;
public:
    ImageX(sf::String usu1, sf::String usu2, int x, int y);

    ~ImageX();

    sf::Sprite drawOn();

    sf::Sprite drawOff();
};
#endif //CHESS_PROXYMENUABOUT_H
