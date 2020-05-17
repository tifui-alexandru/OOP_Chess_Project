#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "utils.h"

enum GameStatus {
    UNFINISHED,
    CHECKMATE,
    RESIGNATION,
    TIMEOUT,
    STALEMATE,
    INSUFFICIENT_MATERIAL,
    MOVE50RULE,
    REPETITION,
    AGREEMENT
};

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
    ~Board();
    std::vector<Square> get_valid_moves(Square pos, PieceColour colour);

    Piece* get_piece(Square pos) const;
    Square get_king(const PieceColour &colour) const;

    bool cell_is_attacked(Square pos, PieceColour colour) const;
    bool castle(const PieceColour &colour, const CastleType &tp) const;
    void change_position(Piece* newPiece, Square pos);
    bool insufficient_material(const PieceColour &colour);
    GameStatus get_status(const PieceColour &colourToMove, const PieceColour &colourToWait);

    bool operator == (const Board& other);
    bool operator != (const Board& other) {return !(*this == other);}
};

#endif //BOARD_H
