#include "../include/startGame.h"
#include "SFML/Audio.hpp"
#include "../include/gameMode.h"

startGame * startGame::instance_ = nullptr;

startGame::startGame() = default;

startGame *startGame::GetInstance() {
    if (instance_ == nullptr)
        instance_ = new startGame();

    return instance_;
}


void startGame::runStart()
{

    menuMode t2;
    menuAbout t4;

    sf::SoundBuffer map1Buff;
    sf::SoundBuffer map2Buff;

    sf::Sound map1Sound;
    sf::Sound map2Sound;

    if (!map1Buff.loadFromFile("../sounds/map1.wav")) throw Exception("Sound file must be in .wav format");
    if (!map2Buff.loadFromFile("../sounds/map2.wav")) throw Exception("Sound file must be in .wav format");

    map1Sound.setBuffer(map1Buff);
    map2Sound.setBuffer(map2Buff);

    map1Sound.setLoop(true);
    map2Sound.setLoop(true);

    map1Sound.play();

    bool volumeWorking = true;

    float volumePower = 100.0;

    menuGame t1(map1Sound, map2Sound, volumeWorking, volumePower);

    bool menuModeGo = false;
    bool menuGameGo = true;
    bool menuAboutGo = false;
    bool Game1v1Go = false;
    bool Game1vPcGo = false;

    std::unique_ptr<GameMode> newGame = std::make_unique<GameMode>();

    do{
        if(menuGameGo == true)
        {
            t1.menuRun();
            menuGameGo = false;

            if(t1.menuModeGo == true)
            {
                t1.menuModeGo = false;
                menuModeGo = true;
            }

            if(t1.menuAboutGo == true)
            {
                t1.menuAboutGo = false;
                menuAboutGo = true;
            }
        }

        if(menuModeGo == true)
        {
            t2.menuRun();
            menuModeGo = false;

            if(t2.Game1v1Go == true)
            {
                t2.Game1v1Go = false;
                Game1v1Go = true;
            }

            if(t2.Game1vPcGo == true)
            {
                t2.Game1vPcGo = false;
                Game1vPcGo = true;
            }

            if(t2.menuGameGo == true)
            {
                t2.menuGameGo = false;
                menuGameGo = true;
            }
        }

        if(Game1v1Go == true)
        {
            map1Sound.pause();
            map2Sound.play();

            newGame->setStrategy(GameMode::_1VS1);
            newGame->play();
            map2Sound.stop();
            map1Sound.play();

            Game1v1Go = false;
            menuModeGo = true;
        }

        if(Game1vPcGo == true)
        {
            map1Sound.pause();
            map2Sound.play();

            newGame->setStrategy(GameMode::_1VSPC);
            newGame->play();
            map2Sound.stop();
            map1Sound.play();

            Game1vPcGo = false;
            menuModeGo = true;
        }

        if(menuAboutGo == true)
        {
            t4.menuRun();
            menuAboutGo = false;

            if(t4.menuGameGo == true)
            {
                t4.menuGameGo = false;
                menuGameGo = true;
            }
        }


     }while(menuModeGo == true || menuGameGo == true || menuAboutGo == true || Game1v1Go == true);

}