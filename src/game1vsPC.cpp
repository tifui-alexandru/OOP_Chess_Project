#include "../include/game1vsPC.h"
#include "../include/chessEngine.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstring>

EventType Game1vsPC::checkMenuClick(const int& x, const int& y) {
    if (endButton.isInside(x, y)) return END_GAME;
    if (hintButton.isInside(x, y)) return GET_HINT;
    return NOTHING;
}

Game1vsPC::Game1vsPC(const PieceColour &humanCol) : GameFront("GameMode: 1 VS PC"), humanPlayer(humanCol)
{
    endGameButtonImg.loadFromFile("../images/endGameButton.png");
    endGameButtonSprite.setTexture(endGameButtonImg);
    endGameButtonSprite.setPosition(526, 350);

    endGameButtonNowImg.loadFromFile("../images/endGameButtonNow.png");
    endGameButtonNowSprite.setTexture(endGameButtonNowImg);
    endGameButtonNowSprite.setPosition(526, 350);

    getHintButtonImg.loadFromFile("../images/get_hint_button.png");
    getHintButtonSprite.setTexture(getHintButtonImg);
    getHintButtonSprite.setPosition(526, 250);

    getHintButtonNowImg.loadFromFile("../images/get_hint_buttonNow.png");
    getHintButtonNowSprite.setTexture(getHintButtonNowImg);
    getHintButtonNowSprite.setPosition(526, 250);

    promoteMenuImg.loadFromFile("../images/promotionMenu.png");
    promoteMenuSprite.setTexture(promoteMenuImg);
    promoteMenuSprite.setPosition(504, 0);

    buttonsMenuImg.loadFromFile("../images/buttons_menu.png");
    buttonsMenuSprite.setTexture(buttonsMenuImg);
    buttonsMenuSprite.setPosition(504, 0);

    if(!font.loadFromFile("../images/sans.ttf"));

    text.setFont(font);

    text.setCharacterSize(50);

    text.setFillColor(sf::Color::Black);

    text.setStyle(sf::Text::Bold);

    text.setPosition(520, 50);
}

void Game1vsPC::printTime()
{
    sf::Time elapsed = clock.getElapsedTime();
    float secondsElapsed = elapsed.asSeconds();

    int show2 = (int)secondsElapsed % 60;

    int show1 = (int)secondsElapsed / 60;

    std::string usu = "";

    if(show1 < 10) usu += '0';
    usu += std::to_string(show1);

    usu += ':';

    if(show2 < 10) usu += '0';
    usu += std::to_string(show2);

    text.setString(usu);

    window.draw(text);

}

void Game1vsPC::play()
{
    bool showed = false; //daca am aratat finalul
    int noCurrMoves = 0;
    PieceColour playerMoving = WHITE;
    std::string currBoardPosition;
    ConnectToEngine("../stockfish.exe");

    while(window.isOpen()) {
        window.clear();

        window.draw(promoteMenuSprite);
        Vector2i posNow = Mouse::getPosition(window);
        EventType event = checkClick();

        if (playerMoving == humanPlayer) {
            if (event == BOARD_CLICK) {
                squareClicked();
            }
        }
        else {
            PieceType newPiece = PAWN;
            std::pair <Square, Square> computerMove = getStockfishMove(currBoardPosition, newPiece);
            game->make_move(computerMove.first, computerMove.second);
            if (newPiece != PAWN) game->promote(computerMove.second, newPiece);
        }

        window.draw(buttonsMenuSprite);

        //printTime();

        if(!isMoving) {
            if (endButton.isInside(posNow.x, posNow.y)) {
                window.draw(endGameButtonNowSprite);

                /*if (event == MENU_CLICK) {
                    //Game1v1Go = true;
                    //window.close();
                }*/
            } else
                window.draw(endGameButtonSprite);
        }
        else
            window.draw(endGameButtonSprite);

        if(!isMoving) {
            if (hintButton.isInside(posNow.x, posNow.y)) {
                window.draw(getHintButtonNowSprite);

                if (event == GET_HINT) {
                    PieceType newPiece = PAWN;
                    std::pair <Square, Square> hint = getStockfishMove(currBoardPosition, newPiece);

                    std::memset(validMove, false, sizeof(validMove));
                    validMove[hint.first.x][hint.first.y] = validMove[hint.second.x][hint.second.y] = true;
                }
            } else
                window.draw(getHintButtonSprite);
        }
        else
            window.draw(getHintButtonSprite);


        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here
            
            currBoardPosition += mv->toLongAlgebraicNotation() + " ";
            playerMoving = (playerMoving == WHITE ? BLACK : WHITE);

            ++noCurrMoves;
        }

        printBoard(); // print cu butoane si chestii

        auto status = game->get_status();

        if (status != UNFINISHED && showed == false)
        {
            window.clear();
            printBoard();
            window.display();
            showed = true;
            if(status == CHECKMATE && game->getPlayerToMove() == BLACK)
            {
                showEnd final(3);
                final.showRun();
            }

            if(status == CHECKMATE && game->getPlayerToMove() == WHITE)
            {
                showEnd final(2);
                final.showRun();
            }

            if(status == REPETITION || status == INSUFFICIENT_MATERIAL || status == MOVE50RULE || status == AGREEMENT || status == STALEMATE)
            {
                showEnd final(1);
                final.showRun();
            }
            window.close();
        }

        window.display();
    }
    CloseConnection();
}