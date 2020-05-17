#include "../include/showEnd.h"


showEnd::showEnd(/*GameStatus status*/int status) {

    //aici cand fac egal

    if (status == 1) {
        if (!endT.loadFromFile("../images/draw_end.png")) throw Exception("Failed to load image");
        endS.setTexture(endT);
    }

    //aici cand bate negru

    if (status == 2) {
        if (!endT.loadFromFile("../images/black_won.png")) throw Exception("Failed to load image");
        endS.setTexture(endT);
    }

    //aici cand bate alb

    if (status == 3) {
        if (!endT.loadFromFile("../images/white_won.png")) throw Exception("Failed to load image");
        endS.setTexture(endT);
    }

    //cand pierd eu

    if(status == 4) {
        if (!endT.loadFromFile("../images/you_lost.png")) throw Exception("Failed to load image");
        endS.setTexture(endT);
    }

    //cand bat eu

    if(status == 5){
        if (!endT.loadFromFile("../images/you_won.png")) throw Exception("Failed to load image");
        endS.setTexture(endT);
    }

    size = endT.getSize();
}

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
