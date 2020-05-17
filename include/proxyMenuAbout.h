#ifndef CHESS_PROXYMENUABOUT_H
#define CHESS_PROXYMENUABOUT_H
//#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class RealImage
{
    Texture Telem1, Telem2;
    Sprite Selem1, Selem2;
public:
    RealImage(String usu1, String usu2, int x, int y);

    ~RealImage(){}

    Sprite drawOn();

    Sprite drawOff();
};

class ImageX
{
    RealImage *real_thing;
public:
    ImageX(String usu1, String usu2, int x, int y);

    ~ImageX();

    Sprite drawOn();

    Sprite drawOff();
};
#endif //CHESS_PROXYMENUABOUT_H
