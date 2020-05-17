#include "../include/game1vsPC.h"
#include "../include/chessEngine.h"
#include <string>
#include <cstring>

EventType Game1vsPC::checkMenuClick(const int& x, const int& y) {
    if (endButton.isInside(x, y)) return END_GAME;
    if (hintButton.isInside(x, y)) return GET_HINT;
    return NOTHING;
}

Game1vsPC::Game1vsPC(const PieceColour &humanCol) : GameFront("GameMode: 1 VS PC"), humanPlayer(humanCol)
{
    if (!EndedMenuImg.loadFromFile("../images/Ended.png")) throw Exception("Failed to load image");
    EndedMenuSprite.setTexture(EndedMenuImg);
    EndedMenuSprite.setPosition(504, 0);

    if (!endGameButtonImg.loadFromFile("../images/endGameButton.png")) throw Exception("Failed to load image");
    endGameButtonSprite.setTexture(endGameButtonImg);
    endGameButtonSprite.setPosition(526, 350);

    if (!EndedImg.loadFromFile("../images/YesNoBig.png")) throw Exception("Failed to load image");
    EndedSprite.setTexture(EndedImg);
    EndedSprite.setPosition(526, 350);

    if (!NoEndedImg.loadFromFile("../images/NoBig.png")) throw Exception("Failed to load image");
    NoEndedSprite.setTexture(NoEndedImg);
    NoEndedSprite.setPosition(526, 350);

    if (!YesEndedImg.loadFromFile("../images/YesBig.png")) throw Exception("Failed to load image");
    YesEndedSprite.setTexture(YesEndedImg);
    YesEndedSprite.setPosition(526, 350);

    if (!endGameButtonNowImg.loadFromFile("../images/endGameButtonNow.png")) throw Exception("Failed to load image");
    endGameButtonNowSprite.setTexture(endGameButtonNowImg);
    endGameButtonNowSprite.setPosition(526, 350);

    if (!getHintButtonImg.loadFromFile("../images/get_hint_button.png")) throw Exception("Failed to load image");
    getHintButtonSprite.setTexture(getHintButtonImg);
    getHintButtonSprite.setPosition(526, 250);

    if (!getHintButtonNowImg.loadFromFile("../images/get_hint_buttonNow.png")) throw Exception("Failed to load image");
    getHintButtonNowSprite.setTexture(getHintButtonNowImg);
    getHintButtonNowSprite.setPosition(526, 250);

    if (!promoteMenuImg.loadFromFile("../images/promotionMenu.png")) throw Exception("Failed to load image");
    promoteMenuSprite.setTexture(promoteMenuImg);
    promoteMenuSprite.setPosition(504, 0);

    if (!buttonsMenuImg.loadFromFile("../images/buttons_menu.png")) throw Exception("Failed to load image");
    buttonsMenuSprite.setTexture(buttonsMenuImg);
    buttonsMenuSprite.setPosition(504, 0);

    if (!font.loadFromFile("../images/sans.ttf")) throw Exception("Failed to load image");

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
    bool wantResign = false;
    int whenResign = -1;
    int noCurrMoves = 0;
    PieceColour playerMoving = WHITE;
    std::string currBoardPosition;
    ConnectToEngine("../stockfish.exe");

    while(window.isOpen()) {
        window.clear();

        window.draw(promoteMenuSprite);
        sf::Vector2i posNow = sf::Mouse::getPosition(window);
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

        printTime();


        //ENDED BUTTON //////////////////////////////////////////////////////////////////////////////////
        if(!isMoving)
        {
            if (endButton.isInside(posNow.x, posNow.y))
            {

                window.draw(endGameButtonNowSprite);

                if (event != NOTHING) {
                    if (game->getPlayerToMove() == WHITE) {
                        if (wantResign == true && whenResign == game->get_no_moves()) {
                            if (acceptEndButton.isInside(posNow.x, posNow.y)) {
                                game->set_resign();
                            } else {
                                wantResign = false;
                            }
                        } else {
                            wantResign = true;
                            whenResign = game->get_no_moves();
                        }
                    }
                }
                if(wantResign == true && whenResign == game->get_no_moves())
                {
                    window.draw(EndedSprite);
                    if (acceptEndButton.isInside(posNow.x, posNow.y)) window.draw(YesEndedSprite);
                    else window.draw(NoEndedSprite);
                }

                if(wantResign == true && whenResign != game->get_no_moves()) wantResign = false;

            }
            else
            {
                window.draw(endGameButtonSprite);

                if(wantResign == true && whenResign == game->get_no_moves())
                {
                    window.draw(EndedSprite);
                }

                if(wantResign == true && whenResign != game->get_no_moves()) wantResign = false;

            }
        }
        else
            window.draw(endGameButtonSprite);

        //////////////////////////////////////////////////////////////////////////////////////

        if(!isMoving) {
            if (hintButton.isInside(posNow.x, posNow.y)) {
                window.draw(getHintButtonNowSprite);

                if (event == GET_HINT) {
                    PieceType newPiece = PAWN;
                    std::pair <Square, Square> hint = getStockfishMove(currBoardPosition, newPiece);

                    std::memset(hintMove, false, sizeof(hintMove));
                    hintMove[hint.first.x][hint.first.y] = hintMove[hint.second.x][hint.second.y] = true;
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
            window.draw(EndedMenuSprite);
            window.display();
            showed = true;

            if(status == RESIGNATION)
            {
                showEnd final(4);
                final.showRun();
            }

            if(status == CHECKMATE && game->getPlayerToMove() == BLACK)
            {
                showEnd final(5);
                final.showRun();
            }

            if(status == CHECKMATE && game->getPlayerToMove() == WHITE)
            {
                showEnd final(4);
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
