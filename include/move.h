#ifndef MOVE_H
#define MOVE
#include "board.h"
#include "utils.h"
#include <unordered_map>

class Move {
private:
    Piece *from_piece, *to_piece;
    Square from, to;
    Board *curr_board, *next_board;
    PieceColour col;
    static const std::unordered_map <int, std::string> AlgebraicPiece;

public:
    Move(const Square &from, const Square &to, Board *curr_bord, Board *next_board, const PieceColour &col);
    std::string toAlgebraicNotation();
    std::string toLongAlgebraicNotation();
};

#endif 