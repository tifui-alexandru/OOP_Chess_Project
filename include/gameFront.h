#ifndef GAMEFRONT_H
#define GAMEFRONT_H

#include <SFML/Graphics.hpp>
#include "game.h"
#include "promote.h"
#include "showEnd.h"

enum EventType {
    BOARD_CLICK,
    END_GAME,
    GET_HINT,
    RESIGN,
    OFFER_DRAW,
    DRAW,
    NOTHING,
    MENU_CLICK
};

class GameFront {
protected:
    const int squareSize = 56;
    const ButtonBox <size_t> boardBox = {28, 28, 28 + 8 * 56, 28 + 8 * 56};
    const ButtonBox <size_t> menuBox = {504, 0, 504 + 170, 504};

    sf::Texture piecesImg, movingPiecesImg, emptyBoardImg, highlightImg, kingSah;
    sf::RenderWindow window;
    Game* game;
    //std::unique_ptr<Game> game;
    std::vector<sf::Sprite> pieceSprites;
    std::vector<sf::Sprite> movingPieceSprites;
    sf::Sprite emptyBoardSprite, highlightSprite, chessPieceSprite[2];
    bool validMove[BOARD_SIZE][BOARD_SIZE];
    bool hintMove[BOARD_SIZE][BOARD_SIZE];
    bool isMoving;
    Square clickedSquare, secondClickedSquare;

    void printBoard();
    sf::Sprite getPieceSprite(const PieceType &piece, const PieceColour &colour, bool moving);
    Square getSquare(sf::Vector2i posCursor);
    EventType checkClick();
    virtual EventType checkMenuClick(const int& x, const int& y) = 0;
    void squareClicked();
public:
    GameFront(const std::string& gameModeName);
    ~GameFront();
};

#endif //GAMEFRONT_H