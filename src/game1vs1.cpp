#include "../include/game1vs1.h"
#include <iostream>

EventType Game1vs1::checkMenuClick(const int& x, const int& y) {
    if (resignButton.isInside(x, y)) return RESIGN;
    if (drawButton.isInside(x, y)) return DRAW;
    return NOTHING;
}

Game1vs1::Game1vs1() : GameFront("GameMode: 1 VS 1")
{
    if (!EndedImg.loadFromFile("../images/Ended.png")) throw Exception("Failed to load image");
    EndedSprite.setTexture(EndedImg);
    EndedSprite.setPosition(504, 0);

    if (!YesNoButtonImg.loadFromFile("../images/YesNoButton.png")) throw Exception("Failed to load image");
    YesNoButtonSprite.setTexture(YesNoButtonImg);
    YesNoButtonSprite.setPosition(526, 400);

    if (!promoteMenuImg.loadFromFile("../images/promotionMenu.png")) throw Exception("Failed to load image");
    promoteMenuSprite.setTexture(promoteMenuImg);
    promoteMenuSprite.setPosition(504, 0);

    if (!buttonsMenuImg.loadFromFile("../images/buttons_menu.png")) throw Exception("Failed to load image");
    buttonsMenuSprite.setTexture(buttonsMenuImg);
    buttonsMenuSprite.setPosition(504, 0);

    if (!atMoveBlackImg.loadFromFile("../images/black_at_move.png")) throw Exception("Failed to load image");
    atMoveBlackSprite.setTexture(atMoveBlackImg);

    if (!atMoveWhiteImg.loadFromFile("../images/white_at_move.png")) throw Exception("Failed to load image");
    atMoveWhiteSprite.setTexture(atMoveWhiteImg);

    if (!proposeDrawImg.loadFromFile("../images/propose_draw_button.png")) throw Exception("Failed to load image");
    proposeDrawSprite.setTexture(proposeDrawImg);
    proposeDrawSprite.setPosition(526, 310);

    if (!proposeDrawNowImg.loadFromFile("../images/propose_draw_buttonNow.png")) throw Exception("Failed to load image");
    proposeDrawNowSprite.setTexture(proposeDrawNowImg);
    proposeDrawNowSprite.setPosition(526, 310);

    if (!acceptDrawImg.loadFromFile("../images/accept_draw_button.png")) throw Exception("Failed to load image");
    acceptDrawSprite.setTexture(acceptDrawImg);
    acceptDrawSprite.setPosition(526, 310);

    if (!acceptDrawNowImg.loadFromFile("../images/accept_draw_buttonNow.png")) throw Exception("Failed to load image");
    acceptDrawNowSprite.setTexture(acceptDrawNowImg);
    acceptDrawNowSprite.setPosition(526, 310);

    if (!drawProposedImg.loadFromFile("../images/draw_proposed.png")) throw Exception("Failed to load image");
    drawProposedSprite.setTexture(drawProposedImg);
    drawProposedSprite.setPosition(526, 310);

    if (!resignImg.loadFromFile("../images/resign_button.png")) throw Exception("Failed to load image");
    resignSprite.setTexture(resignImg);
    resignSprite.setPosition(526, 400);

    if (!resignNowImg.loadFromFile("../images/resign_buttonNowStrong.png")) throw Exception("Failed to load image");
    resignNowSprite.setTexture(resignNowImg);
    resignNowSprite.setPosition(526, 400);

    if (!YesButtonImg.loadFromFile("../images/YesButton.png")) throw Exception("Failed to load image");
    YesButtonSprite.setTexture(YesButtonImg);
    YesButtonSprite.setPosition(526, 400);

    if (!NoButtonImg.loadFromFile("../images/NoButton.png")) throw Exception("Failed to load image");
    NoButtonSprite.setTexture(NoButtonImg);
    NoButtonSprite.setPosition(526, 400);

    minutesWhite = 30 * 60;
    minutesBlack = 30 * 60;

    addWhite = 0;
    addBlack = 0;

    secondsLeftWhite = 30 * 60;
    secondsLeftBlack = 30 * 60;

    ant = 0;

    atMove = WHITE;

    if (!font.loadFromFile("../images/sans.ttf")) throw Exception("Failed to load image");

    textWhite.setFont(font);
    textBlack.setFont(font);

    textWhite.setCharacterSize(50);

    textWhite.setFillColor(sf::Color::Red);

    textWhite.setStyle(sf::Text::Bold);

    textWhite.setPosition(520, 70);


    textBlack.setCharacterSize(50);

    textBlack.setFillColor(sf::Color::Blue);

    textBlack.setStyle(sf::Text::Bold);

    textBlack.setPosition(520, 10);


    atMoveWhiteSprite.setPosition(529, 150);
    atMoveBlackSprite.setPosition(529, 150);
}

