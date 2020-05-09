#include <SFML/Graphics.hpp>

using namespace sf;

#include "../include/MainMenu.h"

menuGame::menuGame()
{
    terminate = false;

    menuModeGo = false;

    menuAboutGo = false;

    tusu1.loadFromFile("../images/menu_img.jpg");
    susu1.setTexture(tusu1);

    tusu2.loadFromFile("../images/play1.png");
    susu2.setTexture(tusu2);

    tusu3.loadFromFile("../images/play2.png");
    susu3.setTexture(tusu3);

    tusu4.loadFromFile("../images/about1.png");
    susu4.setTexture(tusu4);

    tusu5.loadFromFile("../images/about2.png");
    susu5.setTexture(tusu5);

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

        susu2.setPosition(207.5, 120);

        susu3.setPosition(207.5, 120);

        susu4.setPosition(250, 400);

        susu5.setPosition(250, 400);

        window.clear();
        //refresh

        window.draw(susu1);
        //window.draw(text);

        //change the play button
        if(pos.x >= 207.5 && pos.x<= 207.5 + 265 && pos.y >= 120 && pos.y <= 120 + 121)
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
        if(pos.x >= 250 && pos.x<= 250 + 180 && pos.y >= 400 && pos.y <= 400 + 83)
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

        window.display();

    }
}
