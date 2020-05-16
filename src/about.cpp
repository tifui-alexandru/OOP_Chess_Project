#include "../include/about.h"

menuAbout::menuAbout()
{
    terminate = false;

    menuGameGo = false;

    if (!tusu1.loadFromFile("../images/about.jpg")) throw std::runtime_error("Failed to load image");
    susu1.setTexture(tusu1);

    /*if (!tusu2.loadFromFile("../images/ab_b1.png")) throw std::runtime_error("Failed to load image");
    susu2.setTexture(tusu2);

    if (!tusu3.loadFromFile("../images/ab_b2.png")) throw std::runtime_error("Failed to load image");
    susu3.setTexture(tusu3);

    if (!tusu4.loadFromFile("../images/ab_f1.png")) throw std::runtime_error("Failed to load image");
    susu4.setTexture(tusu4);

    if (!tusu5.loadFromFile("../images/ab_f2.png")) throw std::runtime_error("Failed to load image");
    susu5.setTexture(tusu5);*/



    size = tusu1.getSize();
}

void menuAbout::menuRun()
{
    ImageX img1("../images/ab_b1.png", "../images/ab_b2.png", 55, 120);
    ImageX img2("../images/ab_f1.png", "../images/ab_f2.png", 490, 120);

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

        //susu2.setPosition(55, 120);

        //susu3.setPosition(55, 120);

        /*susu4.setPosition(490, 120);

        susu5.setPosition(490, 120);*/


        window.clear();
        //refresh

        window.draw(susu1);

        //change the play button
        if(pos.x >= 55 && pos.x <= 55 + 128 && pos.y >= 120  && pos.y <= 120 + 57)
        {
            window.draw(img1.drawOff());

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
            window.draw(img1.drawOn());

        //change the about button
        if(pos.x >= 490 && pos.x<= 490 + 128 && pos.y >= 120 && pos.y <= 120 + 57)
        {
            window.draw(img2.drawOff());

            if(event.type == Event::MouseButtonPressed)
            {
                if((int)event.key.code == (int)Mouse::Left)
                {
                    menuGameGo = true;
                    window.close();
                }
            }
        }

        else
            window.draw(img2.drawOn());

        window.display();

    }
}