void Game1vs1::printTime()
{
    sf::Time elapsed = clock.getElapsedTime();
    float secondsElapsed = elapsed.asSeconds();

    if(game->get_status() != UNFINISHED) secondsElapsed = ant;

    if(atMove == WHITE)
    {
        addWhite += (secondsElapsed - ant);
        secondsLeftWhite = minutesWhite - addWhite;

        //if (secondsLeftWhite < 0) //alb pierde ca nu mai are timp
    }

    if(atMove == BLACK)
    {
        addBlack += (secondsElapsed - ant);
        secondsLeftBlack = minutesBlack - addBlack;
        //if (secondsElapsed < 0) break; //alb pierde ca nu mai are timp
    }

    int showWhite2 = (int)secondsLeftWhite % 60;
    int showBlack2 = (int)secondsLeftBlack % 60;

    int showWhite1 = (int)secondsLeftWhite / 60;
    int showBlack1 = (int)secondsLeftBlack / 60;

    std::string usuWhite = "";
    std::string usuBlack = "";

    if(showWhite1 < 10) usuWhite += '0';
    usuWhite += std::to_string(showWhite1);

    usuWhite += ':';

    if(showWhite2 < 10) usuWhite += '0';
    usuWhite += std::to_string(showWhite2);

    textWhite.setString(usuWhite);

    //sus white jos black

    if(showBlack1 < 10) usuBlack += '0';
    usuBlack += std::to_string(showBlack1);

    usuBlack += ':';

    if(showBlack2 < 10) usuBlack += '0';
    usuBlack += std::to_string(showBlack2);

    textBlack.setString(usuBlack);


    window.draw(textBlack);
    window.draw(textWhite);

    ant = secondsElapsed;
}

