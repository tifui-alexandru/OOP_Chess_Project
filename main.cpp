#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace sf;

#include "include/MainMenu.h"
#include "include/GameMenu.h"
#include "include/game1vs1.h"
#include "include/about.h"
#include "include/game1vsPC.h"

int main()
{
    Game1vsPC t;
    t.play();

//    sf::RenderWindow window( sf::VideoMode( 400, 600 ), "Awesome Game" );
//
//    sf::Time micro = sf::microseconds( 10000 );
//    sf::Time milli = sf::milliseconds( 10 );
//    sf::Time second = sf::seconds( 0.01f );
//
//    //std::cout << micro.asSeconds( ) << std::endl;
//    //std::cout << micro.asMilliseconds( ) << std::endl;
//    //std::cout << micro.asMicroseconds( ) << std::endl;
//
//    //std::cout << ( micro + milli ).asSeconds( ) << std::endl;
//
//    sf::Clock clock; // starts the clock
//    float pwp = 30 * 60;
//
//    while ( window.isOpen( ))
//    {
//        sf::Event event;
//
//        while ( window.pollEvent( event ) )
//        {
//            switch ( event.type )
//            {
//                case sf::Event::Closed:
//                    window.close( );
//
//                    break;
//
//                case sf::Event::KeyReleased:
//                    clock.restart( );
//
//                    break;
//            }
//        }
//        window.clear( );
//
//        sf::Text text;
//
//        sf::Font font;
//        if(!font.loadFromFile("../images/sans.ttf")){}
//
//        sf::Time elapsed = clock.getElapsedTime( );
//        std::cout << elapsed.asSeconds( ) << std::endl;
//        //float a = elapsed.asSeconds();
//        int t1 = elapsed.asSeconds();
//
//        t1 = pwp - t1;
//        if(t1 < 0) break ;
//
//        text.setFont(font);
//
//        int t2 = t1 % 60;
//
//        t1 /= 60;
//
//        std::string usu = "";
//        if(t1 < 10) usu += '0';
//        usu += std::to_string(t1);
//
//    // menuGame t1;
//    // menuMode t2;
//    // menuAbout t4;
//
//        //std::string usu2="";
//
//        //int k = 0;
//        //while(usu[k] != '.') usu2.push_back(usu[k++]);
//
//        //usu2.push_back('.');
//        //++k;
//        //usu2.push_back(usu[k++]);
//        //usu2.push_back(usu[k++]);
//
//        text.setString(usu);
//
//        text.setCharacterSize(80);
//
//        text.setFillColor(sf::Color::Red);
//
//        text.setStyle(sf::Text::Bold);
//
//        text.setPosition(100, 200);
//
//        window.draw(text);
//
//
//
//        window.display( );
//    }



///////////////////////////////////////////////////////////////////////////////////////////////////


//    menuGame t1;
//    menuMode t2;
//    menuAbout t4;
//
//
//    bool menuModeGo = false;
//    bool menuGameGo = true;
//    bool menuAboutGo = false;
//    bool Game1v1Go = false;
//
//
//    do{
//        if(menuGameGo == true)
//        {
//            t1.menuRun();
//            menuGameGo = false;
//
//            if(t1.menuModeGo == true)
//            {
//                t1.menuModeGo = false;
//                menuModeGo = true;
//            }
//
//            if(t1.menuAboutGo == true)
//            {
//                t1.menuAboutGo = false;
//                menuAboutGo = true;
//            }
//        }
//
//        if(menuModeGo == true)
//        {
//            t2.menuRun();
//            menuModeGo = false;
//
//            if(t2.Game1v1Go == true)
//            {
//                t2.Game1v1Go = false;
//                Game1v1Go = true;
//            }
//
//            if(t2.menuGameGo == true)
//            {
//                t2.menuGameGo = false;
//                menuGameGo = true;
//            }
//        }
//
//        if(Game1v1Go == true)
//        {
//            Game1vs1 t3;
//            t3.play();
//            Game1v1Go = false;
//        }
//
//        if(menuAboutGo == true)
//        {
//            t4.menuRun();
//            menuAboutGo = false;
//
//            if(t4.menuGameGo == true)
//            {
//                t4.menuGameGo = false;
//                menuGameGo = true;
//            }
//        }
//
//
//     }while(menuModeGo == true || menuGameGo == true || menuAboutGo == true || Game1v1Go == true);

    return 0;
}
