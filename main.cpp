#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#include "SFML/Audio.hpp"
using namespace sf;

//#include "include/startGame.h"

int main()
{
    //startGame t;

    //t.runStart();

    sf::SoundBuffer map1Buff;
    sf::Sound map1Sound;

    if(!map1Buff.loadFromFile("sounds/map1.wav"));

    map1Sound.setBuffer(map1Buff);


    map1Sound.play();
    return 0;
}
