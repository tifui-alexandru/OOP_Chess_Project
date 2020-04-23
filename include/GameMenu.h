#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

class menuMode
{
public:
    bool terminate;

    Texture tusu1, tusu2, tusu3, tusu4, tusu5;
    Sprite susu1, susu2, susu3, susu4, susu5;

    Vector2u size;

public:

    menuMode();

    ~menuMode();

    void menuRun();
};

