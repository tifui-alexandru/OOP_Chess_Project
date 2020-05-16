#include <SFML/Graphics.hpp>
using namespace sf;
#include <SFML/Audio.hpp>
#include "../include/MainMenu.h"

menuGame::menuGame(Sound& map1Primit, Sound& map2Primit, bool volumPrimit, float& volumePower)
{
    map1 = &map1Primit;
    map2 = &map2Primit;

    volumeP = &volumePower;

    terminate = false;

    menuModeGo = false;

    menuAboutGo = false;

    volumeWorking = volumPrimit;

    if (!tusu1.loadFromFile("../images/menu_img.jpg")) throw std::runtime_error("Failed to load image");
    susu1.setTexture(tusu1);

    if (!tusu2.loadFromFile("../images/play1.png")) throw std::runtime_error("Failed to load image");
    susu2.setTexture(tusu2);
    susu2.setPosition(257.5, 100);

    if (!tusu3.loadFromFile("../images/play2.png")) throw std::runtime_error("Failed to load image");
    susu3.setTexture(tusu3);
    susu3.setPosition(257.5, 100);

    if (!tusu4.loadFromFile("../images/about1.png")) throw std::runtime_error("Failed to load image");
    susu4.setTexture(tusu4);
    susu4.setPosition(180, 380);

    if (!tusu5.loadFromFile("../images/about2.png")) throw std::runtime_error("Failed to load image");
    susu5.setTexture(tusu5);
    susu5.setPosition(180, 380);

    if (!volumeOnImg.loadFromFile("../images/soundOn.png")) throw std::runtime_error("Failed to load image");
    volumeOnSprite.setTexture(volumeOnImg);
    volumeOnSprite.setPosition(500, 470);

    if (!volumeOffImg.loadFromFile("../images/soundOff.png")) throw std::runtime_error("Failed to load image");
    volumeOffSprite.setTexture(volumeOffImg);
    volumeOffSprite.setPosition(500, 470);

    if (!volumeBarImg.loadFromFile("../images/sound.png")) throw std::runtime_error("Failed to load image");
    volumeBarSprite.setTexture(volumeBarImg);

    if(!songPatternImg.loadFromFile("../images/songPattern.jpg")) throw std::runtime_error("Failed to load image");
    songPatternSprite.setTexture(songPatternImg);

    volumeBarSprite.setPosition(500 + 51, 470);

    size = tusu1.getSize();
}

menuGame::~menuGame(){}

void menuGame::menuRun()
{
    RenderWindow window(sf::VideoMode(680, 544), "MENU", sf::Style::Titlebar | sf::Style::Close);
    // VideoMode - > window size
    // "MENU" -> window title
    // style -> can not be resizable
    // sf::Text text;
    // sf::Font font;
    // font.loadFromFile("../images/sans.ttf");
    // text.setFont(font);
    //text.setString("Test");
    //text.setCharacterSize(24);

    sf::RectangleShape rectV{ {103.f, 53.f } };
    //rectV.setFillColor(sf::Color::Red);
    rectV.setPosition({ 551, 470});
    rectV.setTexture(&songPatternImg);
    rectV.setTextureRect(sf::IntRect(0, 0, 103, 53));
    rectV.setSize(sf::Vector2f (*volumeP / 100.0 * 103.0, 53));

    rectV.setTextureRect(sf::IntRect(0, 0, *volumeP / 100.0 * 103.0, 53));
    rectV.setOutlineColor(sf::Color::Black);
    rectV.setOutlineThickness(2.f);

    while(window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {

            //until we close the window

            if(event.type == sf::Event::Closed)
            {
                terminate = true;

                window.close();
            }
        }

        /*if(event.type == Event::MouseButtonPressed) {
            if ((int) event.key.code == (int) Mouse::Left) {
                map1->stop();
            }

        }*/

        Vector2i pos = Mouse::getPosition(window);

        window.clear();
        //refresh

        window.draw(susu1);
        //window.draw(text);

        //change the play button
        if(pos.x >= 257.5 && pos.x<= 257.5 + 265 && pos.y >= 100 && pos.y <= 100 + 121)
        {
            window.draw(susu3);

            if(event.type == Event::MouseButtonPressed)
            {
                if((int)event.key.code ==(int)Mouse::Left)
                {
                    menuModeGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(susu2);

        //change the about button
        if(pos.x >= 180 && pos.x<= 180 + 180 && pos.y >= 380 && pos.y <= 380 + 83)
        {
            window.draw(susu5);

            if(event.type == Event::MouseButtonPressed)
            {
                if((int)event.key.code ==(int)Mouse::Left)
                {
                    menuAboutGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(susu4);

        window.draw(volumeBarSprite);

        /*if(pos.x >= 500 && pos.x<= 500 + 51 && pos.y >= 470 && pos.y <= 470 + 53)
        {
            if(event.type == Event::MouseButtonPressed)
            {
                if((int)event.key.code ==(int)Mouse::Left)
                {
                    if(volumeWorking == true) volumeWorking = false;
                    else volumeWorking = true;
                }
            }
        }*/

        if(pos.x >= 551 && pos.x<= 551 + 103 && pos.y >= 470 && pos.y <= 470 + 53)
        {
            if(event.type == Event::MouseButtonPressed)
            {
                if((int)event.key.code ==(int)Mouse::Left)
                {
                    rectV.setSize(sf::Vector2f (pos.x - 551, 53));
                    map1->setVolume((pos.x-551.0) / 103.0 * 100.0);
                    map2->setVolume((pos.x-551.0) / 103.0 * 100.0);
                    *volumeP = (pos.x-551.0) / 103.0 * 100.0;
                    rectV.setTextureRect(sf::IntRect(0, 0, *volumeP / 100.0 * 103.0, 53));
                }
            }
        }

        if(volumeWorking == true)
            window.draw(volumeOnSprite);
        else
            window.draw(volumeOffSprite);

        window.draw(rectV);

        window.display();

    }
}
