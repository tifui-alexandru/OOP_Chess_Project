#include "../include/utils.h"
#include "../include/board.h"

Board::Board() {
    for (auto colour : {WHITE, BLACK}) {
        int row = 0, offset = 1;
        if (colour == BLACK) row =  7, offset = -1;
        board[row][0] = new Rook(colour, {row, 0});
        board[row][7] = new Rook(colour, {row, 7});
        board[row][1] = new Knight(colour, {row, 1});
        board[row][6] = new Knight(colour, {row, 6});
        board[row][2] = new Bishop(colour, {row, 2});
        board[row][5] = new Bishop(colour, {row, 5});
        board[row][3] = new Queen(colour, {row, 3});
        board[row][4] = new King(colour, {row, 4});

        for (int col = 0; col < 8; ++col)
            board[row + offset][col] = new Pawn(colour, {row + offset, col});
    }
}