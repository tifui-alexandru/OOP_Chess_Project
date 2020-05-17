#include "../include/pieces.h"
#include "../include/utils.h"
#include <vector>

// N S E W NE NW SE SW
static const Square directions[8] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

Piece::Piece(const PieceColour &col, const Square &pos, const int &val, const PieceType &tp, int no_moves) : colour(col), position(pos), value(val), type(tp), no_moves(no_moves) {}

Piece* Piece::createPiece(const PieceType &piece, const PieceColour &col, const Square &pos) {
    if (piece == PAWN) return new Pawn(col, pos);
    if (piece == ROOK) return new Rook(col, pos);
    if (piece == KNIGHT) return new Knight(col, pos);
    if (piece == BISHOP) return new Bishop(col, pos);
    if (piece == QUEEN) return new Queen(col, pos);
    if (piece == KING) return new King(col, pos);
    return nullptr;
}

bool Piece::operator==(const Piece &other) {
    return (colour == other.colour && type == other.type && position == other.position);
}

King::King(const PieceColour &col, const Square &pos) : Piece(col, pos, 0, KING) {}
Queen::Queen(const PieceColour &col, const Square &pos) : Piece(col, pos, 9, QUEEN) {}
Rook::Rook(const PieceColour &col, const Square &pos) : Piece(col, pos, 5, ROOK) {}
Knight::Knight(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, KNIGHT) {}
Bishop::Bishop(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, BISHOP) {}
Pawn::Pawn(const PieceColour &col, const Square &pos) : Piece(col, pos, 1, PAWN), can_be_captured_en_passant(false) {}

inline std::pair<bool, bool> valid_move(const PieceColour &col, const Square &sq, const BoardType &board) {
    if (sq.inside_board() and board[sq.x][sq.y] == nullptr) return {true, false};

    if (!sq.inside_board() or board[sq.x][sq.y]->get_colour() == col) return {false, true};
    return {true, true}; // can capture
}

// ignoring check
std::vector <Square> King::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (auto& idx : directions) {
         Square temp = position + idx;
         if (valid_move(colour, temp, board).first) ans.emplace_back(temp);
     }
    return ans;
}

std::vector <Square> Queen::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (auto& idx : directions) 
        for (int dim = 1; dim < BOARD_SIZE; ++dim) {
            Square temp = position + (idx * Square(dim, dim));
            std::pair <bool, bool> cond = valid_move(colour, temp, board);
            if (cond.first) ans.emplace_back(temp);
            if (cond.second) break;
        }
    return ans;
}

std::vector <Square> Rook::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 0; idx < 4; ++idx) 
        for (int dim = 1; dim < BOARD_SIZE; ++dim) {
            Square temp = position + (directions[idx] * Square(dim, dim));
            std::pair <bool, bool> cond = valid_move(colour, temp, board);
            if (cond.first) ans.emplace_back(temp);
            if (cond.second) break;
        }
    return ans;
}

std::vector <Square> Knight::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 4; idx < BOARD_SIZE; ++idx) {
        Square temp1 = position + directions[idx] + (directions[idx] * Square(1, 0));
        Square temp2 = position + directions[idx] + (directions[idx] * Square(0, 1));

        if (valid_move(colour, temp1, board).first) ans.emplace_back(temp1);
        if (valid_move(colour, temp2, board).first) ans.emplace_back(temp2);
    }
    return ans;
}

std::vector <Square> Bishop::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 4; idx < BOARD_SIZE; ++idx)
        for (int dim = 1; dim <= 7; ++dim) {
            Square temp = position + (directions[idx] * Square(dim, dim));
             std::pair <bool, bool> cond = valid_move(colour, temp, board);
            if (cond.first) ans.emplace_back(temp);
            if (cond.second) break;
        }   
    return ans;
}

std::vector <Square> Pawn::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    int adv = (colour == WHITE ? 1 : -1);
    for (int add = -1; add <= 1; ++add) {
        Square temp = position + Square(adv, add);
        
        if (temp.inside_board()) {
            if (board[temp.x][temp.y] == nullptr and add == 0) ans.emplace_back(temp);
            else if (board[temp.x][temp.y] != nullptr and board[temp.x][temp.y]->get_colour() != colour and add) ans.emplace_back(temp);
        }
    }

    // 2 squares start
    if (!moved()) {
        Square temp = position + Square(2 * adv, 0);
        Square temp2 = position + Square(1 * adv, 0);
        if (board[temp2.x][temp2.y] == nullptr and board[temp.x][temp.y] == nullptr) ans.emplace_back(temp);
    }

    // en passant
    for (int add = -1; add <= 1; ++add) {
        if (add == 0) continue;
        Square temp = position + Square(0, add);
        if (temp.inside_board()) {
            if (board[temp.x][temp.y] == nullptr) continue;
            if (board[temp.x][temp.y]->get_type() == PAWN and board[temp.x][temp.y]->get_colour() != colour)
                if (dynamic_cast<Pawn*>(board[temp.x][temp.y])->get_en_passant())
                    ans.emplace_back(position + Square(adv, add));
        }
    }

    return ans;
}