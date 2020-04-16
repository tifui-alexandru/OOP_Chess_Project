#include "../include/utils.h"
#include "../include/board.h"

Board::Board() {
    board.resize(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; ++i)
        board[i].resize(BOARD_SIZE, nullptr);
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

        for (int col = 0; col < BOARD_SIZE; ++col)
            board[row + offset][col] = new Pawn(colour, {row + offset, col});
    }
}

Piece* Board::get_piece(Square pos) {
    return board[pos.x][pos.y];
}

// std::vector<Square> Board::get_valid_moves(Square pos, PieceColour colour) {
//     if (board[pos.x][pos.y] == nullptr or board[pos.x][pos.y]->get_colour() != colour) return {};
//     auto positions = board[pos.x][pos.y]->get_possible_moves();
//     std::vector<Square> valid_positions;
//     for (auto p : positions) {
//         if (board[p.x][p.y]->get_colour() == colour) continue;

//     }
// }

Move::Move(const std::pair <Square, Square> &mv, Board *board) : mv(mv), current_board(board) {

}