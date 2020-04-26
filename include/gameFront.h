#ifndef GAMEFRONT_H
#define GAMEFRONT_H

#include <SFML/Graphics.hpp>
#include "game.h"

enum EventType {
    BOARD_CLICK,
    GO_BACK,
    GET_HINT,
    RESIGN,
    OFFER_DRAW,
    ACCEPT_DRAW,
    REFUSE_DRAW,
    NOTHING
};

class GameFront {
protected:
    const int squareSize = 56;
    const ButtonBox boardBox = {28, 28, 28 + 8 * 56, 28 + 8 * 56};

    sf::Texture piecesImg, movingPiecesImg, emptyBoardImg, highlightImg;
    sf::RenderWindow window;
    Game* game;
    std::vector<sf::Sprite> pieceSprites;
    std::vector<sf::Sprite> movingPieceSprites;
    sf::Sprite emptyBoardSprite, highlightSprite;
    bool validMove[BOARD_SIZE][BOARD_SIZE];
    bool isMoving;
    Square clickedSquare, secondClickedSquare;

    void printBoard();
    sf::Sprite getPieceSprite(const PieceType &piece, const PieceColour &colour, bool moving);
    Square getSquare(sf::Vector2i posCursor);
public:
    GameFront();
    EventType checkClick();
    void squareClicked();
};

#endif //GAMEFRONT_H