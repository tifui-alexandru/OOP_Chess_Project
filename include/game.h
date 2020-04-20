#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "utils.h"
#include "pieces.h"

class Game {
private:
    struct Player {
        std::vector<Piece> capturedPieces; ///Pieces captured by this player
        int pawnValue;
        PieceColour Colour;
        Player(const PieceColour Colour) {
            pawnValue = 39;
            Colour = Colour;
        }
    };
    Player playerToMove(WHITE)
};

#endif
