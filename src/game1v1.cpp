#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
//#include "../Connector.hpp"

using namespace sf;

#include "../include/game1v1.h"

Game1v1::Game1v1()
{
    terminate = false;

    usux = 0;

    usuy = 0;

    n = 0;

    str = "";

    position = "";

    isMove = false;

    offset.x = 28;
    offset.y = 28;
}

Game1v1::~Game1v1()
{
    //CloseConnection();
}

std::string Game1v1::toChessNote(Vector2f p)
{
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

Vector2f Game1v1::toCoord(char a, char b) //normal coordinates
{
   int x = int(a) - 97;
   int y = 7 - int(b) + 49;
   return Vector2f(x * size, y * size);
}

void Game1v1::move(std::string str)
{
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);

    for(int i = 0; i < 32; ++i)
        if(f[i].getPosition() == newPos) f[i].setPosition(-100, -100); //erase

    for(int i = 0; i < 32; ++i)
        if(f[i].getPosition() == oldPos) f[i].setPosition(newPos); //move

    //castling       //if the king didn't move
    if(str == "e1g1")
        if(position.find("e1") == -1) move("h1f1");
    if(str == "e8g8")
        if(position.find("e8") == -1) move("h8f8");
    if(str == "e1c1")
        if(position.find("e1") == -1) move("a1d1");
    if(str == "e8c8")
        if(position.find("e8") == -1) move("a8d8");
}

void Game1v1::loadPosition()
{
    int k = 0;
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            int n = board[i][j];
            if(!n) continue;
            int x = abs(n) - 1;
            int y = n>0?1:0;

            f[k].setTextureRect( IntRect(size * x, size * y, size, size) );
            f[k].setPosition(size * j, size * i);

            f2[k].setTextureRect( IntRect(size * x, size * y, size, size) );
            f2[k].setPosition(size * j, size * i);

            f3[k].setTextureRect( IntRect(size * x, size * y, size, size) );
            f3[k].setPosition(size * j, size * i);

            ++k;
        }
    }

    for(int i = 0; i < position.length(); i += 5)
        move(position.substr(i, 4));
}

void Game1v1::releaseMove()
{
    newPos = oldPos;

    //std::cout << "NEW:  " << newPos.x/size << ' ' << newPos.y/size << '\n';

    str = toChessNote(oldPos) + toChessNote(newPos);

    move(str);

    f[n].setPosition(newPos);
}

void Game1v1::playGame1v1()
{
    RenderWindow window(VideoMode(504, 504), "Chess Game1v1", Style::Titlebar | sf::Style::Close);

    //ConnectToEngine("stockfish.exe"); //vs computer

    t1.loadFromFile("../images/figures.png"); //pieces
    t2.loadFromFile("../images/board.png"); //background
    t3.loadFromFile("../images/erase.png"); //next move effects
    t4.loadFromFile("../images/next2.png");

    for(int i = 0; i < 32; ++i) f[i].setTexture(t1); //initialize the pieces
    for(int i = 0; i < 32; ++i) f2[i].setTexture(t3); //initialize the effects
    for(int i = 0; i < 32; ++i) f3[i].setTexture(t4); //initialize the effects

    Sprite sBoard(t2); //initialize the background

    loadPosition(); //initialize all the positions

    dx = 0;
    dy = 0;

    goodMove[1][2] = 1;

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset); //actual position of the mouse

        Event e;

        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) //closes the window
            {
                terminate = false;
                window.close();
            }

            //move back//
            if(e.type == Event::KeyPressed)
                if(e.key.code == Keyboard::BackSpace)
                {
                    if(position.length() > 6)
                        position.erase(position.length() - 6, 5);
                    loadPosition();
                }

            //drag and drop//
            if(e.type == Event::MouseButtonPressed)
            {
                if(isMove == false)
                {
                    if(e.key.code == Mouse::Left)
                        for(int i = 0; i < 32; ++i)
                            if(f[i].getGlobalBounds().contains(pos.x, pos.y))
                            {
                                isMove = true;

                                // AICI FUNCTIE CARE IMI DA IN goodMove TOATE POZITIILE VALIDE

                                n = i;
                                dx = pos.x - f[i].getPosition().x;
                                dy = pos.y - f[i].getPosition().y;
                                oldPos = f[i].getPosition();

                                usux = oldPos.x / size;
                                usuy = oldPos.y / size;

                                //std::cout << "OLD:  " << usux << ' ' << usuy << '\n';
                                //get the matrix position
                            }
                }
                else if(isMove == true)
                {
                    if(e.key.code == Mouse::Left)
                    {
                        isMove = false;

                        Vector2f p = f2[n].getPosition() + Vector2f(size / 2, size / 2);

                        newPos = Vector2f( size * int(p.x / size), size * int(p.y / size) );

                        usux = newPos.x / size;
                        usuy = newPos.y / size;

                        if(wrongMove[usux][usuy] == true)
                        {
                            releaseMove();
                            continue;
                        }

                        //std::cout << "NEW:  " << newPos.x / size << ' ' << newPos.y / size << '\n';

                        str = toChessNote(oldPos) + toChessNote(newPos);

                        move(str);

                        if(oldPos != newPos) position += str + " ";

                        f[n].setPosition(newPos);
                        f2[n].setPosition(newPos);
                    }
                }
            }
        }

        //comp move
//        if(Keyboard::isKeyPressed(Keyboard::Space))
//        {
//            str = getNextMove(position);
//
//            oldPos = toCoord(str[0], str[1]);
//            newPos = toCoord(str[2], str[3]);
//
//            for(int i = 0; i < 32; ++i)
//                if(f[i].getPosition() == oldPos) n = i;
//
//            //animation//
//            for(int k = 0; k < 50; ++k)
//            {
//                Vector2f p = newPos - oldPos;
//
//                f[n].move(p.x / 50, p.y / 50);
//
//                window.draw(sBoard);
//
//                for(int i = 0; i < 32; ++i) f[i].move(offset);
//
//                for(int i = 0; i < 32; ++i) window.draw(f[i]);
//
//                window.draw(f[n]);
//
//                for(int i = 0; i < 32; ++i) f[i].move(-offset);
//
//                window.display();
//            }
//
//            move(str);
//            position += str + " ";
//
//            f[n].setPosition(newPos);
//            f2[n].setPosition(newPos);
//        }

        if(isMove) f2[n].setPosition(pos.x - dx, pos.y - dy);

        // draw //
        window.clear();
        window.draw(sBoard);

        for(int i = 0; i < 32; ++i)
        {
            f[i].move(offset);
            f2[i].move(offset);
            f3[i].move(offset);
        }

        if(isMove == false)
        {
            for(int i = 0; i < 32; ++i) window.draw(f[i]);
        }

        else
        {
            for(int i = 0; i < 32; ++i)
            {
                if(n == i) continue;
                else window.draw(f[i]);
            }
            for(int i = 0; i < 8; ++i)
            {
                for(int j = 0; j < 8; ++j)
                {
                    if(goodMove[i][j])
                    {
                        f3[0].setPosition(28 + j * 56, 28 + i * 56);
                        window.draw(f3[0]);
                    }
                }
            }
            window.draw(f2[n]);
        }

        //window.draw(f[n]);

        //window.draw(f3[0]);

        for(int i = 0; i < 32; ++i)
        {
            f[i].move(-offset);
            f2[i].move(-offset);
            f3[i].move(-offset);
        }

        window.display();
    }
}
