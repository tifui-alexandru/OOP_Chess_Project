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
    Board(const Board *obj);
    std::vector<Square> get_valid_moves(Square pos, PieceColour colour);
    Piece* get_piece(Square pos) const;
    Square get_king(const PieceColour &colour) const;
    bool cell_is_attacked(Square pos, PieceColour colour) const;
    bool castle(const PieceColour &colour, const CastleType &tp) const;
    void change_position(Piece* newPiece, Square pos);
};

class Move {
private:
    Piece *from_piece, *to_piece;
    Square from, to;
    Board *curr_board, *next_board;
    PieceColour col;
    Move(const std::pair <Square, Square> &mv, Board *board);
};

#endif //BOARD_H
