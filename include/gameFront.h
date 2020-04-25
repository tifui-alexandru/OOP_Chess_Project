#ifndef GAMEFRONT_H
#define GAMEFRONT_H

#include <SFML/Graphics.hpp>
#include "game.h"

class GameFront {
protected:
    static const int squareSize = 56;
    const ButtonBox boardBox = {28, 28, 28 + 8 * 56, 28 + 8 * 56};

    sf::Texture piecesImg, movingPiecesImg, emptyBoardImg, highlightImg;
    sf::RenderWindow window;
    Game* game;
    std::vector<sf::Sprite> pieceSprites;
    std::vector<sf::Sprite> movingPieceSprites;
    sf::Sprite emptyBoardSprite, highlightSprite;
    bool validMove[BOARD_SIZE][BOARD_SIZE];
    bool isMoving;
    Square clickedSquare;
public:
    GameFront();
};

#endif //GAMEFRONT_H