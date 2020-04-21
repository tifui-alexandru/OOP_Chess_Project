// #include <iostream>
// #include <bits/stdc++.h>
// #include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

// int main( )
// {
//     sf::RenderWindow window( sf::VideoMode( 400, 600 ), "Awesome Game" );

//     sf::Time micro = sf::microseconds( 10000 );
//     sf::Time milli = sf::milliseconds( 10 );
//     sf::Time second = sf::seconds( 0.01f );

//     std::cout << micro.asSeconds( ) << std::endl;
//     std::cout << micro.asMilliseconds( ) << std::endl;
//     std::cout << micro.asMicroseconds( ) << std::endl;

//     std::cout << ( micro + milli ).asSeconds( ) << std::endl;

//     sf::Clock clock; // starts the clock
//     float pwp = 7;

//     while ( window.isOpen( ))
//     {
//         sf::Event event;

//         while ( window.pollEvent( event ) )
//         {
//             switch ( event.type )
//             {
//                 case sf::Event::Closed:
//                     window.close( );

//                     break;

//                 case sf::Event::KeyReleased:
//                     clock.restart( );

//                     break;
//             }
//         }
//         window.clear( );

//         sf::Text text;

//         sf::Font font;
//         if(!font.loadFromFile("images/sans.ttf")){}

//         sf::Time elapsed = clock.getElapsedTime( );
//         std::cout << elapsed.asSeconds( ) << std::endl;
//         float a = elapsed.asSeconds();

//         a = pwp - a;
//         if(a<0) break ;

//         text.setFont(font);

//         std::string usu = std::to_string(a);

//         std::string usu2="";

//         int k = 0;
//         while(usu[k] != '.') usu2.push_back(usu[k++]);

//         usu2.push_back('.');
//         ++k;
//         usu2.push_back(usu[k++]);
//         usu2.push_back(usu[k++]);

//         text.setString(usu2);

//         text.setCharacterSize(80);

//         text.setFillColor(sf::Color::Red);

//         text.setStyle(sf::Text::Bold);

//         text.setPosition(100, 200);

//         window.draw(text);



//         window.display( );
//     }

//     return EXIT_SUCCESS;
// }
