#include "../include/game1vs1.h"

Game1vs1::Game1vs1() : GameFront("GameMode: 1 VS 1") {}

void Game1vs1::play() {
    int noCurrMoves = 0;

    while(window.isOpen()) {
        window.clear();

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        printBoard(); // print cu butoane si chestii

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here

        }

        if (game->get_status() != UNFINISHED) {
            // end of the game
            // display chestii
        }

        window.display();
    }
}
