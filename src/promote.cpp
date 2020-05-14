#include "../include/promote.h"

Promote::Promote() 
{
    if (!promoteT.loadFromFile("../images/choose_piece.png")) throw std::runtime_error("Failed to load image");
    promoteS.setTexture(promoteT);

    chosenType = PAWN;

    size = promoteT.getSize();
}

void Promote::promoteRun()
{
    RenderWindow window(sf::VideoMode(226, 70), "Promotion", sf::Style::Titlebar | sf::Style::Close);
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
                    chosenType = ROOK; 
                }
                else if(pos.x > 226 / 4 && pos.x <= 226 / 2)
                {
                    chosenType = KNIGHT; 
                }
                else if(pos.x > 226 / 2 && pos.x <= 3 * 226 / 4)
                {
                    chosenType = BISHOP;
                }
                else
                {
                    chosenType = QUEEN; 
                }
                window.close();
            }
        }

        window.display();

    }
}

PieceType Promote::getPiece() 
{
    promoteRun(); 
    
    return chosenType; 
}
