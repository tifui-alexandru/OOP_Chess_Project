#ifndef GAMEFRONT_H
#define GAMEFRONT_H

#include <SFML/Graphics.hpp>
#include "game.h"
#include "promote.h"

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

    sf::Texture piecesImg, movingPiecesImg, emptyBoardImg, highlightImg, kingSah, buttonsMenuImg;
    sf::RenderWindow window;
    Game* game;
    std::vector<sf::Sprite> pieceSprites;
    std::vector<sf::Sprite> movingPieceSprites;
    sf::Sprite emptyBoardSprite, highlightSprite, buttonsMenuSprite;
    bool validMove[BOARD_SIZE][BOARD_SIZE];
    bool isMoving;
    Square clickedSquare, secondClickedSquare;

    void printBoard();
    sf::Sprite getPieceSprite(const PieceType &piece, const PieceColour &colour, bool moving);
    Square getSquare(sf::Vector2i posCursor);
    EventType checkClick();
    void squareClicked();
public:
    GameFront(const std::string& gameModeName);
};

#endif //GAMEFRONT_H