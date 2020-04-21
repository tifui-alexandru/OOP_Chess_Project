#ifndef MOVE_H
#define MOVE
#include "board.h"
#include "utils.h"

class Move {
private:
    Piece *from_piece, *to_piece;
    Square from, to;
    Board *curr_board, *next_board;
    PieceColour col;
    static std::unordered_map <PieceType, std::string> AlgebraicPiece;

public:
    Move(const Square &from, const Square &to, Board *curr_bord, Board *next_board, const PieceColour &col);
    std::string toAlgebraicNotation();
    
};

#endif 