void Game1vs1::play()
{
    bool showed = false; //daca am aratat finalul
    bool whiteWantsResign = false;
    bool blackWantsResign = false;
    int whenBlack = -1;
    int whenWhite = -1;
    bool whiteResigned = false;
    bool blackResigned = false;

    bool drawEnd = false;
    int whenDraw = -2;

    while(window.isOpen())
    {
        atMove = game->getPlayerToMove();
        window.clear();

        window.draw(promoteMenuSprite);

        sf::Vector2i posNow = sf::Mouse::getPosition(window);

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        window.draw(buttonsMenuSprite);

        printTime();

        if(atMove == WHITE) window.draw(atMoveWhiteSprite); //alb la mutare
        else window.draw(atMoveBlackSprite); //negru la mutare

        //BUTON DE DRAW//////////////////////////////////////////////////////////////////////////

        if(!isMoving) {

            if (drawButton.isInside(posNow.x, posNow.y)) {
                if (whenDraw == game->get_no_moves() - 1) {
                    window.draw(acceptDrawNowSprite);

                    if (event != NOTHING) {
                        drawEnd = true;
                    }
                } else {
                    window.draw(proposeDrawNowSprite);
                    if (event != NOTHING) whenDraw = game->get_no_moves();
                }
            }
            else{
                if(whenDraw == game->get_no_moves() - 1) window.draw(acceptDrawSprite);
                else window.draw(proposeDrawSprite);
            }
        }
        else{
            if(whenDraw == game->get_no_moves() - 1) window.draw(acceptDrawSprite);
            else window.draw(proposeDrawSprite);
        }

        if(whenDraw == game->get_no_moves()) window.draw(drawProposedSprite);


        /*if(!isMoving) {
            if (drawButton.isInside(posNow.x, posNow.y)) {
                window.draw(proposeDrawNowSprite);

                if (event == DRAW) {
                        //Game1v1Go = true;
                        //window.close();
                }
            } else
                window.draw(proposeDrawSprite);
        }
        else
            window.draw(proposeDrawSprite);*/


        //BUTON DE RESIGN////////////////////////////////////////////////////////////////////////



        if(!isMoving)
        {
            if (resignButton.isInside(posNow.x, posNow.y))
            {

                window.draw(resignNowSprite);

                if (event == RESIGN)
                {
                    if(game->getPlayerToMove() == WHITE) {
                        if (whiteWantsResign == true && whenWhite == game->get_no_moves()) {
                            if (acceptResign.isInside(posNow.x, posNow.y)) {
                                whiteResigned = true;
                                game->set_resign();
                            }
                            else
                            {
                                whiteWantsResign = false;
                            }
                        }
                        else
                        {
                            whiteWantsResign = true;
                            whenWhite = game->get_no_moves();
                        }
                    }

                    if(game->getPlayerToMove() == BLACK)
                    {
                        if(blackWantsResign == true && whenBlack == game->get_no_moves()) {
                            if (acceptResign.isInside(posNow.x, posNow.y)) {
                                blackResigned = true;
                                game->set_resign();
                            }
                            else
                            {
                                blackWantsResign = false;
                            }
                        }
                        else
                        {
                            blackWantsResign = true;
                            whenBlack = game->get_no_moves();
                        }
                    }

                }

                if(whiteWantsResign == true && whenWhite == game->get_no_moves())
                {
                    window.draw(YesNoButtonSprite);
                    if (acceptResign.isInside(posNow.x, posNow.y)) window.draw(YesButtonSprite);
                    else window.draw(NoButtonSprite);
                }

                if(whiteWantsResign == true && whenWhite != game->get_no_moves()) whiteWantsResign = false;

                if(blackWantsResign == true && whenBlack == game->get_no_moves())
                {
                    window.draw(YesNoButtonSprite);
                    if (acceptResign.isInside(posNow.x, posNow.y)) window.draw(YesButtonSprite);
                    else window.draw(NoButtonSprite);
                }

                if(blackWantsResign == true && whenBlack != game->get_no_moves()) blackWantsResign = false;

            }
            else
            {
                window.draw(resignSprite);

                if(whiteWantsResign == true && whenWhite == game->get_no_moves())
                {
                    window.draw(YesNoButtonSprite);
                }

                if(whiteWantsResign == true && whenWhite != game->get_no_moves()) whiteWantsResign = false;

                if(blackWantsResign == true && whenBlack == game->get_no_moves())
                {
                    window.draw(YesNoButtonSprite);
                }

                if(blackWantsResign == true && whenBlack != game->get_no_moves()) blackWantsResign = false;
            }
        }
        else
            window.draw(resignSprite);

        //aici daca am mutare{ clock.reset(); ant = 0; }

        printBoard(); // print cu butoane si chestii

        auto status = game->get_status();

        if (drawEnd == true) game->set_resign();

        if (status != UNFINISHED && showed == false)
        {
            window.clear();
            printBoard();
            window.draw(EndedSprite);
            window.display();
            showed = true;

            if(status == RESIGNATION && drawEnd == true)
            {
                showEnd final(1);
                final.showRun();
            }

            if((status == CHECKMATE && game->getPlayerToMove() == BLACK) || blackResigned == true)
            {
                showEnd final(3);
                final.showRun();
            }

            if((status == CHECKMATE && game->getPlayerToMove() == WHITE) || whiteResigned == true)
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
}
