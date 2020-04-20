#ifndef MOVE_H
#define MOVE
#include "board.h"

class Move {
private:
    Piece *from_piece, *to_piece;
    Square from, to;
    Board *curr_board, *next_board;
    PieceColour col;
    Move(const Square &from, const Square &to, const Board *curr_bord, const Board *next_board, const PieceColour &col);
};

#endif 