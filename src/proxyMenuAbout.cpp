#include "../include/proxyMenuAbout.h"

RealImage::RealImage(sf::String usu1, sf::String usu2, int x, int y)
{
    Telem1.loadFromFile(usu1);
    Telem2.loadFromFile(usu2);
    Selem1.setTexture(Telem1);
    Selem2.setTexture(Telem2);
    Selem1.setPosition(x, y);
    Selem2.setPosition(x, y);
}

sf::Sprite RealImage::drawOn()
{
    return Selem1;
}
sf::Sprite RealImage::drawOff()
{
    return Selem2;
}



ImageX::ImageX(sf::String usu1, sf::String usu2, int x, int y)
{
    real_thing = new RealImage(usu1, usu2, x, y);
}

ImageX::~ImageX()
{
    delete real_thing;
}

sf::Sprite ImageX::drawOn()
{
    return real_thing->drawOn();
}

sf::Sprite ImageX::drawOff()
{
    return real_thing->drawOff();
}