#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class menuGame
{
public:
    Sound* map1;
    Sound* map2;

    bool terminate;

    bool menuModeGo;

    bool menuAboutGo;

    float* volumeP;

    Texture tusu1, tusu2, tusu3, tusu4, tusu5, volumeOnImg, volumeOffImg, volumeBarImg;
    Texture songPatternImg;

    Sprite susu1, susu2, susu3, susu4, susu5, volumeOnSprite, volumeOffSprite, volumeBarSprite;
    Sprite songPatternSprite;

    Vector2u size;

public:
    bool volumeWorking;

    menuGame(Sound&, Sound&, bool, float&);

    ~menuGame();

    void menuRun();
};