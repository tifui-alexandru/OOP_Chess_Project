#include <SFML/Graphics.hpp>
using namespace sf;

#include "../include/GameMenu.h"

menuMode::menuMode()
{
    terminate = false;

    Game1v1Go = false;

    Game1vPcGo = false;

    menuGameGo = false;

    if (!tusu1.loadFromFile("../images/menu_modes.jpg")) throw std::runtime_error("Failed to load image");
    susu1.setTexture(tusu1);

    if (!tusu2.loadFromFile("../images/game1v1.png")) throw std::runtime_error("Failed to load image");
    susu2.setTexture(tusu2);

    if (!tusu3.loadFromFile("../images/fight.png")) throw std::runtime_error("Failed to load image");
    susu3.setTexture(tusu3);

    if (!tusu4.loadFromFile("../images/gamecomp.png")) throw std::runtime_error("Failed to load image");
    susu4.setTexture(tusu4);

    if (!tusu5.loadFromFile("../images/fight.png")) throw std::runtime_error("Failed to load image");
    susu5.setTexture(tusu5);

    if (!tusu6.loadFromFile("../images/back1.png")) throw std::runtime_error("Failed to load image");
    susu6.setTexture(tusu6);

    if (!tusu7.loadFromFile("../images/back2.png")) throw std::runtime_error("Failed to load image");
    susu7.setTexture(tusu7);

    size = tusu1.getSize();
}

menuMode::~menuMode(){}

void menuMode::menuRun()
{
    RenderWindow window(sf::VideoMode(720, 640), "MENU", sf::Style::Titlebar | sf::Style::Close);
    // VideoMode - > window size
    // "MENU" -> window title
    // style -> can not be resizable
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

        Vector2i pos = Mouse::getPosition(window);

        //get the position every time to know where the mouse is

        susu2.setPosition(227.5 - 90, 120);

        susu3.setPosition(227.5 - 90, 120);

        susu4.setPosition(227.5 + 90, 400);

        susu5.setPosition(227.5 + 90, 400);

        susu6.setPosition(50, 535);

        susu7.setPosition(50, 535);

        window.clear();
        //refresh

        window.draw(susu1);

        //change the play button
        if(pos.x >= 227.5 - 90 && pos.x <= 227.5 + 265 - 90 && pos.y >= 120 && pos.y <= 120 + 121)
        {
            window.draw(susu3);

            if(event.type == Event::MouseButtonPressed)
            {
                if(event.key.code == (int)Mouse::Left)
                {
                    Game1v1Go = true;
                    window.close();
                }
            }
        }
        else
            window.draw(susu2);

        //change the about button
        if(pos.x >= 227.5 + 90 && pos.x<= 227.5 + 265 + 90 && pos.y >= 400 && pos.y <= 400 + 121)
        {
            window.draw(susu5);

            if(event.type == Event::MouseButtonPressed)
            {
                if(event.key.code == (int)Mouse::Left)
                {
                    Game1vPcGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(susu4);

        if(pos.x >= 50 && pos.x<= 50 + 127 && pos.y >= 535 && pos.y <= 535 + 58)
        {
            window.draw(susu7);

            if(event.type == Event::MouseButtonPressed)
            {
                if(event.key.code == (int)Mouse::Left)
                {
                    menuGameGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(susu6);

        window.display();

    }
}
