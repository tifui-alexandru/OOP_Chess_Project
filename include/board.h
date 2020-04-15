#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "utils.h"

class Board {
private:
    Piece *board[BOARD_SIZE][BOARD_SIZE]{}; //! Set to nullptr
public:
    //! Set the initial state of the board.
    Board();
    // std::vector<Square> get_valid_moves(Square )
};

#endif //BOARD_H
