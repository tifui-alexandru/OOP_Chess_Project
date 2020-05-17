#include "../include/move.h"

Move::Move(const Square &from, const Square &to, Board *curr_board, Board *next_board, const PieceColour &col) : from(from), to(to), curr_board(curr_board), next_board(next_board), col(col) {
    from_piece = curr_board->get_piece(from);
    to_piece = curr_board->get_piece(to);
}

const std::unordered_map <int, std::string> Move::AlgebraicPiece = {
    {KING, "K"},
    {QUEEN, "Q"},
    {ROOK, "R"},
    {BISHOP, "B"},
    {KNIGHT, "K"},
    {PAWN, ""}
};

std::string Move::toAlgebraicNotation() {
    std::string ans;

    // solve castle first
    if (from_piece->get_type() == KING and from.x == to.x and abs(from.y - to.y) == 2) {
        if (from.y < to.y) ans = "O-O";
        else ans = "O-O-O";
    }

    // normal moves
    else {
        std::string from_notation, to_notation;
        to_notation = to.chess_notation_pos();
        if (to_piece) to_notation = "x" + to_notation; // capture
        from_notation = AlgebraicPiece.at(from_piece->get_type());

        // pawn case
        if (from_piece->get_type() == PAWN) {
            from_notation = static_cast<char>(from.y + 'a');
            if (to_piece) to_notation = "x" + to.chess_notation_pos();
            else to_notation = static_cast<char>(to.x + 1 + '0');
        }

        // handle en passant
        if (from_piece->get_type() == PAWN and from.y != to.y and to_piece == nullptr) {
            int add = (from_piece->get_colour() == WHITE ? -1 : 1);
            Square temp_piece = to + Square(add, 0);
            to_notation = "x" + temp_piece.chess_notation_pos() + " e.p.";
        }

        // solve ambiguity
        bool same_row = false, same_col = false, ambig = false;
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (i == from.x and j == from.y) continue;
                if (from_piece->get_type() == PAWN) continue;

                Piece* other_from = curr_board->get_piece({i, j});
                if (other_from == nullptr or other_from->get_type() != from_piece->get_type()) continue;

                std::vector <Square> temp = curr_board->get_valid_moves({i, j}, col);
                for (auto& it : temp) {
                    if (it == to) {
                        if (i == from.x) same_row = true;
                        if (j == from.y) same_col = true;
                        ambig = true;
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

        if (from_piece->get_type() == PAWN) {
            int back_rank = (from_piece->get_colour() == WHITE ? 7 : 0);
            if (to.x == back_rank) 
                to_notation += "=" + AlgebraicPiece.at(next_board->get_piece(to)->get_type());
        }

        ans = from_notation + to_notation;
    }

    PieceColour other_colour = (col == WHITE ? BLACK : WHITE);
    if (next_board->cell_is_attacked(next_board->get_king(other_colour), other_colour)) {
        if (next_board->get_status(other_colour, col) == CHECKMATE) ans += "#";
        else ans += "+";
    }

    return ans;
}

std::string Move::toLongAlgebraicNotation() {
    std::string promotionPiece = "";
    if (from_piece->get_type() == PAWN) {
        int back_rank = (from_piece->get_colour() == WHITE ? 7 : 0);
        if (to.x == back_rank) {
            auto piece = next_board->get_piece(to)->get_type();
            if (piece == QUEEN) promotionPiece = "q";
            else if (piece == ROOK) promotionPiece = "r";
            else if (piece == BISHOP) promotionPiece = "b";
            else promotionPiece = "k";
        }
    }
    return from.chess_notation_pos() + to.chess_notation_pos() + promotionPiece;
}

bool Move::operator==(const Move &other) {
    return (col == other.col && *from_piece == *other.from_piece && *to_piece == *other.to_piece);
}
