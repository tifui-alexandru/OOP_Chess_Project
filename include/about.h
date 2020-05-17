#include <SFML/Graphics.hpp>

#include "proxyMenuAbout.h"
#include "utils.h"

class menuAbout
{
public:
    bool terminate;

    bool menuGameGo;

    sf::Texture tusu1, tusu2, tusu3, tusu4, tusu5;
    sf::Sprite susu1, susu2, susu3, susu4, susu5;

    sf::Vector2u size;

public:

    menuAbout();

    void menuRun();
};