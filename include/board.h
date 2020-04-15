#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "utils.h"

class Board {
private:
    Piece *board[BOARD_SIZE][BOARD_SIZE];
public:
    Board() {
        //set the start board of the game

    }

};

#endif //BOARD_H
