#include "../include/utils.h"
#include "../include/move.h"

Move::Move(const Square &from, const Square &to, Board *curr_bord, Board *next_board, const PieceColour &col) : from(from), to(to), curr_board(curr_board), next_board(next_board), col(col) {
    from_piece = curr_board->get_piece(from);
    to_piece = curr_board->get_piece(to);

    AlgebraicPiece[KING] = "K";
    AlgebraicPiece[QUEEN] = "Q";
    AlgebraicPiece[ROOK] = "R";
    AlgebraicPiece[BISHOP] = "B";
    AlgebraicPiece[KNIGHT] = "K";
    AlgebraicPiece[PAWN] = "";
}

std::string Move::toAlgebraicNotation() {
    std::string from_nottion, to_notation;
    to_notation = to.chess_notation_pos();
    if (to_piece) to_notation = "x" + to_notation; // capture
    from_nottion = AlgebraicPiece[from_piece->get_type()];
}