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

    minutesWhite = 30 * 60;
    minutesBlack = 30 * 60;

    addWhite = 0;
    addBlack = 0;

    secondsLeftWhite = 30 * 60;
    secondsLeftBlack = 30 * 60;

    ant = 0;

    atMove = 1; //white at move; 2 -> black
    antMove = 1; //cine e anterior

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

    if(atMove == 1)
    {
        addWhite += (secondsElapsed - ant);
        secondsLeftWhite = minutesWhite - addWhite;

        //if (secondsLeftWhite < 0) //alb pierde ca nu mai are timp
    }

    if(atMove == 2)
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

    while(window.isOpen())
    {
        window.clear();

        EventType event = checkClick();
        if (event == BOARD_CLICK) {
            squareClicked();
        }

        printBoard(); // print cu butoane si chestii

        printTime();

        if(atMove == 1) window.draw(atMoveWhiteSprite); //alb la mutare
        else window.draw(atMoveBlackSprite); //negru la mutare

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here

        }

        //aici daca am mutare{ clock.reset(); ant = 0; }

        if (auto status = game->get_status() != UNFINISHED) {
            // end of the game
            // display chestii
        }

        window.display();
    }
}
