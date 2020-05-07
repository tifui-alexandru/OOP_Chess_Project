#include "../include/showEnd.h"


showEnd::showEnd(/*GameStatus status*/int status) {

    //aici cand fac egal

    if (status == 1) {
        endT.loadFromFile("../images/draw_end.png");
        endS.setTexture(endT);
    }

    //aici cand bate negru

    if (status == 2) {
        endT.loadFromFile("../images/black_won.png");
        endS.setTexture(endT);
    }

    //aici cand bate alb

    if (status == 3) {
        endT.loadFromFile("../images/white_won.png");
        endS.setTexture(endT);
    }

    size = endT.getSize();
}

showEnd::~showEnd(){}

void showEnd::showRun()
{
    sf::RenderWindow window(sf::VideoMode(296, 124), "THE END", sf::Style::Titlebar | sf::Style::Close);
    // VideoMode - > window size
    // "MENU" -> window title
    // style -> can not be resizable
    while(window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            //until we close the window

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);

        //get the position every time to know where the mouse is

        window.clear();
        //refresh

        window.draw(endS);

        //oriunde apesi, ti se inchise fereastra
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.key.code == (int) sf::Mouse::Left) {
                window.close();
            }
        }

        window.display();

    }
}
