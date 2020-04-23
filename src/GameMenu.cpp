#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "include/GameMenu.h"

menuMode::menuMode()
{
    terminate = false;

    tusu1.loadFromFile("images/menu_modes.jpg");
    susu1.setTexture(tusu1);

    tusu2.loadFromFile("images/game1v1.png");
    susu2.setTexture(tusu2);

    tusu3.loadFromFile("images/fight.png");
    susu3.setTexture(tusu3);

    tusu4.loadFromFile("images/gamecomp.png");
    susu4.setTexture(tusu4);

    tusu5.loadFromFile("images/fight.png");
    susu5.setTexture(tusu5);

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

        susu2.setPosition(227.5 - 50, 120);

        susu3.setPosition(227.5 - 50, 120);

        susu4.setPosition(227.5 + 50, 400);

        susu5.setPosition(227.5 + 50, 400);

        window.clear();
        //refresh

        window.draw(susu1);

        //change the play button
        if(pos.x >= 227.5 - 50 && pos.x <= 227.5 + 265 - 50 && pos.y >= 120 && pos.y <= 120 + 121)
            window.draw(susu3);

        else
            window.draw(susu2);

        //change the about button
        if(pos.x >= 227.5 + 50 && pos.x<= 227.5 + 265 + 50 && pos.y >= 400 && pos.y <= 400 + 121)
            window.draw(susu5);

        else
            window.draw(susu4);

        window.display();

    }
}
