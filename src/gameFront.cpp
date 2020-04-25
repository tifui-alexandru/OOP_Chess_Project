#include "../include/gameFront.h"

GameFront::GameFront() {
    window.create(sf::VideoMode(504, 504), "Chess Game1v1", sf::Style::Titlebar | sf::Style::Close);
    game = new Game();

    piecesImg.loadFromFile("../images/pieces.png");
    movingPiecesImg.loadFromFile("../images/movingPieces.png");
    emptyBoardImg.loadFromFile("../images/board.png");
    highlightImg.loadFromFile("../images/highlight.png");

    emptyBoardSprite.setTexture(emptyBoardImg);
    highlightSprite.setTexture(highlightImg);
    highlightSprite.setTextureRect(sf::IntRect(0, 0, squareSize, squareSize));

    pieceSprites.resize(12);
    for (int i = 0; i < 2; ++i) {
        pieceSprites[6 * i + 0].setTexture(piecesImg);
        pieceSprites[6 * i + 0].setTextureRect(sf::IntRect(squareSize * 5, squareSize * i, squareSize, squareSize));

        pieceSprites[6 * i + 1].setTexture(piecesImg);
        pieceSprites[6 * i + 1].setTextureRect(sf::IntRect(squareSize * 2, squareSize * i, squareSize, squareSize));

        pieceSprites[6 * i + 2].setTexture(piecesImg);
        pieceSprites[6 * i + 2].setTextureRect(sf::IntRect(squareSize * 1, squareSize * i, squareSize, squareSize));

        pieceSprites[6 * i + 3].setTexture(piecesImg);
        pieceSprites[6 * i + 3].setTextureRect(sf::IntRect(squareSize * 0, squareSize * i, squareSize, squareSize));

        pieceSprites[6 * i + 4].setTexture(piecesImg);
        pieceSprites[6 * i + 4].setTextureRect(sf::IntRect(squareSize * 3, squareSize * i, squareSize, squareSize));

        pieceSprites[6 * i + 5].setTexture(piecesImg);
        pieceSprites[6 * i + 5].setTextureRect(sf::IntRect(squareSize * 4, squareSize * i, squareSize, squareSize));
    }

    movingPieceSprites.resize(12);
    for (int i = 0; i < 2; ++i) {
        movingPieceSprites[6 * i + 0].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 0].setTextureRect(sf::IntRect(squareSize * 5, squareSize * i, squareSize, squareSize));

        movingPieceSprites[6 * i + 1].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 1].setTextureRect(sf::IntRect(squareSize * 2, squareSize * i, squareSize, squareSize));

        movingPieceSprites[6 * i + 2].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 2].setTextureRect(sf::IntRect(squareSize * 1, squareSize * i, squareSize, squareSize));

        movingPieceSprites[6 * i + 3].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 3].setTextureRect(sf::IntRect(squareSize * 0, squareSize * i, squareSize, squareSize));

        movingPieceSprites[6 * i + 4].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 4].setTextureRect(sf::IntRect(squareSize * 3, squareSize * i, squareSize, squareSize));

        movingPieceSprites[6 * i + 5].setTexture(movingPiecesImg);
        movingPieceSprites[6 * i + 5].setTextureRect(sf::IntRect(squareSize * 4, squareSize * i, squareSize, squareSize));
    }

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            validMove[i][j] = false;
    isMoving = false;
}

sf::Sprite GameFront::getPieceSprite(const PieceType &piece, const PieceColour &colour, bool moving) {
    int id = 6 * (int)colour + (int)piece;
    if (moving) return movingPieceSprites[id];
    return pieceSprites[id];
}


void GameFront::printBoard() {
    Board* board = game->get_board();
    window.draw(emptyBoardSprite);

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = board->get_piece({i, j});
            if (piece == nullptr or (isMoving && Square(i, j) == clickedSquare)) continue;
            sf::Sprite copy = getPieceSprite(piece->get_type(), piece->get_colour(), false);
            Square temp = Square(boardBox.topLeft.first, boardBox.topLeft.second) + Square(squareSize, squareSize) * Square(i, j).reverse();
            copy.setPosition((float)temp.y, (float)temp.x);
            window.draw(copy);
        }

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (validMove[i][j]) {
                sf::Sprite copy = highlightSprite;
                Square temp = Square(boardBox.topLeft.first, boardBox.topLeft.second) + Square(squareSize, squareSize) * Square(i, j).reverse();
                copy.setPosition((float)temp.y, (float)temp.x);
                window.draw(copy);
            }

    if (isMoving) {
        auto piece = board->get_piece(clickedSquare);
        sf::Sprite copy = getPieceSprite(piece->get_type(), piece->get_colour(), true);
        auto pos = sf::Mouse::getPosition(window);
        copy.setPosition(pos.x, pos.y);
        window.draw(copy);
    }
}

Square GameFront::getSquare(sf::Vector2i posCursor) {

    return Square();
}

