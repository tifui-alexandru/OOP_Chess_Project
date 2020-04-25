#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/game1v1.h"
//#include "../Connector.hpp"

using namespace sf;

Game1v1::Game1v1()
{
    std::memset(goodMove, 0, sizeof(goodMove));

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
    //newPos = oldPos;

    //std::cout << "NEW:  " << newPos.x/size << ' ' << newPos.y/size << '\n';

    //str = toChessNote(oldPos) + toChessNote(newPos);

    move(str);

    f[n].setPosition(newPos);
}

int getPieceCode(const PieceType &tp, const PieceColour &col) {
    // in f2 daca sunt apasate
    //f[0] - tura galbena
    //f[1] - cal galben
    //f[2] - nebun galben
    //f[3] - regina galbena
    //f[4] - rege galben
    //f[8] - pion galben

    //f[16] - pion alb
    //f[24] - tura alba
    //f[25] - cal alb
    //f[26] - nebun alb
    //f[27] - regina alba
    //f[28] - rege alb

    //f3[0] - casuta

    if (col == WHITE) {
        if (tp == KING) return 28;
        if (tp == QUEEN) return 27;
        if (tp == ROOK) return 24;
        if (tp == BISHOP) return 26;
        if (tp == KNIGHT) return 25;
        if (tp == PAWN) return 16;
    }
    else {
        if (tp == KING) return 4;
        if (tp == QUEEN) return 3;
        if (tp == ROOK) return 0;
        if (tp == BISHOP) return 2;
        if (tp == KNIGHT) return 1;
        if (tp == PAWN) return 8;
    }
}

void Game1v1::playGame1v1()
{
    Game currGame;

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

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset); //actual position of the mouse

        Event e;

        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) //closes the window
            {
                terminate = true;
                window.close();
            }

            //move back//
//            if(e.type == Event::KeyPressed)
//                if(e.key.code == Keyboard::BackSpace)
//                {
//                    if(position.length() > 6)
//                        position.erase(position.length() - 6, 5);
//                    loadPosition();
//                }

            //drag and drop//
            if(e.type == Event::MouseButtonPressed)
            {
                if(isMove == false)
                {
                    if(e.key.code == Mouse::Left)
                    {
                                isMove = true;
                                // AICI FUNCTIE CARE IMI DA IN goodMove TOATE POZITIILE VALIDE
                                dy = pos.x / size; //pozitiile la primul click
                                dx = pos.y / size;

                                //dx dy casuta pe care am apasat-o

                                //std::cout << "OLD:  " << usux << ' ' << usuy << '\n';
                                //get the matrix position
                    }
                }
                else if(isMove == true)
                {
                    if(e.key.code == Mouse::Left)
                    {
                        isMove = false;

                        usux = pos.x / size; //pozitiile la click-ul 2
                        usuy = pos.y / size;

//                        if(goodMove[usux][usuy] == false)
//                        {
//                            releaseMove();
//                            continue;
//                        }

                        //std::cout << "NEW:  " << newPos.x / size << ' ' << newPos.y / size << '\n';

//                        str = toChessNote(oldPos) + toChessNote(newPos);
//
//                        move(str);
//
//                        if(oldPos != newPos) position += str + " ";
//
//                        f[n].setPosition(newPos);
//                        f2[n].setPosition(newPos);
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

        //if(isMove) f2[n].setPosition(pos.x - dx, pos.y - dy);

        // draw //
        window.clear();
        window.draw(sBoard);

        for(int i = 0; i < 32; ++i)
        {
            f[i].move(offset);
            f2[i].move(offset);
            f3[i].move(offset);
        }

        //drawboard

        Board* board = currGame.get_board();
        Square clickedSquare = Square(dx, dy).reverse();

        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j) {
                auto piece = board->get_piece({i, j});
                if (piece == nullptr or (isMove && Square(i, j) == clickedSquare)) continue;
                Sprite copy = f[getPieceCode(piece->get_type(), piece->get_colour())];

                Square temp = Square(28, 28) + Square(56, 56) * Square(i, j).reverse();

                copy.setPosition(temp.y, temp.x);

                window.draw(copy);

                // piece->get_type(), piece->get_colour()
            }


        for (int i = 0; i < BOARD_SIZE; ++i)
           for (int j = 0; j < BOARD_SIZE; ++j)
                if (goodMove[i][j]) {
                    Sprite copyBlue = f3[0];

                    Square tempBlue = Square(28, 28) + Square(56, 56) * Square(i, j).reverse();

                    copyBlue.setPosition(tempBlue.y, tempBlue.x);

                    window.draw(copyBlue);
                }

//        Sprite usu = f[1];
//
//                usu.setPosition(28 + 56 * 0, 28 + 56 * 1);
//                window.draw(usu);

        if (isMove) {
            auto piece = board->get_piece(clickedSquare);
            Sprite copyMove = f2[getPieceCode(piece->get_type(), piece->get_colour())];

            Square tempMove = Square(28, 28) + Square(56, 56) * Square(dx, dy);

            copyMove.setPosition(tempMove.x, tempMove.y);

            // cursor
        }

        for(int i = 0; i < 32; ++i)
        {
            f[i].move(-offset);
            f2[i].move(-offset);
            f3[i].move(-offset);
        }

        window.display();
    }
}
