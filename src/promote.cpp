#include "../include/promote.h"

promote::promote() {


    promoteT.loadFromFile("../images/choose_piece.png");
    promoteS.setTexture(promoteT);

    chosenType = 0;

    size = promoteT.getSize();
}

promote::~promote(){}

void promote::promoteRun()
{
    RenderWindow window(sf::VideoMode(226, 70), "MENU", sf::Style::Titlebar | sf::Style::Close);
    // VideoMode - > window size
    // "MENU" -> window title
    // style -> can not be resizable
    while(window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            //until we close the window

            if (event.type == sf::Event::Closed) {
                //window.close();

                //nu poti sa dai X ca sa se inchida ca busesti programu
            }
        }

        Vector2i pos = Mouse::getPosition(window);

        //get the position every time to know where the mouse is

        window.clear();
        //refresh

        window.draw(promoteS);

        //oriunde apesi, ti se inchise fereastra
        if (event.type == Event::MouseButtonPressed) {
            if (event.key.code == (int) Mouse::Left) {
                if(pos.x >= 0 && pos.x <= 226 / 4)
                {
                    chosenType = 1; //tura
                }
                else if(pos.x > 226 / 4 && pos.x <= 226 / 2)
                {
                    chosenType = 2; //cal
                }
                else if(pos.x > 226 / 2 && pos.x <= 3 * 226 / 2)
                {
                    chosenType = 3; //nebun
                }
                else
                {
                    chosenType = 4; //regina
                }
                window.close();
            }
        }

        window.display();

    }
}