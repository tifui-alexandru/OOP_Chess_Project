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

// en passant ignored for now
// pawn promotion ignoed for now
std::string Move::toAlgebraicNotation() {
    std::string ans;

    // solve castle first
    if (from_piece->get_type() == KING and from.x == to.x and abs(from.x - to.x) == 2) {
        if (from.x < to.x) ans = "O-O";
        else ans = "O-O-O";
    }

    // normal moves
    else {
        std::string from_notation, to_notation;
        to_notation = to.chess_notation_pos();
        if (to_piece) to_notation = "x" + to_notation; // capture
        from_notation = AlgebraicPiece[from_piece->get_type()];

        // solve ambiguity
        bool same_row = false, same_col = false, ambig = false;
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (i == from.x and j == from.y) continue;

                Piece* other_from = curr_board->get_piece({i, j});
                if (other_from == nullptr or other_from->get_type() != from_piece->get_type()) continue;

                std::vector <Square> temp = curr_board->get_valid_moves({i, j}, col);
                bool found = false;
                for (auto& it : temp) {
                    ambig = true;
                    if (it == to) {
                        if (i == from.x) same_row = true;
                        if (j == from.y) same_col = true;
                    }
                }
            }
        if (ambig) {
            if (!same_col)
                from_notation += char('a' + from.y);
            else {
                if (!same_row)
                    from_notation += std::to_string(from.x + 1);
                else
                    from_notation += char('a' + from.y) + std::to_string(from.x + 1);
            }
        }

        ans = from_notation + to_notation;
    }

    PieceColour other_colour = (col == WHITE ? BLACK : WHITE);
    if (next_board->cell_is_attacked(next_board->get_king(other_colour), other_colour)) {
        if (next_board->checkmate()) ans += "#";
        else ans += "+";
    }

    return ans;
}