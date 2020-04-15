#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "utils.h"

class Board {
private:
    Piece *board[BOARD_SIZE][BOARD_SIZE];
public:
    //! Set the initial state of the board.
    Board() {
    }

};

#endif //BOARD_H
