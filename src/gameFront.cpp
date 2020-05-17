#include "../include/gameFront.h"

GameFront::GameFront(const std::string& gameModeName) {

    window.create(sf::VideoMode(674, 504), gameModeName, sf::Style::Titlebar | sf::Style::Close);
    //game = std::make_unique<Game>();
    game = new Game();

    if (!piecesImg.loadFromFile("../images/pieces.png")) throw std::runtime_error("Failed to load image");
    if (!movingPiecesImg.loadFromFile("../images/movingPieces.png")) throw std::runtime_error("Failed to load image");
    if (!emptyBoardImg.loadFromFile("../images/board.png")) throw std::runtime_error("Failed to load image");
    if (!highlightImg.loadFromFile("../images/highlight.png")) throw std::runtime_error("Failed to load image");
    if (!kingSah.loadFromFile("../images/sah.png")) throw std::runtime_error("Failed to load image");

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

    for (int i = 0; i < 2; ++i) {

        chessPieceSprite[i].setTexture(kingSah);
        chessPieceSprite[i].setTextureRect(sf::IntRect(squareSize * 4, squareSize * i, squareSize, squareSize));
    }


    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            validMove[i][j] = hintMove[i][j] = false;
    isMoving = false;
}

GameFront::~GameFront() {
    delete game;
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

            if (piece->get_type() == KING && board->cell_is_attacked({i, j}, piece->get_colour())) copy = chessPieceSprite[(int)piece->get_colour()];

            Square temp = Square(boardBox.topLeft.first, boardBox.topLeft.second) + Square(squareSize, squareSize) * Square(i, j).reverse();
            copy.setPosition((float)temp.y, (float)temp.x);
            window.draw(copy);
        }

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (validMove[i][j] or hintMove[i][j]) {
                sf::Sprite copy = highlightSprite;
                Square temp = Square(boardBox.topLeft.first, boardBox.topLeft.second) + Square(squareSize, squareSize) * Square(i, j).reverse();
                copy.setPosition((float)temp.y, (float)temp.x);
                window.draw(copy);
            }

    if (isMoving) {
        auto piece = board->get_piece(clickedSquare);
        sf::Sprite copy = getPieceSprite(piece->get_type(), piece->get_colour(), true);
        auto pos = sf::Mouse::getPosition(window);
        copy.setPosition(pos.x - (float)squareSize / 2, pos.y - (float)squareSize / 2);
        window.draw(copy);
    }
}

Square GameFront::getSquare(sf::Vector2i posCursor) {
    int x = posCursor.x - boardBox.topLeft.first;
    int y = posCursor.y - boardBox.topLeft.second;
    x /= squareSize;
    y /= squareSize;
    return Square(y, x).reverse();
}

EventType GameFront::checkClick() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // add new events here
        // ex: back button, get hint button

        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        if (event.type == sf::Event::MouseButtonPressed) {
            if ((int)event.key.code == (int)sf::Mouse::Left) {
                if (boardBox.isInside(mousePos.x, mousePos.y)) return BOARD_CLICK;
                else if (menuBox.isInside(mousePos.x, mousePos.y)) return checkMenuClick(mousePos.x, mousePos.y);
            }
        }
    }
    return NOTHING;
}

void GameFront::squareClicked() {
    Square pos = getSquare(sf::Mouse::getPosition(window));
    if (isMoving) {
        bool promotion = false;
        if (validMove[pos.x][pos.y]) {
            game->make_move(clickedSquare, pos);
            if ((pos.x == 7 or pos.x == 0) && game->get_board()->get_piece(pos)->get_type() == PAWN) promotion = true;
        }
        isMoving = false;
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                validMove[i][j] = hintMove[i][j] = false;
        if (promotion) {
            printBoard();
            window.display();
            window.clear();
            Promote promoteWindow;
            game->promote(pos, promoteWindow.getPiece());
        }
    } else {
        auto piece = game->get_board()->get_piece(pos);
        if (piece == nullptr or piece->get_colour() != game->getPlayerToMove()) return;
        auto possibleMoves = game->get_board()->get_valid_moves(pos, game->getPlayerToMove());
        if (possibleMoves.empty()) return;
        isMoving = true;
        clickedSquare = pos;
        for (auto p : possibleMoves)
            validMove[p.x][p.y] = true;
    }
}
