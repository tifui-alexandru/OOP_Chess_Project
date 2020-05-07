#include "../include/game1vs1.h"

Game1vs1::Game1vs1() : GameFront("GameMode: 1 VS 1")
{
    buttonsMenuImg.loadFromFile("../images/buttons_menu.png");
    buttonsMenuSprite.setTexture(buttonsMenuImg);
    buttonsMenuSprite.setPosition(504, 0);

    atMoveBlackImg.loadFromFile("../images/black_at_move.png");
    atMoveBlackSprite.setTexture(atMoveBlackImg);

    atMoveWhiteImg.loadFromFile("../images/white_at_move.png");
    atMoveWhiteSprite.setTexture(atMoveWhiteImg);

    proposeDrawImg.loadFromFile("../images/propose_draw_button.png");
    proposeDrawSprite.setTexture(proposeDrawImg);
    proposeDrawSprite.setPosition(526, 310);

    proposeDrawNowImg.loadFromFile("../images/propose_draw_buttonNow.png");
    proposeDrawNowSprite.setTexture(proposeDrawNowImg);
    proposeDrawNowSprite.setPosition(526, 310);

    acceptDrawImg.loadFromFile("../images/accept_draw_button.png");
    acceptDrawSprite.setTexture(acceptDrawImg);

    resignImg.loadFromFile("../images/resign_button.png");
    resignSprite.setTexture(resignImg);
    resignSprite.setPosition(526, 400);

    resignNowImg.loadFromFile("../images/resign_buttonNowStrong.png");
    resignNowSprite.setTexture(resignNowImg);
    resignNowSprite.setPosition(526, 400);

    minutesWhite = 30 * 60;
    minutesBlack = 30 * 60;

    addWhite = 0;
    addBlack = 0;

    secondsLeftWhite = 30 * 60;
    secondsLeftBlack = 30 * 60;

    ant = 0;

    atMove = WHITE;

    if(!font.loadFromFile("../images/sans.ttf")){}

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

    if(auto status = game->get_status() != UNFINISHED) secondsElapsed = ant;

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
    int noCurrMoves = 0;
    bool showed = false; //daca am aratat finalul

    while(window.isOpen())
    {
        atMove = game->getPlayerToMove();
        window.clear();

        window.draw(buttonsMenuSprite);

        Vector2i posNow = Mouse::getPosition(window);
        sf::Event eventNow;

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        printTime();

        if(atMove == WHITE) window.draw(atMoveWhiteSprite); //alb la mutare
        else window.draw(atMoveBlackSprite); //negru la mutare

        if(!isMoving) {
            if (posNow.x >= 526 && posNow.x <= 526 + 126 && posNow.y >= 310 && posNow.y <= 310 + 66) {
                window.draw(proposeDrawNowSprite);

                if (eventNow.type == Event::MouseButtonPressed) {
                    if (eventNow.key.code == (int) Mouse::Left) {
                        //Game1v1Go = true;
                        //window.close();
                    }
                }
            } else
                window.draw(proposeDrawSprite);
        }
        else
            window.draw(proposeDrawSprite);


        if(!isMoving) {
            if (posNow.x >= 526 && posNow.x <= 526 + 126 && posNow.y >= 400 && posNow.y <= 400 + 66) {
                window.draw(resignNowSprite);

                if (eventNow.type == Event::MouseButtonPressed) {
                    if (eventNow.key.code == (int) Mouse::Left) {
                        //Game1v1Go = true;
                        //window.close();
                    }
                }
            } else
                window.draw(resignSprite);
        }
        else
            window.draw(resignSprite);

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here

        }

        //aici daca am mutare{ clock.reset(); ant = 0; }

        printBoard(); // print cu butoane si chestii

        if (auto status = game->get_status() != UNFINISHED && showed == false)
        {
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
        }

        window.display();
    }
}
