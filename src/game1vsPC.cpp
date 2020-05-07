#include "../include/game1vsPC.h"
#include "../include/chessEngine.h"
#include <string>
#include <cstdlib>

Game1vsPC::Game1vsPC(const PieceColour &humanCol) : GameFront("GameMode: 1 VS PC"), humanPlayer(humanCol) {}

void Game1vsPC::play() {
    int noCurrMoves = 0;
    PieceColour playerMoving = WHITE;
    std::string currBoardPosition;
    ConnectToEngine("../stockfish.exe");
    while(window.isOpen()) {
        window.clear();
        if (playerMoving == humanPlayer) {
            EventType event = checkClick();
            if (event == BOARD_CLICK) {
                squareClicked();
            }
        }
        else {
            PieceType newPiece = PAWN;
            std::pair <Square, Square> computerMove = getStockfishMove(currBoardPosition, newPiece);
            game->make_move(computerMove.first, computerMove.second);
            if (newPiece != PAWN) game->promote(computerMove.second, newPiece);
        }

        // new move has been made
        if (noCurrMoves != game->get_no_moves()) {
            Move* mv = game->get_last_move();

            // display move in Algrebraic notation -- here
            
            currBoardPosition += mv->toLongAlgebraicNotation() + " ";
            playerMoving = (playerMoving == WHITE ? BLACK : WHITE);

            ++noCurrMoves;
        }

        printBoard(); // print cu butoane si chestii

        if (game->get_status() != UNFINISHED) {
            // end of the game
            // display chestii
        }

        window.display();
    }
    CloseConnection();
}