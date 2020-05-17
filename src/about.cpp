#include "../include/about.h"

menuAbout::menuAbout()
{
    terminate = false;

    menuGameGo = false;

    if (!tusu1.loadFromFile("../images/about.jpg")) throw Exception("Failed to load image");
    susu1.setTexture(tusu1);

    size = tusu1.getSize();
}

void menuAbout::menuRun()
{
    sf::RenderWindow window(sf::VideoMode(700, 622), "MENU", sf::Style::Titlebar | sf::Style::Close);
    ImageX img1("../images/ab_b1.png", "../images/ab_b2.png", 55, 120);
    ImageX img2("../images/ab_f1.png", "../images/ab_f2.png", 490, 120);
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

        sf::Vector2i pos = sf::Mouse::getPosition(window);

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

            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.key.code == (int)sf::Mouse::Left)
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

            if(event.type == sf::Event::MouseButtonPressed)
            {
                if((int)event.key.code == (int)sf::Mouse::Left)
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
