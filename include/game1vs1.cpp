#include "../include/game1vs1.h"

Game1vs1::Game1vs1() {
    GameFront();
}

void Game1vs1::play() {
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window); 

            if (event.type == sf::Event::MouseButtonPressed) {
                if (!isMoving) {
                    if (event.key.code == sf::Mouse::Left) {
                        if (!boardBox.isInside(mousePos.x, mousePos.y)) continue;

                        clickedSquare = getSquare(mousePos);
                        if (game->get_board()->get_piece(clickedSquare))
                            isMoving = true;
                    }
                }
            }
        }

        window.display();
    }
}

