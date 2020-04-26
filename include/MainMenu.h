#include <SFML/Graphics.hpp>
using namespace sf;

class menuGame
{
public:
    bool terminate;

    bool menuModeGo;

    bool menuAboutGo;

    Texture tusu1, tusu2, tusu3, tusu4, tusu5;
    Sprite susu1, susu2, susu3, susu4, susu5;

    Vector2u size;

public:

    menuGame();

    ~menuGame();

    void menuRun();
};