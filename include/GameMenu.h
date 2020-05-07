#include <SFML/Graphics.hpp>
using namespace sf;

class menuMode
{
public:
    bool terminate;

    bool Game1v1Go;

    bool Game1vPcGo;

    bool menuGameGo;

    Texture tusu1, tusu2, tusu3, tusu4, tusu5, tusu6, tusu7;
    Sprite susu1, susu2, susu3, susu4, susu5, susu6, susu7;

    Vector2u size;

public:

    menuMode();

    ~menuMode();

    void menuRun();
};

