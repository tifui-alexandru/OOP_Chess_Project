#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "../include/about.h"

menuAbout::menuAbout()
{
    terminate = false;

    menuGameGo = false;

    tusu1.loadFromFile("../images/about.jpg");
    susu1.setTexture(tusu1);

    tusu2.loadFromFile("../images/ab_b1.png");
    susu2.setTexture(tusu2);

    tusu3.loadFromFile("../images/ab_b2.png");
    susu3.setTexture(tusu3);

    tusu4.loadFromFile("../images/ab_f1.png");
    susu4.setTexture(tusu4);

    tusu5.loadFromFile("../images/ab_f2.png");
    susu5.setTexture(tusu5);

    size = tusu1.getSize();
}

menuAbout::~menuAbout(){}

void menuAbout::menuRun()
{
    RenderWindow window(sf::VideoMode(700, 622), "MENU", sf::Style::Titlebar | sf::Style::Close);
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


        window.clear();
        //refresh

        window.draw(susu1);

        //change the play button
        if(pos.x >= 227.5 - 90 && pos.x <= 227.5 + 265 - 90 && pos.y >= 120 && pos.y <= 120 + 121)
        {
            window.draw(susu3);

            if(event.type == Event::MouseButtonPressed)
            {
                if(event.key.code == Mouse::Left)
                {
                    menuGameGo = true;
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
                if(event.key.code == Mouse::Left)
                {
                    menuGameGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(susu4);

        window.display();

    }
}
