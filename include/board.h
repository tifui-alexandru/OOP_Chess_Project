#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "utils.h"

class Board {
private:
    BoardType board;
public:
    //! Set the initial state of the board.
    Board();
    std::vector<Square> get_valid_moves(Square pos, PieceColour colour);
    Piece* get_piece(Square pos);
};

class Move {
private:
    Piece *from_piece, *to_piece;
    std::pair <Square, Square> mv;
    Board *current_board;
    Move(const std::pair <Square, Square> &mv, Board *board);
};

#endif //BOARD_H
