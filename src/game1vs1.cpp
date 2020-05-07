#include "../include/game1vs1.h"

Game1vs1::Game1vs1() : GameFront("GameMode: 1 VS 1")
{
    atMoveBlackImg.loadFromFile("../images/black_at_move.png");
    atMoveBlackSprite.setTexture(atMoveBlackImg);

    atMoveWhiteImg.loadFromFile("../images/white_at_move.png");
    atMoveWhiteSprite.setTexture(atMoveWhiteImg);

    proposeDrawImg.loadFromFile("../images/propose_draw_button.png");
    proposeDrawSprite.setTexture(proposeDrawImg);

    acceptDrawImg.loadFromFile("../images/accept_draw_button.png");
    acceptDrawSprite.setTexture(acceptDrawImg);

    resignImg.loadFromFile("../images/resign_button.png");
    resignSprite.setTexture(resignImg);
    resignSprite.setPosition(520, 200);
}

void Game1vs1::play() {
    int noCurrMoves = 0;

    while(window.isOpen()) {
        window.clear();

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        printBoard(); // print cu butoane si chestii

        window.draw(resignSprite);

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here

        }

        if (auto status = game->get_status() != UNFINISHED) {
            // end of the game
            // display chestii
        }

        window.display();
    }
}
