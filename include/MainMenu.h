#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "utils.h"

class menuGame
{
public:
    sf::Sound* map1;
    sf::Sound* map2;

    bool terminate;

    bool menuModeGo;

    bool menuAboutGo;

    float* volumeP;

    sf::Texture tusu1, tusu2, tusu3, tusu4, tusu5, volumeOnImg, volumeOffImg, volumeBarImg;
    sf::Texture songPatternImg;

    sf::Sprite susu1, susu2, susu3, susu4, susu5, volumeOnSprite, volumeOffSprite, volumeBarSprite;
    sf::Sprite songPatternSprite;

    sf::Vector2u size;

public:
    bool volumeWorking;

    menuGame(sf::Sound&, sf::Sound&, bool, float&);

    ~menuGame();

    void menuRun();
};