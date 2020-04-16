#include <bits/stdc++.h>
#include "../include/pieces.h"
#include "../include/utils.h"

// N S E W NE NW SE SW
static const Square directions[8] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

Piece::Piece(const PieceColour &col, const Square &pos, const int &val, const PieceType &tp) : colour(col), position(pos), value(val), type(tp) {}

King::King(const PieceColour &col, const Square &pos) : Piece(col, pos, 0, KING) {}
Queen::Queen(const PieceColour &col, const Square &pos) : Piece(col, pos, 9, QUEEN) {}
Rook::Rook(const PieceColour &col, const Square &pos) : Piece(col, pos, 5, ROOK) {}
Knight::Knight(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, KNIGHT) {}
Bishop::Bishop(const PieceColour &col, const Square &pos) : Piece(col, pos, 3, BISHOP) {}
Pawn::Pawn(const PieceColour &col, const Square &pos) : Piece(col, pos, 1, PAWN) {}

// returns true if it is ok to move
// stop is true if the search should stop in that particular direction and false otherwise
inline bool valid_move(const PieceColour &col, const Square &sq, const BoardType &board, bool &stop) {
    stop = false;
    if (sq.inside_board() and board[sq.x][sq.y] == nullptr) return true;

    stop = true;
    if (!sq.inside_board() or board[sq.x][sq.y]->get_colour() == col) return false;
    return true; // can capture
}

// ignoring check
std::vector <Square> King::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (auto& idx : directions) {
         Square temp = position + idx;
         bool stop; // ignored
         if (valid_move(colour, temp, board, stop)) ans.emplace_back(temp);
     }
    return ans;
}

std::vector <Square> Queen::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (auto& idx : directions) 
        for (int dim = 1; dim < BOARD_SIZE; ++dim) {
            Square temp = position + (idx * Square(dim, dim));
            bool stop;
            if (valid_move(colour, temp, board, stop)) ans.emplace_back(temp);
            if (stop) break;
        }
    return ans;
}

std::vector <Square> Rook::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 0; idx < 4; ++idx) 
        for (int dim = 1; dim < BOARD_SIZE; ++dim) {
            Square temp = position + (directions[idx] * Square(dim, dim));
            bool stop;
            if (valid_move(colour, temp, board, stop)) ans.emplace_back(temp);
            if (stop) break;
        }
    return ans;
}

std::vector <Square> Knight::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 4; idx < BOARD_SIZE; ++idx) {
        Square temp1 = position + directions[idx] + (directions[idx] * Square(1, 0));
        Square temp2 = position + directions[idx] + (directions[idx] * Square(0, 1));
        bool stop; // ignored

        if (valid_move(colour, temp1, board, stop)) ans.emplace_back(temp1);
        if (valid_move(colour, temp2, board, stop)) ans.emplace_back(temp2);
    }
    return ans;
}

std::vector <Square> Bishop::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    for (int idx = 4; idx < BOARD_SIZE; ++idx)
        for (int dim = 1; dim <= 7; ++dim) {
            Square temp = position + (directions[idx] * Square(dim, dim));
            bool stop;
            if (valid_move(colour, temp, board, stop)) ans.emplace_back(temp);
            if (stop) break;
        }   
    return ans;
}

std::vector <Square> Pawn::get_possible_moves(const BoardType &board) {
    std::vector <Square> ans;
    int adv = (colour == WHITE ? 1 : -1);
    for (int add = -1; add <= 1; ++add) {
        Square temp = position + Square(adv, add);
        bool stop;
        if (temp.inside_board()) {
            if (board[temp.x][temp.y] == nullptr and add == 0) ans.emplace_back(temp);
            else if (board[temp.x][temp.y]->get_colour() != colour and add) ans.emplace_back(temp);
        }
    }
    return ans;
}