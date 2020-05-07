#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "include/startGame.h"
int main()
{
    startGame t;
    t.runStart();
//    Game1vsPC t1;
//    t1.play();

return 0;
    sf::RenderWindow window( sf::VideoMode( 400, 600 ), "Awesome Game" );

    //std::cout << micro.asSeconds( ) << std::endl;
    //std::cout << micro.asMilliseconds( ) << std::endl;
    //std::cout << micro.asMicroseconds( ) << std::endl;

    //std::cout << ( micro + milli ).asSeconds( ) << std::endl;

    sf::Clock clock; // starts the clock
    float minutesWhite = 30 * 60;
    float minutesBlack = 30 * 60;

    float addWhite = 0;
    float addBlack = 0;

    float secondsLeftWhite = 30 * 60;
    float secondsLeftBlack = 30 * 60;

    float ant = 0;

    int atMove = 1;

    while ( window.isOpen( ))
    {
        sf::Event event;

        while ( window.pollEvent( event ) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close( );

                    break;

                case sf::Event::KeyReleased:
                    clock.restart( );

                    break;
            }
        }
        window.clear( );

        sf::Text textWhite;
        sf::Text textBlack;

        sf::Font font;
        if(!font.loadFromFile("../images/sans.ttf")){}

        sf::Time elapsed = clock.getElapsedTime( );
        std::cout << elapsed.asSeconds( ) << std::endl;

        float secondsElapsed = elapsed.asSeconds();

        if(atMove == 1)
        {
            addWhite += (secondsElapsed - ant);
            secondsLeftWhite = minutesWhite - addWhite;
            //if (secondsLeftWhite < 0) //alb pierde ca nu mai are timp

                if (secondsLeftWhite < 60 * 29 + 56) {
                    atMove = 2;
                    ant = 0;
                    clock.restart();
                }
        }

        if(atMove == 2)
        {
            addBlack += (secondsElapsed - ant);
            secondsLeftBlack = minutesBlack - addBlack;
            if (secondsElapsed < 0) break; //alb pierde ca nu mai are timp
        }

        textWhite.setFont(font);
        textBlack.setFont(font);

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

        textWhite.setCharacterSize(80);

        textWhite.setFillColor(sf::Color::Red);

        textWhite.setStyle(sf::Text::Bold);

        textWhite.setPosition(100, 200);

        window.draw(textWhite);



        if(showBlack1 < 10) usuBlack += '0';
        usuBlack += std::to_string(showBlack1);

        usuBlack += ':';

        if(showBlack2 < 10) usuBlack += '0';
        usuBlack += std::to_string(showBlack2);

        textBlack.setString(usuBlack);

        textBlack.setCharacterSize(80);

        textBlack.setFillColor(sf::Color::Blue);

        textBlack.setStyle(sf::Text::Bold);

        textBlack.setPosition(100, 400);

        window.draw(textBlack);

        ant = secondsElapsed;

        window.display( );
    }

    return 0;
}
