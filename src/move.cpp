#include "../include/utils.h"
#include "../include/move.h"

Move::Move(const Square &from, const Square &to, Board *curr_bord, Board *next_board, const PieceColour &col) : from(from), to(to), curr_board(curr_board), next_board(next_board), col(col) {
    from_piece = curr_board->get_piece(from);
    to_piece = curr_board->get_piece(to);
}

std::string Move::toChessNotation() {
    bool capture = false;
    if (to_piece) capture = true;

    std::string from_nottion, to_notation;
    to_notation = to.chess_notation_pos();
}