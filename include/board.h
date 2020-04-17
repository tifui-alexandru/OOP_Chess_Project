#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "utils.h"

class Board {
private:
    BoardType board;
    enum CastleType {
        QUEENSIDE,
        KINGSIDE
    };
public:
    //! Set the initial state of the board.
    Board();
    std::vector<Square> get_valid_moves(Square pos, PieceColour colour);
    Piece* get_piece(Square pos);
    Square get_king(const PieceColour &colour);
    bool cell_is_attacked(Square pos, PieceColour colour);
    bool castle(const PieceColour &colour, const CastleType &tp);
};

class Move {
private:
    Piece *from_piece, *to_piece;
    std::pair <Square, Square> mv;
    Board *current_board;
    Move(const std::pair <Square, Square> &mv, Board *board);
};

#endif //BOARD_H
