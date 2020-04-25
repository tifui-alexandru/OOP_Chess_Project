#include "../include/game1vs1.h"

Game1vs1::Game1vs1() {
    GameFront();
}

void Game1vs1::play() {
    while(window.isOpen()) {
        window.clear();

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        printBoard(); // print cu butoane si chestii

        if (game->)

        window.display();
    }
}
