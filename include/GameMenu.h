#include <SFML/Graphics.hpp>
#include "utils.h"

class menuMode
{
public:
    bool terminate;

    bool Game1v1Go;

    bool Game1vPcGo;

    bool menuGameGo;

    sf::Texture tusu1, tusu2, tusu3, tusu4, tusu5, tusu6, tusu7;
    sf::Sprite susu1, susu2, susu3, susu4, susu5, susu6, susu7;

    sf::Vector2u size;

public:

    menuMode();

    ~menuMode();

    void menuRun();
};

