#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "move.h"
#include <vector>

class Game {
private:
    struct Player {
        std::vector<Piece*> capturedPieces; ///Pieces captured by this player
        int pawnValue;
        PieceColour colour;
        Player(PieceColour colour) : colour(colour), pawnValue(39) {}
    };
    Player *playerToMove, *playerToWait;
    std::vector<Board*> gameBoards;
    std::vector<Move*> gameMoves;
public:
    Game();
    Board* get_board(int time = -1);
    GameStatus make_move(Square from, Square to);
};

#endif
