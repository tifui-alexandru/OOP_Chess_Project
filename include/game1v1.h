#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.h"
//#include "Connector.hpp"

using namespace sf;

class Game1v1
{

public:
    bool terminate;

    bool goodMove[8][8];
    int size = 56;
    bool isMove;
    //Square clickedSquare;
    //RenderWindow window;
    int board[8][8] =
    { {-1, -2, -3, -4, -5, -3, -2, -1},
      { -6, -6, -6, -6, -6, -6, -6, -6},
    {      0,  0,  0,  0,  0,  0,  0,  0},
{      0,  0,  0,  0,  0,  0,  0,  0},
{      0,  0,  0,  0,  0,  0,  0,  0},
{      0,  0,  0,  0,  0,  0,  0,  0},
{      6,  6,  6,  6,  6,  6,  6,  6},
{1,  2,  3,  4,  5,  3,  2,  1} };

    int usux, usuy, n;

    std::string str;

    std::string position;

    bool wrongMove[8][8];

    Vector2f oldPos, newPos;

    Vector2f offset;

    Sprite f[32]; //figures
    Sprite f2[32]; //actual
    Sprite f3[32]; //next

    Texture t1, t2, t3, t4;

    int dx, dy;

public:
    Game1v1();

    ~Game1v1();

    std::string toChessNote(Vector2f); //scientific notation

    Vector2f toCoord(char, char); //normal coordinates

    void move(std::string);

    void loadPosition();

    void initialise();

    void releaseMove();

    //void printBoard(Board* board);

    void playGame1v1();

};
